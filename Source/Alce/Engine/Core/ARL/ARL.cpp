#include "ARL.hpp"
#include "../Data/ARLMessages.hpp"
#include "../Debug/Debug.hpp"
#include "../Kernel/Kernel.hpp"

using namespace alce;

void ARL_PROCESSOR::Shell(String prompt, Scene* scene)
{
    this->currentScene = scene;
    
    for(auto command : prompt.Split(";"))
    {
        Process(command.RemoveComments());
    }
}

void ARL_PROCESSOR::Process(String command)
{
    // std::stringstream ss(command);
    // std::string mainCmd;
    // ss >> mainCmd;
    command.Replace("\t", "");
    command.Replace("\n", "");

    auto args = command.Split(" ");

    args.ForEach([](String& arg) {
        arg.Trim();
    }).RemoveIf([](String arg) {
        return arg == "";
    });

    String mainCmd = args.First();

    if (mainCmd == "help") 
    {
        String subCmd = args[1];

        if(subCmd == "")
        {
            Debug.ARLMessage(ARLM.help);
        }
        else if(subCmd == "system")
        {
            Debug.ARLMessage(ARLM.helpSystem);
        }
        else if(subCmd == "window")
        {
            Debug.ARLMessage(ARLM.helpWindow);
        }
        else if(subCmd == "screen")
        {
            Debug.ARLMessage(ARLM.helpScreen);
        }
        else if(subCmd == "stop")
        {
            Debug.ARLMessage(ARLM.helpStop);
        }
        else if(subCmd == "play")
        {
            Debug.ARLMessage(ARLM.helpPlay);
        }
        else if(subCmd == "help")
        {
            Debug.ARLMessage(ARLM.helpHelp);
        }
        else if(subCmd == "standby")
        {
            Debug.ARLMessage(ARLM.helpStandby);
        }
        else if(subCmd == "grid scale")
        {
            Debug.ARLMessage(ARLM.helpGridScale);
        }
        else if(subCmd == "grid size")
        {
            Debug.ARLMessage(ARLM.helpGridSize);
        }
        else if(subCmd == "change to")
        {
            Debug.ARLMessage(ARLM.helpChangeTo);
        }
        else if(subCmd == "add object")
        {
            Debug.ARLMessage(ARLM.helpAddObject);
        }
        else if(subCmd == "add component")
        {
            Debug.ARLMessage(ARLM.helpAddComponent);
        }
        else if(subCmd == "delete object")
        {
            Debug.ARLMessage(ARLM.helpDeleteObject);
        }
        else if(subCmd == "delete component")
        {
            Debug.ARLMessage(ARLM.helpDeleteComponent);
        }
        else if(subCmd == "enable object")
        {
            Debug.ARLMessage(ARLM.helpEnableObject);
        }
        else if(subCmd == "disable component")
        {
            Debug.ARLMessage(ARLM.helpDisableComponent);
        }
        else if(subCmd == "disable object")
        {
            Debug.ARLMessage(ARLM.helpDisableObject);
        }
        else if(subCmd == "set object")
        {
            Debug.ARLMessage(ARLM.helpSetObject);
        }
        else if(subCmd == "set component")
        {
            Debug.ARLMessage(ARLM.helpSetComponent);
        }
        else
        {
            Debug.ARLMessage("Unknown Command {}\n\nUse help for more info.\n", {subCmd});
        }
    } 
    else if (mainCmd == "system") 
    {
        Debug.ARLMessage("\nOperating System: {}\nArchitecture: {}\nProcessor{}\nGraphics Card: {}\nTotal RAM: {}\nRAM in use: {}\nVideo Memory: {}\nDirectX Version: {}", {
            Alce.GetWindowsVersion(),
            Alce.GetArchitecture(),
            Alce.GetCPU(),
            Alce.GetGPU(),
            Alce.GetRAM(),
            Alce.GetRAMinUse(),
            Alce.GetVRAM(),
            Alce.GetDirectXVersion()
        });
    } 
    else if (mainCmd == "screen") 
    {
        Debug.ARLMessage("\n{}", {Alce.GetMonitorInfo()});
    } 
    else if (mainCmd == "window") 
    {
        Debug.ARLMessage("\n{}", {Alce.GetWindowInfo()});
    } 
    else if (mainCmd == "stop") 
    {
        currentScene->Pause(true);
    } 
    else if (mainCmd == "play") 
    {
        currentScene->Pause(false);
    } 
    else if (mainCmd == "exit") 
    {
        Alce.exit = true;
    } 
    else if (mainCmd == "switch") 
    {
        currentScene->DevelopmentMode(!currentScene->developmentMode);
        
        if(currentScene->developmentMode) Debug.ARLMessage("Switched to development mode.");
        else Debug.ARLMessage("Switched to production mode.");
    } 
    else if (mainCmd == "list") 
    {
        String message = String("Scene: " + currentScene->GetName().ToAnsiString() + "\n");

        for(auto& go: currentScene->GetAllGameObjects())
        {
            message += go->id + ": " + go->alias + "\n";
        }

        message.PopLast();

        Debug.ARLMessage(message);
    } 
    else if (mainCmd == "standby") 
    {
        String option = args[1];
        
        if(option == "on")
        {
            Alce.stanby = true;
            Debug.ARLMessage("Standby: ON");
        }
        else if(option == "off")
        {
            Alce.stanby = false;
            Debug.ARLMessage("Standby: OFF");
        }
        else if(option == "")
        {
            Debug.ARLError("Stanby command requires argument \"option\"");
        }
        else
        {
            Debug.ARLError("Unknown option {}", {option});
        }
    } 
    else if (mainCmd == "scene")
    {
        Debug.ARLMessage("Current scene: {}", {currentScene->name});
    }
    else if (mainCmd == "grid") 
    {
        String subCmd = args[1];

        if(subCmd == "scale")
        {
            int value = args[2].ParseInt();
            currentScene->GridScale = value;

            Debug.ARLMessage("Grid scale set to {}", {value});
        }
    } 
    else if (mainCmd == "has") 
    {
        String alias = args[1];

        for(auto& go: currentScene->GetAllGameObjects())
        {
            if(go->alias == alias)
            {
                Debug.ARLMessage("True");
                return;
            }
        }

        Debug.ARLMessage("False");
    } 
    else if (mainCmd == "change") 
    {
        //TODO: BUG AL PASAR DE ESCENA A OTRA: 
        std::cout << "Debug list:\n";
        for(auto& s: Alce.scenes)
        {
            std::cout << "\"" << s.first.ToAnsiString() << "\"\n";
        }

        String subCmd = args[1];

        if(subCmd == "to")
        {
            std::string scene = args.Last().ToAnsiString();
            
            Alce.SetCurrentScene(scene);
            currentScene = Alce.GetCurrentScene().get();
            Debug.ARLMessage("Changed to scene {}", {args.Last()});
        }
        else
        {
            Debug.ARLError("Syntax error, please check out 'help change to' for more info.");
        }
    } 
    else if (mainCmd == "add") 
    {
        // std::string type;
        // ss >> type;
        // if (type == "object") 
        // {
        //     std::string className, asKeyword, alias;
        //     ss >> className >> asKeyword >> alias;
        //     //TODO: add object command with className and alias
        //     std::cout << "Executing 'add object' with className: " << className << ", alias: " << alias << std::endl;
        // } 
        // else if (type == "component") 
        // {
        //     std::string className, toKeyword, alias;
        //     ss >> className >> toKeyword >> alias;
        //     //TODO: add component command with className and alias
        //     std::cout << "Executing 'add component' with className: " << className << ", alias: " << alias << std::endl;
        // }
    } 
    else if (mainCmd == "set") 
    {
        // std::string type;
        // ss >> type;
        // if (type == "object") 
        // {
        //     std::string alias, field, asKeyword, value;
        //     ss >> alias >> field >> asKeyword >> value;
        //     //TODO: set object command with alias, field, and value
        //     std::cout << "Executing 'set object' with alias: " << alias << ", field: " << field << ", value: " << value << std::endl;
        // } 
        // else if (type == "component") 
        // {
        //     std::string className, field, ofKeyword, alias, asKeyword, value;
        //     ss >> className >> field >> ofKeyword >> alias >> asKeyword >> value;
        //     //TODO: set component command with className, field, alias, and value
        //     std::cout << "Executing 'set component' with className: " << className << ", field: " << field << ", alias: " << alias << ", value: " << value << std::endl;
        // }
    } 
    else if (mainCmd == "delete") 
    {
        // std::string type;
        // ss >> type;
        // if (type == "object") 
        // {
        //     std::string alias;
        //     ss >> alias;
        //     //TODO: delete object command with alias
        //     std::cout << "Executing 'delete object' with alias: " << alias << std::endl;
        // } 
        // else if (type == "component") 
        // {
        //     std::string className, ofKeyword, alias;
        //     ss >> className >> ofKeyword >> alias;
        //     //TODO: delete component command with className and alias
        //     std::cout << "Executing 'delete component' with className: " << className << ", alias: " << alias << std::endl;
        // }
    } 
    else if (mainCmd == "enable") 
    {
        // std::string type;
        // ss >> type;
        // if (type == "object") 
        // {
        //     std::string alias;
        //     ss >> alias;
        //     //TODO: enable object command with alias
        //     std::cout << "Executing 'enable object' with alias: " << alias << std::endl;
        // } 
        // else if (type == "component") 
        // {
        //     std::string className, ofKeyword, alias;
        //     ss >> className >> ofKeyword >> alias;
        //     //TODO: enable component command with className and alias
        //     std::cout << "Executing 'enable component' with className: " << className << ", alias: " << alias << std::endl;
        // }
    } 
    else if (mainCmd == "disable") 
    {
        // std::string type;
        // ss >> type;
        // if (type == "object") 
        // {
        //     std::string alias;
        //     ss >> alias;
        //     //TODO: disable object command with alias
        //     std::cout << "Executing 'disable object' with alias: " << alias << std::endl;
        // } 
        // else if (type == "component") 
        // {
        //     std::string className, ofKeyword, alias;
        //     ss >> className >> ofKeyword >> alias;
        //     //TODO: disable component command with className and alias
        //     std::cout << "Executing 'disable component' with className: " << className << ", alias: " << alias << std::endl;
        // }
    } 
    else 
    {
        Debug.ARLError("Unknown command: {}", {command});
    }
}
