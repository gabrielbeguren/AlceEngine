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

void Scene::DebugMode(bool flag)
{
    debugMode = flag;
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
                
                //RenderGrid(Alce.GetWindow(), camera->view);
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

void Scene::RenderGrid(sf::RenderWindow& window, const sf::View& view)
{
    const float GRID_SPACING = 5.0f; // Espaciado de la cuadrícula en unidades de Box2D

    sf::Vector2f viewCenter = view.getCenter();
    sf::Vector2f viewSize = view.getSize();
    float left = viewCenter.x - viewSize.x / 2;
    float right = viewCenter.x + viewSize.x / 2;
    float top = viewCenter.y - viewSize.y / 2;
    float bottom = viewCenter.y + viewSize.y / 2;

    sf::Color gridColor(120, 120, 120); // Gris claro
    sf::Font font;
    if (!font.loadFromFile("Assets/fonts/Consolas/CONSOLA.ttf")) // Asegúrate de cargar una fuente válida
    {
        // Error loading font
        return;
    }

    // Convertir las coordenadas de la vista a coordenadas de Box2D
    float leftBox2D = left / PPM;
    float rightBox2D = right / PPM;
    float topBox2D = top / PPM;
    float bottomBox2D = bottom / PPM;

    // Redondear las coordenadas al múltiplo más cercano de GRID_SPACING
    float startX = std::floor(leftBox2D / GRID_SPACING) * GRID_SPACING;
    float endX = std::ceil(rightBox2D / GRID_SPACING) * GRID_SPACING;
    float startY = std::floor(topBox2D / GRID_SPACING) * GRID_SPACING;
    float endY = std::ceil(bottomBox2D / GRID_SPACING) * GRID_SPACING;

    // Dibujar líneas verticales y las coordenadas
    for (float x = startX; x <= endX; x += GRID_SPACING)
    {
        float xPixel = x * PPM;
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(xPixel, top), gridColor),
            sf::Vertex(sf::Vector2f(xPixel, bottom), gridColor)
        };
        window.draw(line, 2, sf::Lines);

        for (float y = startY; y <= endY; y += GRID_SPACING)
        {
            float yPixel = y * PPM;
            // Invertir la coordenada Y para Box2D
            float invertedY = -y;
            sf::Text text;
            text.setFont(font);
            text.setString("(" + std::to_string(static_cast<int>(x)) + ", " + std::to_string(static_cast<int>(invertedY)) + ")");
            text.setCharacterSize(10); // Tamaño de la letra
            text.setFillColor(gridColor);
            text.setPosition(xPixel, yPixel);
            window.draw(text);
        }
    }

    // Dibujar líneas horizontales
    for (float y = startY; y <= endY; y += GRID_SPACING)
    {
        float yPixel = y * PPM;
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(left, yPixel), gridColor),
            sf::Vertex(sf::Vector2f(right, yPixel), gridColor)
        };
        window.draw(line, 2, sf::Lines);
    }
}
