#include "Project/Scenes/Scenes.hpp"

using namespace alce;

int main()
{
    Kernel.Window("Alce Engine Test", DisplayMode::Default);
    Kernel.stanby = true;

    Kernel.AddScene<test::TestScene>();
    Kernel.SetCurrentScene("test");

    Kernel.Run();

    return 0;
}
