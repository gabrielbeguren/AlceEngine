#include "Scene.hpp"
#include "../Kernel/Kernel.hpp"
#include "../../Components/Camera/Camera.hpp"
#include "../../Components/Rigidbody2d/Rigidbody2d.hpp"
#include "../../Components/ParticleSystem/ParticleSystem.hpp"
#include "../../Components/SpriteRenderer/SpriteRenderer.hpp"
#include "../../Components/Animation2d/Animation2d.hpp"
#include "../../UI/TextInput/TextInput.hpp"
#include "../Json/Json.hpp"
#include <thread>

using namespace alce;

Scene::Scene(String name)
{
    this->name = name;
}

void Scene::InitPhysics(Vector2 gravity)
{
    world = std::make_shared<B2World>(gravity);
}

void Scene::Save()
{
    UpdateJson();
    std::thread task([&](){
        json.SaveAsFile(GetName(), "./Scenes/");
    });
    task.join();
}

void Scene::UpdateJson()
{
    json.FromString("{}");

    for(auto& sl : sortingLayers)
    {
        for(auto& go : *sl.second.get())
        {
            String jsonStr = R"({
                "id": "$id", 
                "alias": "$alias", 
                "transform": {
                    "position": "$position",
                    "rotation": $rotation,
                    "scale": "$scale"
                }
            })";

            jsonStr.Replace("$id", go->id);

            if(go->alias != false)
            {
                jsonStr.Replace("$alias", go->alias);
            }

            jsonStr.Replace("$position", go->transform.position.ToString());
            jsonStr.Replace("$rotation", go->transform.rotation);
            jsonStr.Replace("$scale", go->transform.scale.ToString());

            Json obj(jsonStr);

            json.Set(go->alias == false ? go->id : go->alias, obj);
            
        }
    }
}

void Scene::AddGameObject(GameObjectPtr gameObject, String alias)
{
    try
    {
        if(!sortingLayers.GetKeyList().Contains(gameObject->sortingLayer))
        {
            GameObjectListPtr list = std::make_shared<List<GameObjectPtr>>();
            list.get()->Add(gameObject);

            sortingLayers.Set(gameObject->sortingLayer, list);
            gameObject->scene = this;

            gameObject->alias = alias;

            if(persist)
            {
                UpdateJson();
            }
            return;
        }

        if(sortingLayers[gameObject->sortingLayer].get()->Contains(gameObject))
        {
            Debug.Warning("Scene already contains gameObject \"{}\"", {gameObject->id});
            return;
        }

        sortingLayers[gameObject->sortingLayer].get()->Add(gameObject);
        gameObject->scene = this;

        gameObject->alias = alias;

        if(persist)
        {
            UpdateJson();
            if(!JsonFileExists()) 
                Save();
        }
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

void Scene::AddCanvas(CanvasPtr canvas, ComponentPtr camera)
{
    if(canvasList.Contains(canvas))
    {
        Debug.Warning("Scene already contains Canvas \"{}\"", {canvas->id});
        return;
    }

    canvasList.Add(canvas);
    canvas->view = &((Camera*)camera.get())->view;
    canvas->rotation = &camera->transform->rotation;
    canvas->scale = &((Camera*)camera.get())->zoom;
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

void Scene::DevelopmentMode(bool flag)
{
    developmentMode = flag;
}

void Scene::Shell(String command)
{
    //TODO:
}

void Scene::EventsManager(sf::Event& e)
{
    switch(e.type)
    {
    case sf::Event::LostFocus:
        if(Alce.stanby)
            paused = true;
        break;
    case sf::Event::GainedFocus:
        if(paused) paused = false;
        break;
    case sf::Event::Closed:
        Alce.GetWindow().close();
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
    if(developmentMode)
    {
        for(auto& _camera: cameras)
        {
            Camera* camera = (Camera*) _camera;
            RenderGrid(Alce.GetWindow(), camera->view);
        }
    }


    for(auto& _camera: cameras)
    {
        Camera* camera = (Camera*) _camera;

        if(!camera->enabled) continue;



        Alce.GetWindow().setView(camera->view);

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

            if(developmentMode)
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

    for(auto& canvas: canvasList)
    {
        if(canvas->enabled)
        {
            canvas->Render();
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

        if(sortingLayer.second != nullptr)
        {
            sortingLayer.second->RemoveIf([](GameObjectPtr gameObject){
                return gameObject->destroyed;
            });
        }
    }

    for(auto& canvas: canvasList)
    {
        if(canvas->enabled)
        {
            canvas->Update();
        }
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

double calculateProportionalValue(int baseValue, double proportionalBase, int desiredValue) 
{
    return proportionalBase * (static_cast<double>(desiredValue) / baseValue);
}

int roundToNearestMultipleOf5(int value) 
{
    int remainder = value % 5;
    
    if (remainder <= 2) {
        return value - remainder;
    } else 
    {
        return value + (5 - remainder);
    }
}
void Scene::RenderGrid(sf::RenderWindow& window, const sf::View& view)
{
    sf::FloatRect viewport = view.getViewport();

    sf::Vector2f topLeft = window.mapPixelToCoords(sf::Vector2i(viewport.left * window.getSize().x, viewport.top * window.getSize().y), view);
    sf::Vector2f bottomRight = window.mapPixelToCoords(sf::Vector2i((viewport.left + viewport.width) * window.getSize().x, (viewport.top + viewport.height) * window.getSize().y), view);

    float startX = std::floor(topLeft.x / PPM / gridMargin) * gridMargin;
    float endX = std::ceil(bottomRight.x / PPM / gridMargin) * gridMargin;
    float startY = std::floor(topLeft.y / PPM / gridMargin) * gridMargin;
    float endY = std::ceil(bottomRight.y / PPM / gridMargin) * gridMargin;

    std::vector<sf::Vertex> lines;

    Color c = Color(sf::Color::Blue).Blend(Colors::Cyan);

    for (float x = startX; x <= endX; x += gridMargin) 
    {
        lines.emplace_back(sf::Vertex(sf::Vector2f(x * PPM, startY * PPM), c.ToSFMLColor()));
        lines.emplace_back(sf::Vertex(sf::Vector2f(x * PPM, endY * PPM), c.ToSFMLColor()));
    }

    for (float y = startY; y <= endY; y += gridMargin) 
    {
        lines.emplace_back(sf::Vertex(sf::Vector2f(startX * PPM, y * PPM), c.ToSFMLColor()));
        lines.emplace_back(sf::Vertex(sf::Vector2f(endX * PPM, y * PPM), c.ToSFMLColor()));
    }

    window.draw(&lines[0], lines.size(), sf::Lines);

    //TODO: this code doesn't work properly, Y axis positions are not reliable

    // sf::Font font;
    // if (!font.loadFromFile("Assets/fonts/Consolas/CONSOLA.ttf")) 
    // {
    //     return;
    // }

    // float viewHeight = (bottomRight.y - topLeft.y) / PPM;

    // float windowHeight = static_cast<float>(window.getSize().y);

    // for (float x = startX; x <= endX; x += 5) 
    // {
    //     for (float y = startY; y <= endY; y += 5) 
    //     {
    //         sf::Text text;
    //         text.setFont(font);
    //         float invertedY = viewHeight - (y - (topLeft.y / PPM));
    //         float adjustedY = std::round(invertedY / 5.0f) * 5 - roundToNearestMultipleOf5(calculateProportionalValue(720, 10.0, windowHeight));

    //         text.setString("(" + std::to_string(static_cast<int>(x)) + ", " + std::to_string(static_cast<int>(adjustedY)) + ")");
    //         text.setCharacterSize(10);
    //         text.setFillColor(sf::Color::White);
    //         text.setPosition(x * PPM, y * PPM);

    //         window.draw(text);
    //     }
    // }
}