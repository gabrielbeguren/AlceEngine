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
    Alce.GetCurrentScene()->Shell("help; help grid;");
    // Alce.GetCurrentScene()->Shell("system;screen;window;");
    
    Alce.Run();

    return 0;
}
