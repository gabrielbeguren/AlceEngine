#include "Project/Scenes/Scenes.hpp"

using namespace alce;

int main()
{
    Alce.Window("Alce Engine Test", DisplayMode::Default);
    Alce.stanby = true;

    Debug.SetWaitTime(0);

    //Alce.AddScene<Test1Scene::Test1>();
    Alce.AddScene<SampleScene::Sample>();
    
    Alce.SetCurrentScene("Sample");
    
    Alce.Run();

    return 0;
}


// int main() {
//     // Crear una cadena JSON usando un literal raw
//     alce::String jsonString = R"({
//         "name": "John",
//         "age": 30,
//         "address": {
//             "street": "123 Main St",
//             "city": "Anytown"
//         }
//     })";

//     // Crear un objeto Json usando esta cadena
//     alce::Json jsonObj(jsonString);

//     // Verificar y mostrar el contenido del JSON
//     if (jsonObj.IsValid()) {
//         std::cout << jsonObj.ToPrettyString().ToAnsiString() << std::endl;
//     } else {
//         std::cerr << "Invalid JSON format" << std::endl;
//     }

//     return 0;
// }