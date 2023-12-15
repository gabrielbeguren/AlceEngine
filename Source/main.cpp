#include "Project/Scenes/Scenes.hpp"

using namespace alce;

int main()
{
    Alce.Window("Alce Engine Test", DisplayMode::Default);
    Alce.stanby = true;

    Alce.AddScene<test::TestScene>();
    Alce.SetCurrentScene("test");

    Alce.Run();

    return 0;
}
