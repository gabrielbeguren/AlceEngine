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
