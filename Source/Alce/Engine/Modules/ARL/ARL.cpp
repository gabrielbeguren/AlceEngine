#include "ARL.hpp"
#include "../Data/ARLMessages.hpp"
#include "../Debug/Debug.hpp"
#include "../Core/Core.hpp"
#include "../Factory/Factory.hpp"
#include "../Debug/Debug.hpp"

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
    command.Replace("\t", "");
    command.Replace("\n", "");

    auto args = command.Split(" ");

    if(args.Length() == 0)
    {
        Debug.ARLError("There is no command to run.");
        return;
    }

    args.ForEach([](String& arg) {
        arg.Trim();
    }).RemoveIf([](String arg) {
        return arg == "";
    });

    String mainCmd = args.First();

    if (mainCmd == "help") 
    {
        if(args.Length() == 1)
        {
            Debug.ARLMessage(ARLM.help);
            return;
        }

        String subCmd = args[1];

        if(subCmd == "system")
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
        else if(subCmd == "grid")
        {
            Debug.ARLMessage("{}\n{}", {ARLM.helpGridScale, ARLM.helpGridSize});
        }
        else if(subCmd == "change to")
        {
            Debug.ARLMessage(ARLM.helpChangeTo);
        }
        else if(subCmd == "add")
        {
            Debug.ARLMessage("{}\n{}\n{}", {ARLM.helpAddObject, ARLM.helpAddComponent});
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
        if(args.Length() < 2)
        {
            Debug.ARLError("Syntax error, please check out 'help standby' for more info.");
            return;
        }

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
        if(args.Length() < 2)
        {
            Debug.ARLError("Syntax error, please check out 'help grid' for more info.");
            return;
        }

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
        if(args.Length() < 2)
        {
            Debug.ARLError("Syntax error, please check out 'help change to' for more info.");
            return;
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
        if(args.Length() < 5)
        {
            Debug.ARLError("Syntax error, please check out 'help add' for more info.");
            return;
        }

        String type = args[1];
        String creator = args[2];
        String alias = args[4];
        
        if(type == "object")
        {
            if(args[3] != "as")
            {
                Debug.ARLError("Syntax error, please check out 'help add' for more info.");
                return;
            }

            if(!Factory.Has(creator))
            {
                Debug.ARLError("There is no creator \"" + creator.ToAnsiString() + "\" registrated in the instance factory.");
                return;
            }

            auto result = currentScene->GetAllGameObjects().Filter([&](GameObjectPtr go) {
                return alias == go->alias;
            });

            if(result.Length() > 0) 
            {
                Debug.ARLError("An object with the alias name \"" + alias.ToAnsiString() + "\" already exists in the scene.");
                return;
            }   

            auto instance = Factory.Create<GameObject>(creator);
            currentScene->AddGameObject(instance, alias);
        }
        else if(type == "component")
        {
            if(args[3] != "to")
            {
                Debug.ARLError("Syntax error, please check out 'help add' for more info.");
                return;
            }
            
            //TODO:
        }
        else
        {
            Debug.ARLError("Syntax error, please check out 'help add' for more info.");
        }
    } 
    else if (mainCmd == "set") 
    {
        if(args.Length() < 6)
        {
            Debug.ARLError("Syntax error, please check out 'help set' for more info.");
            return;
        }

        String type = args[1];

        if(type == "object")
        {
            String alias = args[2];

            auto result = currentScene->GetAllGameObjects().Filter([&](GameObjectPtr go) {
                return alias == go->alias;
            });
            
            if(result.Length() == 0)
            {
                Debug.ARLError("There is no object with the alias \"" + alias.ToAnsiString() + "\" in the scene.");
                return;
            }   

            String field = args[2];

            //TODO: comprobar que existe ese campo

        }

        if(type == "component")
        {
            //TODO:
        }
    } 
    else if (mainCmd == "delete") 
    {
        if(args.Length() < 3)
        {
            Debug.ARLError("Syntax error, please check out 'help enable' for more info.");
            return;
        }

        String type = args[1];

        if(type == "object")
        {
            String alias = args[2];

            auto result = currentScene->GetAllGameObjects().Filter([&](GameObjectPtr go) {
                return go->alias == alias;
            });

            if(result.Length() == 0)
            {
                Debug.ARLError("There is no object with the alias \"" + alias.ToAnsiString() + "\" in the scene.");
                return;
            }

            result.First()->Destroy();
            Debug.ARLMessage("Object \"" + alias.ToAnsiString() + "\" destroyed.");
        }

        if(type == "component")
        {
            //TODO:
        }
    } 
    else if (mainCmd == "enable") 
    {   
        if(args.Length() < 3)
        {
            Debug.ARLError("Syntax error, please check out 'help enable' for more info.");
            return;
        }

        String type = args[1];

        if(type == "object")
        {
            String alias = args[2];

            auto result = currentScene->GetAllGameObjects().Filter([&](GameObjectPtr go) {
                return alias == go->alias;
            });

            if(result.Length() == 0) 
            {
                Debug.ARLError("There is no object with the alias \"" + alias.ToAnsiString() + "\" in the scene.");
                return;
            }   

            result.First()->enabled = true;
            Debug.ARLMessage("Object \"" + alias.ToAnsiString() + "\" enabled.");
        }

        if(type == "component")
        {
            //TODO:
        }
    } 
    else if (mainCmd == "disable") 
    {
        if(args.Length() < 3)
        {
            Debug.ARLError("Syntax error, please check out 'help enable' for more info.");
            return;
        }

        String type = args[1];

        if(type == "object")
        {
            String alias = args[2];

            auto result = currentScene->GetAllGameObjects().Filter([&](GameObjectPtr go) {
                return alias == go->alias;
            });

            if(result.Length() == 0) 
            {
                Debug.ARLError("There is no object with the alias \"" + alias.ToAnsiString() + "\" in the scene.");
                return;
            }   

            result.First()->enabled = false;
            Debug.ARLMessage("Object \"" + alias.ToAnsiString() + "\" disabled.");
        }

        if(type == "component")
        {
            //TODO:
        }
    } 
    else 
    {
        Debug.ARLError("Unknown command: {}", {command});
    }
}
