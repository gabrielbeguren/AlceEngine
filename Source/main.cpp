#include "Project/Scenes/Scenes.hpp"

using namespace alce;

int main()
{
    Alce.Window("Alce Engine Test", DisplayMode::Default);
    Alce.stanby = true;

    Alce.AddScene<Test1Scene::Test1>();
    Alce.AddScene<SampleScene::Sample>();
    
    Alce.SetCurrentScene("Sample");
    
    Alce.Run();

    return 0;
}

// int main() {
//     EventEmitter emitter;

//     // Registro de oyentes con comportamiento específico usando lambdas
//     emitter.addListener("EventType1", [](const Event& event) {
//         std::cout << "Listener 1 received: " << event.getMessage() << std::endl;
//     });

//     emitter.addListener("EventType1", [](const Event& event) {
//         std::cout << "Listener 2 received: " << event.getMessage() << std::endl;
//     });

//     emitter.addListener("EventType2", [](const Event& event) {
//         std::cout << "Listener 3 received: " << event.getMessage() << std::endl;
//     });

//     // Emisión de eventos
//     Event event1("EventType1", "Hello, Event 1!");
//     Event event2("EventType2", "Hello, Event 2!");

//     emitter.emitEvent(event1);
//     emitter.emitEvent(event2);

//     return 0;
// }