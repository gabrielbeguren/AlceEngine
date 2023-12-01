#include "Scene.hpp"
#include "../Kernel/Kernel.hpp"
#include "../../Components/Camera/Camera.hpp"
#include "../../Components/Rigidbody2d/Rigidbody2d.hpp"
#include "../../Components/ParticleSystem/ParticleSystem.hpp"
#include "../../Components/SpriteRenderer/SpriteRenderer.hpp"
#include "../../Components/Animation2d/Animation2d.hpp"

using namespace alce;

Scene::Scene(String name)
{
    this->name = name;
}

void Scene::InitPhysics(Vector2 gravity)
{
    world = std::make_shared<B2World>(gravity);
}

void Scene::AddGameObject(GameObjectPtr gameObject)
{
    try
    {
        if(!sortingLayers.GetKeyList().Contains(gameObject->sortingLayer))
        {
            GameObjectListPtr list = std::make_shared<List<GameObjectPtr>>();
            list.get()->Add(gameObject);

            sortingLayers.Set(gameObject->sortingLayer, list);
            gameObject->scene = this;
            return;
        }

        if(sortingLayers[gameObject->sortingLayer].get()->Contains(gameObject))
        {
            Debug.Warning("Scene already contains gameObject \"{}\"", {gameObject->id});
            return;
        }

        sortingLayers[gameObject->sortingLayer].get()->Add(gameObject);
        gameObject->scene = this;
    }
    catch(const std::exception& e)
    {
        Debug.Warning("Internal error: {}", {std::string(e.what())});
    }
}

List<GameObjectPtr> Scene::GetAllGameObjects()
{
    List<GameObjectPtr> gameObjects;

    for(auto& i: sortingLayers.GetValueList())
    {
        gameObjects.Merge(*i.get());
    }

    return gameObjects;
}

void Scene::AddUILayer(UILayerPtr _UILayer)
{
    if(UILayer.Contains(_UILayer))
    {
        Debug.Warning("Scene already contains UILayer \"{}\"", {_UILayer->id});
        return;
    }

    UILayer.Add(_UILayer);
}

String Scene::GetName()
{
    return name;
}

void Scene::Pause(bool flag)
{
    paused = flag;
}

bool Scene::IsPaused()
{
    return paused;
}

void Scene::Clear()
{
    sortingLayers.Clear();
}

B2WorldPtr Scene::GetWorld()
{
    return world;
}

void Scene::DebugMode(bool flag)
{
    debugMode = flag;
}

void Scene::EventsManager(sf::Event& e)
{
    switch(e.type)
    {
    case sf::Event::LostFocus:
        if(Kernel.stanby)
            paused = true;
        break;
    case sf::Event::GainedFocus:
        if(paused) paused = false;
        break;
    case sf::Event::Closed:
        Kernel.GetWindow().close();
        break;
    }

    for(auto& sortingLayer: sortingLayers)
    {
        for(auto& gameObject: *sortingLayer.second.get())
        {
            gameObject->EventManager(e);

            for(auto& component: gameObject->GetComponents())
            {
                component->EventManager(e);
            }
        }
    }
}

void Scene::Render()
{
    for(auto& _camera: cameras)
    {
        Camera* camera = (Camera*) _camera;

        if(!camera->enabled) continue;

        Kernel.GetWindow().setView(camera->view);

        auto layers = sortingLayers.GetKeyList();
        int max = Math.Max<int>(~layers);

        for(int i = max; i >= 0; i--)
        {
            if(!layers.Contains(i)) continue;
            
            for(auto& gameObject: *sortingLayers.Get(i).get())
            {
                if(!gameObject->enabled) continue;

                if(gameObject->cardinals.Empty())
                {
                    if(!camera->GetBounds().InArea(gameObject->transform.position.ToPixels())) continue;
                }
                else
                {
                    if(!camera->GetBounds().InArea(*gameObject->cardinals["top-left"].get()) &&
                    !camera->GetBounds().InArea(*gameObject->cardinals["top-right"].get()) &&
                    !camera->GetBounds().InArea(*gameObject->cardinals["bottom-left"].get()) &&
                    !camera->GetBounds().InArea(*gameObject->cardinals["bottom-right"].get()))
                    {
                        continue;
                    }
                }

                gameObject->Render();
            }

            if(debugMode)
            {
                for(auto& gameObject: *sortingLayers.Get(i).get())
                {
                    if(!gameObject->enabled) continue;

                    if(gameObject->cardinals.Empty())
                    {
                        if(!camera->GetBounds().InArea(gameObject->transform.position.ToPixels())) continue;
                    }
                    else
                    {
                        if(!camera->GetBounds().InArea(*gameObject->cardinals["top-left"].get()) &&
                        !camera->GetBounds().InArea(*gameObject->cardinals["top-right"].get()) &&
                        !camera->GetBounds().InArea(*gameObject->cardinals["bottom-left"].get()) &&
                        !camera->GetBounds().InArea(*gameObject->cardinals["bottom-right"].get()))
                        {
                            continue;
                        }
                    }

                    for(auto& component: gameObject->GetComponents())
                    {
                        component->DebugRender();
                    }

                    gameObject->DebugRender();
                }
            }
        }
    }
}

void Scene::Update()
{
    if(paused) return;

    if(world != nullptr) world->Step();

    for(auto& sortingLayer: sortingLayers)
    {
        for(auto& gameObject: *sortingLayer.second.get())
        {
            if(!gameObject->enabled) continue;
            
            gameObject->Update();

            for(auto& component: gameObject->GetComponents())
            {
                if(!component->enabled) continue;
                component->Update();

                if(component->id == "SpriteRenderer")
                    SetCardinals(gameObject,  gameObject->GetComponent<SpriteRenderer>()->GetCardinals());

                if(component->id == "Animation2d")
                    SetCardinals(gameObject, gameObject->GetComponent<Animation2d>()->GetCardinals());
            }
        }

        sortingLayer.second->RemoveIf([](GameObjectPtr gameObject){
            return gameObject->destroyed;
        });
    }
}

void Scene::SetCardinals(GameObjectPtr gameObject, Dictionary<String, Vector2Ptr> cardinals)
{
    if(!gameObject->cardinals.HasKey("top-left") || cardinals.HasKey("top-left") && (
    gameObject->cardinals["top-left"]->y > cardinals["top-left"]->y ||
    gameObject->cardinals["top-left"]->x > cardinals["top-left"]->x))
    {
        gameObject->cardinals.Set("top-left", cardinals["top-left"]);
    }

    if(!gameObject->cardinals.HasKey("top-right") || cardinals.HasKey("top-right") && ( 
    gameObject->cardinals["top-right"]->y > cardinals["top-right"]->y ||
    gameObject->cardinals["top-right"]->x < cardinals["top-right"]->x))
    {
        gameObject->cardinals.Set("top-right", cardinals["top-right"]);
    }

    if(!gameObject->cardinals.HasKey("bottom-left") || cardinals.HasKey("bottom-left") && (
    gameObject->cardinals["bottom-left"]->y < cardinals["bottom-left"]->y ||
    gameObject->cardinals["bottom-left"]->x > cardinals["bottom-left"]->x))
    {
        gameObject->cardinals.Set("bottom-left", cardinals["bottom-left"]);
    }

    if(!gameObject->cardinals.HasKey("bottom-right") || cardinals.HasKey("bottom-right") && (
    gameObject->cardinals["bottom-right"]->y < cardinals["bottom-right"]->y ||
    gameObject->cardinals["bottom-right"]->x < cardinals["bottom-right"]->x))
    {
        gameObject->cardinals.Set("bottom-right", cardinals["bottom-right"]);
    }
}
