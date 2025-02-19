#include "Project/Scenes/Scenes.hpp"

using namespace alce;

int main()
{
    Alce.Window("Alce Engine Test", DisplayMode::Default);
    Alce.stanby = true;

    Debug.SetWaitTime(0);

    Alce.AddScene<Test1Scene::Test1>();
    Alce.AddScene<SampleScene::Sample>();
    
    Alce.SetCurrentScene("Sample");
    //Alce.GetCurrentScene()->Shell("help; help grid;");
    // Alce.GetCurrentScene()->Shell("system;screen;window;");
    
    Alce.Run();

    return 0;
}

// #include <iostream>
// #include <memory>
// #include <unordered_map>
// #include <string>
// #include <functional>
// #include <stdexcept>

// class FactorySingleton {
// public:
//     // Alias para simplificar la definición de las lambdas
//     using Creator = std::function<std::shared_ptr<void>()>;

//     // Método para obtener la instancia del singleton
//     static FactorySingleton& getInstance() {
//         static FactorySingleton instance;
//         return instance;
//     }

//     // Registrar un creador bajo una clave específica
//     void registerCreator(const std::string& key, Creator creator) {
//         if (creators.find(key) != creators.end()) {
//             throw std::runtime_error("Creator with key '" + key + "' already exists.");
//         }
//         creators[key] = std::move(creator);
//     }

//     // Obtener una instancia llamando al creador asociado a la clave
//     template <typename T>
//     std::shared_ptr<T> create(const std::string& key) {
//         auto it = creators.find(key);
//         if (it == creators.end()) {
//             throw std::runtime_error("No creator registered for key '" + key + "'.");
//         }
//         return std::static_pointer_cast<T>(it->second());
//     }

// private:
//     // Constructor privado para asegurar el patrón singleton
//     FactorySingleton() = default;

//     // Evitar copias o asignaciones
//     FactorySingleton(const FactorySingleton&) = delete;
//     FactorySingleton& operator=(const FactorySingleton&) = delete;

//     // Mapa de claves a lambdas creadoras
//     std::unordered_map<std::string, Creator> creators;
// };

// // Ejemplo de uso
// class MyClass {
// public:
//     MyClass(int x) : value(x) {
//         std::cout << "MyClass created with value: " << value << std::endl;
//     }

//     void showValue() const {
//         std::cout << "Value: " << value << std::endl;
//     }

// private:
//     int value;
// };

// class Punto
// {
// public:

//     Punto(int _x, int _y)
//     {
//         x = _x;
//         y = _y;
//     }

//     std::string get()
//     {
//         return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
//     }

// private:

//     int x;
//     int y;
// };

// int main() 
// {
//     auto& factory = FactorySingleton::getInstance();

//     factory.registerCreator("MyClass", []() {
//         return std::make_shared<MyClass>(42); 
//     });

//     auto myObject = factory.create<MyClass>("MyClass");
//     myObject->showValue();

//     factory.registerCreator("Punto1", []() {
//         return std::make_shared<Punto>(3, 4);
//     });

//     factory.registerCreator("Punto2", []() {
//         return std::make_shared<Punto>(10, 10);
//     });

//     auto p1 = factory.create<Punto>("Punto1");
//     auto p2 = factory.create<Punto>("Punto2");

//     std::cout << "--------------------------\n";
//     std::cout << p1->get() << "\n" << p2->get() << "\n";

//     return 0;
// }
