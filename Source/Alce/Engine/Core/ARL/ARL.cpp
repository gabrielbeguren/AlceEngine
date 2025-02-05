#include "ARL.hpp"
#include "../Data/ARLPMessages.hpp"
#include "../Debug/Debug.hpp"

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
            Debug.ARLPMessage(ARLPM.help);
        }
        else if(subCmd == "system")
        {
            Debug.ARLPMessage(ARLPM.helpSystem);
        }
        else if(subCmd == "window")
        {
            Debug.ARLPMessage(ARLPM.helpWindow);
        }
        else if(subCmd == "screen")
        {
            Debug.ARLPMessage(ARLPM.helpScreen);
        }
        else if(subCmd == "stop")
        {
            Debug.ARLPMessage(ARLPM.helpStop);
        }
        else if(subCmd == "play")
        {
            Debug.ARLPMessage(ARLPM.helpPlay);
        }
        else if(subCmd == "help")
        {
            Debug.ARLPMessage(ARLPM.helpHelp);
        }
        else if(subCmd == "standby")
        {
            Debug.ARLPMessage(ARLPM.helpStandby);
        }
        else if(subCmd == "grid scale")
        {
            Debug.ARLPMessage(ARLPM.helpGridScale);
        }
        else if(subCmd == "grid size")
        {
            Debug.ARLPMessage(ARLPM.helpGridSize);
        }
        else if(subCmd == "change to")
        {
            Debug.ARLPMessage(ARLPM.helpChangeTo);
        }
        else if(subCmd == "add object")
        {
            Debug.ARLPMessage(ARLPM.helpAddObject);
        }
        else if(subCmd == "add component")
        {
            Debug.ARLPMessage(ARLPM.helpAddComponent);
        }
        else if(subCmd == "delete object")
        {
            Debug.ARLPMessage(ARLPM.helpDeleteObject);
        }
        else if(subCmd == "delete component")
        {
            Debug.ARLPMessage(ARLPM.helpDeleteComponent);
        }
        else if(subCmd == "enable object")
        {
            Debug.ARLPMessage(ARLPM.helpEnableObject);
        }
        else if(subCmd == "disable component")
        {
            Debug.ARLPMessage(ARLPM.helpDisableComponent);
        }
        else if(subCmd == "disable object")
        {
            Debug.ARLPMessage(ARLPM.helpDisableObject);
        }
        else if(subCmd == "set object")
        {
            Debug.ARLPMessage(ARLPM.helpSetObject);
        }
        else if(subCmd == "set component")
        {
            Debug.ARLPMessage(ARLPM.helpSetComponent);
        }
        else
        {
            Debug.ARLPMessage("Unknown Command {}\n\nUse help for more info.\n", {subCmd});
        }
    } 
    else if (mainCmd == "system") 
    {
        //TODO: system command
        std::cout << "Executing 'system'" << std::endl;
    } 
    else if (mainCmd == "window") 
    {
        //TODO: window command
        std::cout << "Executing 'window'" << std::endl;
    } 
    else if (mainCmd == "screen") 
    {
        //TODO: screen command
        std::cout << "Executing 'screen'" << std::endl;
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
