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
        command.Trim();
        Process(command.RemoveComments().ToAnsiString());
    }
}

void ARL_PROCESSOR::Process(const std::string& command)
{
    std::stringstream ss(command);
    std::string mainCmd;
    ss >> mainCmd;

    if (mainCmd == "help") 
    {
        std::string subCmd;
        ss >> subCmd;

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
        //TODO: stop command
        std::cout << "Executing 'stop'" << std::endl;
    } 
    else if (mainCmd == "play") 
    {
        //TODO: play command
        std::cout << "Executing 'play'" << std::endl;
    } 
    else if (mainCmd == "exit") 
    {
        //TODO: exit command
        std::cout << "Executing 'exit'" << std::endl;
    } 
    else if (mainCmd == "switch") 
    {
        //TODO: switch command
        std::cout << "Executing 'switch'" << std::endl;
    } 
    else if (mainCmd == "list") 
    {
        //TODO: list command
        std::cout << "Executing 'list'" << std::endl;
    } 
    else if (mainCmd == "standby") 
    {
        std::string option;
        ss >> option;
        //TODO: standby command with option
        std::cout << "Executing 'standby' with option: " << option << std::endl;
    } 
    else if (mainCmd == "grid") 
    {
        std::string subCmd;
        ss >> subCmd;
        if (subCmd == "scale") 
        {
            float value;
            ss >> value;
            //TODO: grid scale command with value
            std::cout << "Executing 'grid scale' with value: " << value << std::endl;
        } 
        else if (subCmd == "size") 
        {
            float value;
            ss >> value;
            //TODO: grid size command with value
            std::cout << "Executing 'grid size' with value: " << value << std::endl;
        }
    } 
    else if (mainCmd == "has") 
    {
        std::string alias;
        ss >> alias;
        //TODO: has command with alias
        std::cout << "Executing 'has' with alias: " << alias << std::endl;
    } 
    else if (mainCmd == "change") 
    {
        std::string subCmd;
        ss >> subCmd;
        if (subCmd == "to") 
        {
            std::string scene;
            ss >> scene;
            //TODO: change to command with scene
            std::cout << "Executing 'change to' with scene: " << scene << std::endl;
        }
    } 
    else if (mainCmd == "add") 
    {
        std::string type;
        ss >> type;
        if (type == "object") 
        {
            std::string className, asKeyword, alias;
            ss >> className >> asKeyword >> alias;
            //TODO: add object command with className and alias
            std::cout << "Executing 'add object' with className: " << className << ", alias: " << alias << std::endl;
        } 
        else if (type == "component") 
        {
            std::string className, toKeyword, alias;
            ss >> className >> toKeyword >> alias;
            //TODO: add component command with className and alias
            std::cout << "Executing 'add component' with className: " << className << ", alias: " << alias << std::endl;
        }
    } 
    else if (mainCmd == "set") 
    {
        std::string type;
        ss >> type;
        if (type == "object") 
        {
            std::string alias, field, asKeyword, value;
            ss >> alias >> field >> asKeyword >> value;
            //TODO: set object command with alias, field, and value
            std::cout << "Executing 'set object' with alias: " << alias << ", field: " << field << ", value: " << value << std::endl;
        } 
        else if (type == "component") 
        {
            std::string className, field, ofKeyword, alias, asKeyword, value;
            ss >> className >> field >> ofKeyword >> alias >> asKeyword >> value;
            //TODO: set component command with className, field, alias, and value
            std::cout << "Executing 'set component' with className: " << className << ", field: " << field << ", alias: " << alias << ", value: " << value << std::endl;
        }
    } 
    else if (mainCmd == "delete") 
    {
        std::string type;
        ss >> type;
        if (type == "object") 
        {
            std::string alias;
            ss >> alias;
            //TODO: delete object command with alias
            std::cout << "Executing 'delete object' with alias: " << alias << std::endl;
        } 
        else if (type == "component") 
        {
            std::string className, ofKeyword, alias;
            ss >> className >> ofKeyword >> alias;
            //TODO: delete component command with className and alias
            std::cout << "Executing 'delete component' with className: " << className << ", alias: " << alias << std::endl;
        }
    } 
    else if (mainCmd == "enable") 
    {
        std::string type;
        ss >> type;
        if (type == "object") 
        {
            std::string alias;
            ss >> alias;
            //TODO: enable object command with alias
            std::cout << "Executing 'enable object' with alias: " << alias << std::endl;
        } 
        else if (type == "component") 
        {
            std::string className, ofKeyword, alias;
            ss >> className >> ofKeyword >> alias;
            //TODO: enable component command with className and alias
            std::cout << "Executing 'enable component' with className: " << className << ", alias: " << alias << std::endl;
        }
    } 
    else if (mainCmd == "disable") 
    {
        std::string type;
        ss >> type;
        if (type == "object") 
        {
            std::string alias;
            ss >> alias;
            //TODO: disable object command with alias
            std::cout << "Executing 'disable object' with alias: " << alias << std::endl;
        } 
        else if (type == "component") 
        {
            std::string className, ofKeyword, alias;
            ss >> className >> ofKeyword >> alias;
            //TODO: disable component command with className and alias
            std::cout << "Executing 'disable component' with className: " << className << ", alias: " << alias << std::endl;
        }
    } 
    else 
    {
        std::cerr << "Unknown command: " << command << std::endl;
    }
}
