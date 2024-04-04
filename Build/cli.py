import json
import sys
import os
import glob
import shutil
import re
import subprocess

from pathlib import Path

#region global variables

compiler_bin_path = None

project_name = "Alce-Project"
project_icon = None

build_mode = "debug"
build_express = False

cpp_files = None
hpp_files = None

compile_stack = []

#endregion

#region output functions

def prints(message, style=None):
    if style is None:
        print(message, end="")
    else:
        styles = {
            "red": "\033[91m",
            "green": "\033[92m",
            "yellow": "\033[93m",
            "blue": "\033[94m",
            "magenta": "\033[95m",
            "cyan": "\033[96m",
            "grey": "\033[90m",
            "bold": "\033[1m",
            "underline": "\033[4m"
        }

        if style in styles:
            print(styles[style] + message + "\033[0m", end="")
        else:
            print(message, end="")

def error(message):
    print("\033[91m❌ " + message + "\033[97m")

def warning(message):
    print("\033[93m⚠️ " + message + "\033[97m")

def printHelp():

    prints("Alce CLI Alpha (2023)\n\n", "magenta")

    print("Alce Command Line Interface (CLI) provides functionality for building and managing Alce projects.")

    prints("\nInfo Commands:\n\n", "underline")
    prints(" --version, -v", "green")
    prints(": Display Alce CLI version information.\n")
    prints(" --help, -h", "green")
    prints(": Show help and usage information for Alce CLI commands\n")

    prints("\nInit Command:\n\n", "underline")
    prints(" init, i", "green")
    prints(": Creates the required configuration file \"./Build/settings.json\" with the next fields.\n")

    prints("\nCompilation Commands:\n\n", "underline")
    prints(" compile, c", "green")
    prints(": Compile the project. Use [./Build/alce compile --help] for more info.\n")

    prints("\nRun Commands:\n\n", "underline")
    prints(" run, r", "green")
    prints(": Runs the project. Use [./Build/alce run --help] for more info.\n")

    prints("\nGeneration Commands:\n\n", "underline")
    prints(" generate, g", "green")
    prints(": Generate elements like components, scenes, or objects. Use [./Build/alce generate --help] for more info.\n")

    prints("\nNote:\n", "underline")
    prints("Make sure to configure the MinGW (GCC v13.1.0^) 32bits compiler path in the ")
    prints("Build/settings.json", "underline")
    prints(" file.\n\n")

def printVersion():    
    prints("Alce CLI Alpha (2023)\n", "magenta")

#endregion

#region input functions

def handleArguments(argument_stack):

    global build_express, build_mode

    tasks = []

    last = ""
    first = ""

    for i in argument_stack:
        k = int(i.split(":")[0])
        v = i.split(":")[-1]

        if k == 1:

            # Display Alce CLI version
            if v == "--version" or v == "-v":
                printVersion()    
                sys.exit(0)  
            
            # Display help
            if v == "--help" or v == "-h":
                printHelp()
                sys.exit(0)

            if v == "init" or v == "i":
                None

            # Compile the project
            elif v == "compile" or v == "c":
                tasks.append("compile 0")

            # Run the compiled project
            elif v == "run" or v == "r":
                tasks.append("run 0 standard")

            # Generate element (component, scene, object)
            elif v == "generate" or v == "g":
                tasks.append("generate 0")

            else:
                error(f"Invalid argument \"{v}\"")
                sys.exit(1)

            first = v

        else:

            if v == last:
                error(f"Invalid command: argument \"{v}\" repeated twice")
                sys.exit(1)

            # Compiling options (express build, full build, build mode)
            if first == "compile" or first == "c":

                # Alias name
                if v.split("=")[0] == "alias" or v.split("=")[0] == "a":
                    if not isAliasValid(v.split('=')[-1]):
                        error(f"Invalid alias name \"{v.split('=')[-1]}\"")
                        sys.exit(1)

                    tasks.remove("compile 0")
                    tasks.append(f"compile {v.split('=')[-1]}")

                # Build mode (development, release)
                elif v.split("=")[0] == "mode" or v.split("=")[0] == "m":
                    if len(v.split("=")) < 2:
                        error(f"Invalid use of argument \"{v.split('=')[0]}\", value is missing.")
                        sys.exit(1)
                    if v.split("=")[-1] == "development":
                        build_mode = "development"
                    elif v.split("=")[-1] == "release":
                        build_mode = "release"
                    else:
                        error(f"Invalid build mode \"{v.split('=')[-1]}\"")
                        sys.exit(1)

                # Express build (only compiles modified and untracked files)
                elif v == "--express" or v == "-e":
                    build_express = True

                # Full compile (compiles everything from scratch)
                elif v == "--full" or v == "-f":
                    build_express = False
            
            # Run options (select alias)
            elif first == "run" or first == "r":
                
                # Run alias
                if v.split("=")[0] == "alias" or v.split("=")[0] == "a":
                    if not isAliasValid(v.split("=")[1]):
                        error(f"Invalid alias name \"{v.split('=')[1]}\"")
                        sys.exit(1)
                    
                    prev_run_task = list(filter(lambda x: x.split(" ")[0] == "run", tasks))[0]
                    mode = prev_run_task.split(" ")[2]

                    tasks.remove(prev_run_task)
                    tasks.append(f"run {v.split('=')[-1]} {mode}")

                # Standard run (no debugger)
                elif v == "--standard" or v == "-std":
                    for task in tasks:
                        if task.split(" ")[0] == "run" and task.split(" ")[2] != "standard":
                            tasks.remove(task)
                            tasks.append(f"run {task.split(' ')[1]} standard")

                # Run with debugger (GNU's GDB)
                elif v == "--debug" or v == "-d":
                    for task in tasks:
                        if task.split(" ")[0] == "run" and task.split(" ")[2] != "debug":
                            tasks.remove(task)
                            tasks.append(f"run {task.split(' ')[1]} debug")

                elif v != "--help" and v != "-h":
                    error(f"Invalid argument \"{v}\". Use [alce run --help] for more info.")
                    sys.exit(1)
                            
            # Generation options (component, scene, object)
            elif first == "generate" or first == "g":

                if len(v.split("=")) < 2 and (v.split("=")[0] != "--help" and v.split("=")[0] != "-h"):
                    error(f"Invalid use of argument \"{v.split('=')[0]}\", class name is missing.")
                    sys.exit(1)

                # Generate new component (Alce)
                if v.split("=")[0] == "component" or v.split("=")[0] == "c":
                    if not isClassNameValid(v.split("=")[-1]):
                        error(f"Invalid class name \"{v.split('=')[-1]}\"")
                        sys.exit(1)
                    tasks.append(f"generate component {v.split('=')[-1]}")
                    tasks.remove("generate 0")

                # Generate new scene (Project)
                elif v.split("=")[0] == "scene" or v.split("=")[0] == "s":
                    if not isClassNameValid(v.split("=")[-1]):
                        error(f"Invalid class name \"{v.split('=')[-1]}\"")
                        sys.exit(1)
                    tasks.append(f"generate scene {v.split('=')[-1]}")
                    tasks.remove("generate 0")

                # Generate new GameObject (Project)
                elif v.split("=")[0] == "object" or v.split("=")[0] == "o":
                    if len(v.split("=")[-1].split("@")) != 2:
                        error("Invalid use of [object] argument.")
                        sys.exit(1)

                    scene = v.split("=")[-1].split("@")[0]
                    object = v.split("=")[-1].split("@")[-1]
                    tasks.append(f"generate object {scene}@{object}")
                    tasks.remove("generate 0")

                # Generate method implementation
                elif v.split("=")[0] == "implementation" or v.split("=")[0] == "i":
                    if len(v.split("=")[-1].split("@")) < 2:
                        error("Invalid use of [implementation] argument.")
                        sys.exit(1)
                    
                    target_type = v.split("=")[-1].split("@")[0]
                    name = "$".join(v.split("=")[-1].split("@")[1:])

                    tasks.append(f"generate implementation {target_type}@{name}")
                    tasks.remove("generate 0")
                
                elif v.split("=")[0] != "--help" and v.split("=")[0] != "-h":
                    error(f"Invalid argument \"{v.split('=')[0]}\" for generation command.")
                    sys.exit(1)

            elif first == "init" or first == "i":
                None

            else:
                error(f"Invalid argument \"{v}\"")
                sys.exit(1)
            
            if v == "--help" or v == "-h":
                # Compile command help
                if last == "compile" or last == "c":
                    prints("\nDescription:\n\n", "underline")
                    prints("  Compiles the project using an alias name.\n")
                    prints("\nCommand usage:\n\n", "underline")
                    prints("  ./Build/alce", "grey")
                    prints(" [compile, c] [alias, a]", "green")
                    prints("=<")
                    prints("alias_name", "yellow")
                    prints("> ")
                    prints("[mode, m]", "green")
                    prints("<")
                    prints("development", "magenta")
                    prints("|")
                    prints("release", "magenta")
                    prints("> ")
                    prints("[--full, -f]", "green")
                    prints("|")
                    prints("[--express, -e]\n\n", "green")
                    prints("Compilation methods:\n\n", "underline")
                    prints("  [--express, -e]", "green")
                    prints(": only compiles modified and untracked files in the project.\n\n")
                    prints("  [--full, -f]", "green")
                    prints(": compiles all files in the project.\n\n")
                    prints("Build modes:\n\n", "underline")
                    prints("  [mode, m]=development", "green")
                    prints(": the project execution will be accompanied by a debugging console.\n\n")
                    prints("  [mode, m]=release", "green")
                    prints(": the project execution will be clean and free of debugging information\n\n")
                    prints("Default values:\n\n", "underline")
                    prints("  Compilation Method: ")
                    prints("--full\n\n", "magenta")
                    prints("  Build Mode: ")
                    prints("mode=development\n\n", "magenta")
                    prints("Examples:\n\n", "underline")
                    prints("  ./Build/alce compile alias=your_project_alias", "grey")
                    prints(": Compile the project using default values.\n\n")
                    prints("  ./Build/alce compile alias=compile_test --express", "grey")
                    prints(": only compiles modified and untracked files in the project.\n\n")
                    prints("  ./Build/alce compile alias=compile_test --full", "grey")
                    prints(": compiles all files in the project.\n\n")
                # Run command help
                elif (last == "run" or last == "r") and not ("compile" in tasks):
                    prints("\nCommand usage:\n\n", "underline")
                    prints("  [run, r] [alias, a]=<alias> <options>", "green")
                    prints(": executes a compiled build of project by alias name.\n\n")
                    prints("Options:\n\n", "underline")
                    prints("  [--debug, -d]", "green")
                    prints(": run the project with GNU gdb debugger.\n\n")
                    prints("  [--standard, -std]", "green")
                    prints(": run the project as standard.\n\n")
                    prints("Examples:\n\n", "underline")
                    prints("  ./Build/alce run alias=run_test --debug", "grey")
                    prints(": executes alias \"run_test\" with gdb.\n\n")
                    prints("  ./Build/alce run alias=run_test", "grey")
                    prints(": executes alias \"run_test\" as standard (by default).\n\n")
                # Generate command help
                elif last == "generate" or last == "g":
                    prints("\nCommand usage:\n\n", "underline")
                    prints("  [generate, g] [component, c]=<class_name> | [scene, s]=<scene_name> | [object, o]=<scene_name>@<object_name>]", "green")
                    prints(": generates a new entity (Component or Scene or Object) in the project.\n\n")
                    prints("  [generate, g] [implementation, i]=<target_type>@<sceneName?>@<target_name>", "green")
                    prints(": implements all the methods with the \"//@impl\" decorator in the targeted class.\n\n")
                    prints("Examples:\n\n", "underline")
                    prints("  ./Build/alce generate component=MyComponent", "grey")
                    prints(": generates a new component named \"MyComponent\"\n\n")
                    prints("  ./Build/alce generate scene=MyScene", "grey")
                    prints(": generates a new scene named \"MyScene\"\n\n")
                    prints("  ./Build/alce generate object=MyScene@Player", "grey")
                    prints(": generates a new object named \"Player\" in \"MyScene\"\n\n")      
                    prints("  ./Build/alce generate implementation=MyScene@Player", "grey")
                    prints(": implements all methods with \"//@impl\" decorator in the \"Player\" object class of scene \"MyScene\"\n\n")  
                # TODO: Init command help
                elif last == "init" or last == "i":
                    prints("\nCommand usage:\n\n", "underline")
                    prints("  [init, i]", "green")
                    prints(": creates the required configuration file ")
                    prints("Build/Settings", "underline")
                    prints("with the next fields:\n\n")
                    prints("  -> Compiler\n\n", "green")
                    prints("    -> bin-path", "blue")
                    prints(": the bin path of the MinGW32 compiler.\n\n")
                    prints("  -> Project\n\n", "green")
                    prints("    -> name", "blue")
                    prints(": the name of the current project.\n")
                    prints("    -> icon", "blue")
                    prints(": the .ico file for the executable.\n\n")
                    prints("Examples:\n\n", "underline")
                    #TODO:

                else:
                    prints("\nUndefined help display for this command, use ")
                    prints("./Build/alce --help", "green")
                    prints(" to get more info.\n\n")
                sys.exit(0)
        
        last = v

    return tasks

#endregion

#region filesystem functions

def isDir(path):
    return Path(path).is_dir()

def wasModified(file):
    extension = file.split(".")[-1]

    if extension == "hpp":

        hpp_tracking_file = open("./Tracking/hpp_tracking.txt", "r")
        hpp_tracking = hpp_tracking_file.readlines()
        hpp_tracking_file.close()

        for hpp in hpp_tracking:
            if hpp.split(":")[0] == file:
                registered_mtime = hpp.split(":")[-1].replace("\n", "")
                current_mtime = os.path.getmtime(file).__str__()

                if registered_mtime == current_mtime:
                    return False
                else:
                    return True
                
    if extension == "cpp":

        cpp_tracking_file = open("./Tracking/cpp_tracking.txt", "r")
        cpp_tracking = cpp_tracking_file.readlines()
        cpp_tracking_file.close()

        for cpp in cpp_tracking:
            if cpp.split(":")[0] == file:
                registered_mtime = cpp.split(":")[-1].replace("\n", "")
                current_mtime = os.path.getmtime(file).__str__()

                if registered_mtime == current_mtime:
                    return False
                else:
                    return True
    
    # Not found 
    return True

def addToTrack(file):

    extension = file.split(".")[-1]

    if extension == "cpp":
        cpp_tracking_file_r = open("./Tracking/cpp_tracking.txt", "r")
        cpp_tracking = cpp_tracking_file_r.readlines()
        cpp_tracking_file_r.close()

        for cpp in cpp_tracking:
            if cpp.split(":")[0] == file:
                cpp_tracking.remove(cpp)
        
        cpp_tracking.append(file + ":" + os.path.getmtime(file).__str__() + "\n")

        cpp_tracking_file_w = open("./Tracking/cpp_tracking.txt", "w")
        cpp_tracking_file_w.write("")

        for cpp in cpp_tracking:
            cpp_tracking_file_w.write(cpp)

        cpp_tracking_file_w.close()
    
    if extension == "hpp":
        hpp_tracking_file_r = open("./Tracking/hpp_tracking.txt", "r")
        hpp_tracking = hpp_tracking_file_r.readlines()
        hpp_tracking_file_r.close()

        for hpp in hpp_tracking:
            if hpp.split(":")[0] == file:
                hpp_tracking.remove(hpp)

        hpp_tracking.append(file + ":" + os.path.getmtime(file).__str__() + "\n")

        hpp_tracking_file_w = open("./Tracking/hpp_tracking.txt", "w")
        hpp_tracking_file_w.write("")

        for hpp in hpp_tracking:
            hpp_tracking_file_w.write(hpp)
        
        hpp_tracking_file_w.close()

def generateComponent(name):

    if isDir(f"./../Source/Alce/Engine/Components/{name}"):
        error(f"A component named \"{name}\" already exists in the engine")
        sys.exit(1)
    
    os.makedirs(f"./../Source/Alce/Engine/Components/{name}")

    hpp = open(f"./../Source/Alce/Engine/Components/{name}/{name}.hpp", "w")
    
    hpp.write("#pragma once\n\n")
    hpp.write("#include \"../../Core/Core.hpp\"\n\n")
    hpp.write("namespace alce\n")
    hpp.write("{\n")
    hpp.write(f"\tclass {name} : public Component\n")
    hpp.write("\t{\n")
    hpp.write("\tpublic:\n\n")
    hpp.write(f"\t\t{name}();\n\n")
    hpp.write("\t\tvoid Init();\n\n")
    hpp.write("\t\tvoid Start();\n\n")
    hpp.write("\t\tvoid Render();\n\n")
    hpp.write("\t\tvoid Update();\n\n")
    hpp.write("\t};\n\n")
    hpp.write(f"\ttypedef std::shared_ptr<{name}> {name}Ptr;\n")
    hpp.write("}")

    hpp.close()

    cpp = open(f"./../Source/Alce/Engine/Components/{name}/{name}.cpp", "w")

    cpp.write(f"#include \"{name}.hpp\"\n\n")
    cpp.write(f"using namespace alce;\n\n")
    cpp.write(f"{name}::{name}() : Component(\"{name}\")\n")
    cpp.write("{\n\t\n}\n\n")
    cpp.write("//Custom methods implementation\n")
    cpp.write("#pragma region implementation\n\n")
    cpp.write("\n#pragma endregion\n\n")
    cpp.write("//Inherited methods\n")
    cpp.write("#pragma region inherited\n\n")
    cpp.write(f"void {name}::Init()\n")
    cpp.write("{\n\t\n}\n\n")
    cpp.write(f"void {name}::Start()\n")
    cpp.write("{\n\t\n}\n\n")
    cpp.write(f"void {name}::Render()\n")
    cpp.write("{\n\t\n}\n\n")
    cpp.write(f"void {name}::Update()\n")
    cpp.write("{\n\t\n}\n\n")
    cpp.write("#pragma endregion")

    cpp.close()

    include = open("./../Source/Alce/Engine/Components/Components.hpp", "r")
    lines = include.readlines()
    include.close()
    include = open("./../Source/Alce/Engine/Components/Components.hpp", "w")
    include.write("")
    include.writelines(lines)
    include.write(f"\n#include \"{name}/{name}.hpp\"")
    include.close()

    prints(f"Generated -> Source/Alce/Engine/Components/{name}/{name}.hpp\n", "green")
    prints(f"Generated -> Source/Alce/Engine/Components/{name}/{name}.cpp\n", "green")

def generateScene(name):
     
    if isDir(f"./../Source/Project/Scenes/{name}"):
        error(f"A scene named \"{name}\" already exists in the project.")
        sys.exit(1)
    
    os.makedirs(f"./../Source/Project/Scenes/{name}")

    hpp = open(f"./../Source/Project/Scenes/{name}/{name}.hpp", "w")
    hpp.write("#pragma once\n\n")
    hpp.write("#include \"../../../Alce/Alce.hpp\"\n")
    hpp.write("\nusing namespace alce;\n\n")
    hpp.write(f"namespace {name}Scene\n")
    hpp.write("{\n")
    hpp.write(f"\tclass {name} : public Scene\n")
    hpp.write("\t{\n")
    hpp.write("\tpublic:\n\n")
    hpp.write(f"\t\t{name}();\n\n")
    hpp.write("\t\tvoid Init();\n\n")
    hpp.write("\t\tvoid Start();\n\n")
    hpp.write("\t};\n\n")
    hpp.write(f"\ttypedef std::shared_ptr<{name}> {name}Ptr;\n")
    hpp.write("}")
    hpp.close()

    cpp = open(f"./../Source/Project/Scenes/{name}/{name}.cpp", "w")
    cpp.write(f"#include \"{name}.hpp\"\n\n")
    cpp.write("using namespace alce;\n\n")
    cpp.write(f"{name}Scene::{name}::{name}() : Scene(\"{name}\")\n")
    cpp.write("{\n")
    cpp.write("\tDebugMode(true);\n")
    cpp.write("\tInitPhysics(Vector2(0.0f, -9.8f));\n")
    cpp.write("}\n\n")
    cpp.write("//Custom methods implementation\n")
    cpp.write("#pragma region implementation\n\n")
    cpp.write("\n#pragma endregion\n\n")
    cpp.write("//Inherited methods\n")
    cpp.write("#pragma region inherited\n\n")
    cpp.write(f"void {name}Scene::{name}::Init()\n")
    cpp.write("{\n\t\n}\n\n")
    cpp.write(f"void {name}Scene::{name}::Start()\n")
    cpp.write("{\n\t\n}\n\n")
    cpp.write("#pragma endregion")

    include = open("./../Source/Project/Scenes/Scenes.hpp", "r")
    lines = include.readlines()
    include.close()
    include = open("./../Source/Project/Scenes/Scenes.hpp", "w")
    include.writelines(lines)
    include.write(f"\n#include \"{name}/{name}.hpp\"")
    include.close()

    prints(f"Generated -> Source/Project/Scenes/{name}/{name}.hpp\n", "green")
    prints(f"Generated -> Source/Project/Scenes/{name}/{name}.cpp\n", "green")

def generateObject(scene, name):

    if not isDir(f"./../Source/Project/Scenes/{scene}"):
        error(f"There is no scene named \"{scene}\" in the project.")
        sys.exit(1)

    if isDir(f"./../Source/Project/Scenes/{scene}/{name}"):
        error(f"A game object named \"{name}\" already exists in the scene \"{scene}\"")
        sys.exit(1)
    
    os.makedirs(f"./../Source/Project/Scenes/{scene}/{name}")

    hpp = open(f"./../Source/Project/Scenes/{scene}/{name}/{name}.hpp", "w")
    hpp.write("#pragma once\n\n")
    hpp.write(f"#include \"../{scene}.hpp\"\n\n")    
    hpp.write("using namespace alce;\n\n")
    hpp.write(f"namespace {scene}Scene\n")
    hpp.write("{\n")
    hpp.write(f"\tclass {name} : public GameObject\n")
    hpp.write("\t{\n")
    hpp.write("\tpublic:\n\n")
    hpp.write(f"\t\t{name}();\n\n")
    hpp.write("\t\tvoid Init();\n\n")
    hpp.write("\t\tvoid Start();\n\n")
    hpp.write("\t\tvoid Update();\n\n")
    hpp.write("\t};\n")
    hpp.write(f"\ttypedef std::shared_ptr<{name}> {name}Ptr;\n")
    hpp.write("}")
    hpp.close()

    cpp = open(f"./../Source/Project/Scenes/{scene}/{name}/{name}.cpp", "w")
    cpp.write(f"#include \"{name}.hpp\"\n\n")
    cpp.write("using namespace alce;\n\n")
    cpp.write(f"{scene}Scene::{name}::{name}()\n")
    cpp.write("{\n\t\n}\n\n")
    cpp.write("//Custom methods implementation\n")
    cpp.write("#pragma region implementation\n\n")
    cpp.write("\n#pragma endregion\n\n")
    cpp.write("//Inherited methods\n")
    cpp.write("#pragma region inherited\n\n")
    cpp.write(f"void {scene}Scene::{name}::Init()\n")
    cpp.write("{\n\t\n}\n\n")
    cpp.write(f"void {scene}Scene::{name}::Start()\n")
    cpp.write("{\n\t\n}\n\n")
    cpp.write(f"void {scene}Scene::{name}::Update()\n")
    cpp.write("{\n\t\n}\n\n")
    cpp.write("#pragma endregion")
    cpp.close()

    include = open(f"./../Source/Project/Scenes/{scene}/{scene}.cpp", "r")
    lines = include.readlines()
    include.close()

    include = open(f"./../Source/Project/Scenes/{scene}/{scene}.cpp", "w")
    include.write("")

    for line in lines:
        include.write(line)
        if line == f"#include \"{scene}.hpp\"\n":
            include.write(f"#include \"{name}/{name}.hpp\"\n")

    include.close()
    prints(f"Generated -> Source/Project/Scenes/{scene}/{name}/{name}.hpp\n", "green")
    prints(f"Generated -> Source/Project/Scenes/{scene}/{name}/{name}.cpp\n", "green")

def generateImplementation(target_type, target_name):

    hpp_path = None
    cpp_path = None

    if target_type.lower() == "component":
        if not isDir(f"./../Source/Alce/Engine/Components/{target_name}"):
            error(f"There is no component named \"{target_name}\" in the engine.")
            sys.exit(1)
        hpp_path = f"./../Source/Alce/Engine/Components/{target_name}/{target_name}.hpp"
        cpp_path = f"./../Source/Alce/Engine/Components/{target_name}/{target_name}.cpp"

    elif target_type.lower() == "scene":
        if not isDir(f"./../Source/Project/Scenes/{target_name}"):
            error(f"There is no scene named \"{target_name}\" in the project.")
            sys.exit(1)
        hpp_path = f"./../Source/Project/Scenes/{target_name}/{target_name}.hpp"
        cpp_path = f"./../Source/Project/Scenes/{target_name}/{target_name}.cpp"

    elif target_type.lower() == "object":
        if len(target_name.split("$")) != 2:
            error(f"Invalid object name format. Use [alce generate implementation=object$<scene_name>$<object_name>]")
            sys.exit(1)
        if not isDir(f"./../Source/Project/Scenes/{target_name.split('$')[0]}/{target_name.split('$')[1]}"):
            error(f"There is no game object named \"{target_name.split('$')[1]}\" in the scene {target_name.split('$')[0]}.")
            sys.exit(1)

        hpp_path = f"./../Source/Project/Scenes/{target_name.split('$')[0]}/{target_name.split('$')[1]}/{target_name.split('$')[1]}.hpp"
        cpp_path = f"./../Source/Project/Scenes/{target_name.split('$')[0]}/{target_name.split('$')[1]}/{target_name.split('$')[1]}.cpp"
    else:
        error(f"Invalid target type \"{target_type}\".")
        sys.exit(1)    

    method_stack = []
    extra_lines = []

    hpp = open(hpp_path, "r")
    hpp_lines = hpp.readlines()
    hpp.close()

    cpp = open(cpp_path, "r")
    cpp_lines = cpp.readlines()
    cpp.close()

    add_to_stack = False

    for line in hpp_lines:
        if "//@impl" in line:
            add_to_stack = True
            extra_lines.append(line)
            continue
        
        if add_to_stack:
            line = line.replace("\t", "")
            line = line.replace("\n", "")
            line = line.replace(";", "")
            line = line.strip()
            
            method_stack.append([line.split(" ")[0], " ".join(line.split(" ")[1:])])
            add_to_stack = False
    
    impl = False

    with open(cpp_path, "w") as cpp_w:
        cpp_w.write("")
        for line in cpp_lines:
            if "#pragma region implementation" in line:
                cpp_w.writelines([line])
                impl = True
                continue
            if impl:
                for method in method_stack:
                    if target_type == "component":
                        cpp_w.writelines([
                            f"\n{method[0]} {target_name}::{method[1]}\n"
                            "{\n"
                            "\t\n"
                            "}\n"
                        ])
                    if target_type == "scene":
                        cpp_w.writelines([
                            f"\n{method[0]} {target_name}Scene::{target_name}::{method[1]}\n"
                            "{\n"
                            "\t\n"
                            "}\n"
                        ])
                    if target_type == "object":
                        cpp_w.writelines([
                            f"\n{method[0]} {target_name.split('$')[0]}Scene::{target_name.split('$')[1]}::{method[1]}\n"
                            "{\n"
                            "\t\n"
                            "}\n"
                        ])
                impl = False
            cpp_w.writelines([line])
        
    with open(hpp_path, "w") as hpp_w:
        hpp_w.write("")
        for line in hpp_lines:
            if not line in extra_lines:
                hpp_w.writelines([line])
        
def initProject():

    global project_name

    if os.path.exists("./settings.json"):
        warning("File Build/settings.json already exists, do you want to replace it? (y/n)")
        if(input().lower() != "y"):
            return
    
    is_valid = False

    while not is_valid:

        prints("\nInsert Project name: ")
        project_name = input()

        is_valid = isProjectNameValid(project_name)

        if not is_valid:
            error("Invalid project name. The project name must have more than 3 characters and less than 60 characters.")

    settings_json = open(f"./settings.json", "w")
    settings_json.write("")
    settings = {
        "compiler": {
            "bin-path": ""
        },
        "project": {
            "name": project_name,
            "icon": "Assets/alce.ico"
        }
    }
    settings_json.write(json.dumps(settings, indent=4))
    settings_json.close()
    prints("\nCreated -> Build/settings.json\n", "green")
    warning("The compiler bin path was set undefined by default.")

#endregion

#region regex functions

def isClassNameValid(name):
    keywords = set([
        'alignas', 'alignof', 'and', 'and_eq', 'asm', 'atomic_cancel', 'atomic_commit',
        'atomic_noexcept', 'bitand', 'bitor', 'bool', 'break', 'case', 'catch', 'char',
        'char8_t', 'char16_t', 'char32_t', 'class', 'compl', 'concept', 'const', 'consteval',
        'constexpr', 'const_cast', 'continue', 'co_await', 'co_return', 'co_yield', 'decltype',
        'default', 'delete', 'do', 'double', 'dynamic_cast', 'else', 'enum', 'explicit', 'export',
        'extern', 'false', 'float', 'for', 'friend', 'goto', 'if', 'import', 'inline', 'int',
        'long', 'mutable', 'namespace', 'new', 'noexcept', 'not', 'not_eq', 'nullptr', 'operator',
        'or', 'or_eq', 'private', 'protected', 'public', 'reflexpr', 'register', 'reinterpret_cast',
        'requires', 'return', 'short', 'signed', 'sizeof', 'static', 'static_assert', 'static_cast',
        'struct', 'switch', 'synchronized', 'template', 'this', 'thread_local', 'throw', 'true',
        'try', 'typedef', 'typeid', 'typename', 'union', 'unsigned', 'using', 'virtual', 'void',
        'volatile', 'wchar_t', 'while', 'xor', 'xor_eq'
    ])

    pattern = re.compile(r'^[a-zA-Z_]\w*$')

    return bool(pattern.match(name)) and name not in keywords

def isAliasValid(alias):
    pattern = re.compile(r'^[a-zA-Z_]\w*$')
    return bool(pattern.match(alias))

def isProjectNameValid(name):
    if len(name) > 3 and len(name) < 60:
        return True
    else:
        return False

#endregion

#region compile functions

def initCompile():

    global cpp_files, hpp_files, compile_stack, build_express

    #region Step 1: Check if needed folders exist

    if not os.path.exists("./Objects"):
        os.makedirs("./Objects")

    if not os.path.exists("./Tracking"):
        os.makedirs("./Tracking")
    
    if not os.path.exists("./Temp"):
        os.makedirs("./Temp")

    #endregion

    #region Step 2: Get source files

    c = 0
    cpp_files = glob.glob("./../Source/**/*.cpp", recursive=True)

    for i in cpp_files:
        cpp_files[c] = i.replace("\\", "/")
        c += 1

    c = 0
    hpp_files = glob.glob("./../Source/**/*.hpp", recursive=True)

    for i in hpp_files:
        hpp_files[c] = i.replace("\\", "/")
        c += 1

    #endregion

    #region Step 3: Check if tracking files exist

    if not os.path.exists("./Tracking/hpp_tracking.txt"):
        hpp_tracking_file = open("./Tracking/hpp_tracking.txt", "w")

        for hpp in hpp_files:
            mtime = os.path.getmtime(hpp)
            hpp_tracking_file.write(hpp + ":" + mtime.__str__() + "\n")
        
        hpp_tracking_file.close()

    if not os.path.exists("./Tracking/cpp_tracking.txt"):
        cpp_tracking_file = open("./Tracking/cpp_tracking.txt", "w")

        for cpp in cpp_files:
            mtime = os.path.getmtime(cpp)
            cpp_tracking_file.write(cpp + ":" + mtime.__str__() + "\n")
        
        cpp_tracking_file.close()

    #endregion

    #region Step 4: Prepare the compile stack

    if build_express:
        for hpp in hpp_files:
            if wasModified(hpp):
                for cpp in cpp_files:
                    if cpp.split("/")[-1].split(".")[0] == hpp.split("/")[-1].split(".")[0]:
                        compile_stack.append(cpp)
                        addToTrack(hpp)

        for cpp in cpp_files:
            if wasModified(cpp):
                compile_stack.append(cpp)
                addToTrack(cpp)
    else:

        for cpp in cpp_files:
            compile_stack.append(cpp)

    #endregion

def build():

    if len(compile_stack) == 0:
        return True

    makefile = open("Temp/Makefile", "w")
    makefile.write("all:\n")

    for file in compile_stack:
        makefile.write("\tg++ -std=c++2a -ISFML-2.6.1/include -c " + file + " -o ./Objects/" + file.split("/")[-1].replace("cpp", "o") + "\n")

    makefile.close()

    if os.system("mingw32-make -f Temp/Makefile") != 0:
        os.remove("Temp/Makefile")
        return False
    else:
        os.remove("Temp/Makefile")
        return True
    
def createIcon():

    if not os.path.exists(project_icon):
        error(f"Project icon path \"{project_icon}\" is invalid")
        return False

    rc_file_content = f"IDI_ICON1 ICON \"{project_icon}\""
    rc_file_path = "Temp/icon.rc"

    with open(rc_file_path, "w") as rc_file:
        rc_file.write(rc_file_content)
    
    try:
        os.system(f"windres {rc_file_path} -O coff -o Temp/icon.res")
    except Exception as ex:
        error(f"{ex}")
        return False

    try:
        os.remove(rc_file_path)
    except Exception as ex:
        error(f"{ex}")
        return False

    return True

def link(alias):

    if not os.path.exists("./Out/" + alias):
        os.makedirs("./Out/" + alias)

    makefile = open("Temp/Makefile", "w")
    makefile.write("all:\n")

    o_files = glob.glob("./Objects/*.o")
    c = 0

    for o in o_files:
        o_files[c] = o.replace("\\", "/")
        c += 1
    
    makefile.write("\tg++ ")

    for o in o_files:
        makefile.write(o + " ")
    
    if createIcon():
        makefile.write("Temp/icon.res")
    
    makefile.write(" -o " + "./Out/" + alias + "/" + project_name + " -LSFML-2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio ")

    if build_mode == "release":
        makefile.write("-mwindows ")
    
    makefile.close()

    if os.system("mingw32-make -f Temp/Makefile") != 0:
        os.remove("Makefile")
        return False
    else:

        if os.path.exists("./Out/" + alias + "/Assets"):
            shutil.rmtree("./Out/" + alias + "/Assets")
        
        shutil.copytree("./Assets", os.path.join("./Out/" + alias, "Assets"))

        sfml_dlls = glob.glob("./SFML-2.6.1/bin/*.dll")

        for dll in sfml_dlls:
            shutil.copy(dll, "./Out/" + alias)
        
        compiler_dlls = glob.glob(f"{compiler_bin_path}/*.dll")

        for dll in compiler_dlls:
            shutil.copy(dll, "./Out/" + alias)

        if os.path.exists("Temp/icon.res"):
            os.remove("Temp/icon.res")

        os.remove("Temp/Makefile")
        return True

#endregion

#region run functions

def run(alias, mode):

    if not isDir("./Out"):
        error("Build/Out folder is missing. Use [alce compile] to generate it")
        sys.exit(1)
    
    if not isDir(f"./Out/{alias}"):
        error(f"There is no build with the alias \"{alias}\" in this project.")
        sys.exit(1)

    if mode == "debug":
        subprocess.run(["gdb", f"./Out/{alias}/{project_name}.exe"])
    if mode == "standard":
        subprocess.run(f"./Out/{alias}/{project_name}.exe")

#endregion

def readSettings():

    global compiler_bin_path
    global project_name, project_icon
    global build_mode, build_express, build_alias

    with open("./settings.json", "r") as build_settings:

        data = json.load(build_settings)
        
        #region compiler settings

        compiler = data.get("compiler", None)

        if compiler is None:
            error("Compiler settings are missing at [Build/settings.json -> compiler]")
            return
        else:
            compiler_bin_path = compiler.get("bin-path", None)

            if compiler_bin_path is None:
                error("Compiler bin path is missing at [Build/settings.json -> compiler::bin-path]")
                return
            else:
                if not isDir(compiler_bin_path):
                    error(f"Invalid path {compiler_bin_path} at [Build/settings.json -> compiler::bin-path]")
                    return

        #endregion

        #region project settings

        project = data.get("project", None)

        if project is None:
           warning("Using default project settings")
        else:
            project_name = project.get("name")

            if project_name is None:
                project_name = "Alce-Project"
                warning(f"Using {project_name} as project name by default")
            
            project_icon = project.get("icon")

        #endregion

if __name__ == '__main__':

    arguments = dict(enumerate(sys.argv[1:], start = 1))

    if arguments.__len__() == 1:
        if arguments[1] == "init" or arguments[1] == "i":
            initProject()
            sys.exit(0)

    if not os.path.exists("./settings.json"):
        prints("This project is not initialized, would you like to create the default configuration? (y/n)\n", "green")
        if input().lower() == "y":
            initProject()
        else:
            sys.exit(0)
    
    readSettings()
    argument_stack = []
   
    for i, arg in enumerate(sys.argv[1:], start = 1):
        argument_stack.append(f"{i}:{arg}")

    tasks = handleArguments(argument_stack)

    for task in tasks:

        if task.split(" ")[0] == "compile":
            if task.split(" ")[-1] == "0":
                error("Undefined alias. Use [alce compile --help] for more info.")
                sys.exit(1)
            
            alias = task.split(" ")[-1]

            initCompile()
            if build():
                link(alias)
        
        if task.split(" ")[0] == "run":
            if task.split(" ")[1] == "0":
                error("Undefined alias. Use [alce run --help] for more info.")
                sys.exit(1)
            
            alias = task.split(" ")[1]
            mode = task.split(" ")[2]
            run(alias, mode)
        
        if task.split(" ")[0] == "generate":    
            if task.split(" ")[1] == "0":
                error("Undefined generation. Use [alce generate --help] for more info.")
                sys.exit(1)

            generation_type = task.split(" ")[1]

            if generation_type == "component":
                component_name = task.split(" ")[-1]
                generateComponent(component_name)

            elif generation_type == "scene":
                scene_name = task.split(" ")[-1]
                generateScene(scene_name)

            elif generation_type == "object":
                scene_name = task.split(" ")[-1].split("@")[0]
                object_name = task.split(" ")[-1].split("@")[1]
                generateObject(scene_name, object_name)

            elif generation_type == "implementation":
                target_type = task.split(" ")[-1].split("@")[0]
                target_name = "@".join(task.split(" ")[-1].split("@")[1:])
                generateImplementation(target_type, target_name)
