# Alce Command Line Interface

### Table of Contents

1. [Introduction](#Introduction)
2. [Requirements](#Requirements)
3. [How to Use](#how-to-use)
   - [alce init](#alce-init)
   - [alce compile](#alce-compile)
   - [alce run](#alce-run)
   - [alce generate](#alce-generate)
4. [alce init](#alce-init)
5. [alce compile](#alce-compile)
6. [alce run](#alce-run)
7. [alce generate](#alce-generate)
   - [Generate Component](#generate-component)
   - [Generate Scene](#generate-scene)
   - [Generate Object](#generate-object)
   - [Generate Implementation](#generate-implementation)

# Introduction


The Alce Command Line Interface (CLI) facilitates the construction and administration of Alce projects directly from a command shell. 

It offers essential functionalities tailored for seamless project development and management, empowering users to efficiently handle various tasks associated with Alce projects within a command-line environment.

# Requirements

* Windows 10, 11 (64/32bit)
* GCC v13.1.0^

Optional:

* Python v3.1.0^ (if you want to execute the source code)

# How to Use 

To utilize the CLI, navigate to the <ins>./Build</ins> directory within your project context.

```bash
cd ./Build
```

Within this directory, you'll find 2 folders:

* <ins>Assets</ins>: This folder serves as the asset repository for your project, where you should store all game resources.

* <ins>SFML-2.6.1</ins>: This directory contains SFML stuff. Do not delete this folder.

Additionally, there are 3 files:

* <ins>cli.py</ins>: This file contains the source code for the CLI. You have full freedom to modify it. To use it instead of the official executable, replace the "./Build/alce" command with "python3 cli.py".

* <ins>settings.json</ins>: This file holds essential project data such as name, icon, and the current compiler binary path (which is undefined by default but may be necessary for certain CLI commands).

* <ins>alce.exe</ins>: This file is the official executable for the CLI.

# <ins>alce init</ins>

### Command Syntax
```bash
./Build/alce [init, i]
```

Creates the required configuration file "<ins>Build/Settings.json</ins>" with the next fields:

* __Compiler__:
  * __"bin-path"__: the bin path of the MinGW32 compiler.
* __Project__:
  * __"name"__: Name of the current project.
  * __"icon"__: .ico file for the executable.

# <ins>alce compile</ins>

### Command Syntax
```bash
./Build/alce [compile, c] [alias, a]=<alias_name> [mode, m]=<development|release> [--full, -f]|[--express, -e]
```

Compiles the project using an alias name. 

### Compilation Method

There are two compilation methods available:

* <ins>__Full Compilation__</ins>: This method includes all files inside the <ins>./Source</ins> folder in the compilation queue. It is recommended for releases and major tests.
  
* <ins>__Express Compilation__</ins>: This method only includes the last modified files inside the <ins>./Source</ins> folder in the compilation queue. It is recommended for minor changes and quick adjustments.

Once compilation succeeded, output files are generated inside the <ins>./Build/Out</ins> folder, following the next scheme:

```bash
Build
  |-> Out
  |    |-> alias_name
  |    |     |-> Assets 
  |    |     |  alias_name.exe
  |    |     |  (.dll files)
  |  alce.exe
```

__Note__: The use of express compilation does not involve the compilation of affected files; it solely adds modified files to the compilation queue.

### Build Mode

There are two build modes available:

* <ins>__Development__</ins>: In this mode, the project execution will be accompanied by a debugging console.
* <ins>__Release__</ins>: In this mode, the project execution will be clean and free of debugging information.

### Default values:

* __Compilation method:__ <i>--full</i>
* __Build Mode:__ <i>mode=development</i>

### Usage Examples

> Compile the project using default values:

```bash
./Build/alce compile alias=<your_project_alias> 
./Build/alce c a=<your_project_alias>
```

> Compile the project using the express method:

```bash
./Build/alce compile alias=<your_project_alias> --express
./Build/alce c a=<your_project_alias> -e
```

> Compile the project using the full method:

```bash
./Build/alce compile alias=<your_project_alias> --full
./Build/alce c a=<your_project_alias> -f
```

> Compile the project using the full method as a release:

```bash
./Build/alce compile alias=<your_project_alias> mode=release --full
./Build/alce c a=<your_project_alias> m=release -f
```

> Compile the project in development mode:

```bash
./Build/alce compile alias=<your_project_alias> mode=development
./Build/alce c a=<your_project_alias> m=development
```

# <ins>alce run</ins>

### Command Syntax

```bash
./Build/alce [run, r] [alias, a]=<your_project_alias> [--standard, -std]|[--debug, -d]
```

Runs the project by alias name.

### Run Mode

There are two run modes available:

* <ins>__Standard Mode__</ins>: Runs the project as a standard application.
* <ins>__Debug Mode__</ins>: Runs the project with GDB, the GNU project debugger.

__Note__: the use of <i>--debug</i> mode could affect the performance of the project.

### Default Values:

* __Run Mode:__ <i>--standard</i>

### Usage Examples

> Run the project by alias name using default values

```bash
./Build/alce run alias=<your_project_alias>
./Build/alce r a=<your_project_alias>
```

> Run the project by alias name using the GDB debugger

```bash
./Build/alce run alias=<your_project_alias> --debug
./BUild/alce r a=<your_project_alias> -d
```

> Run the project by alias name as a standard application

```bash
./Build/alce run alias=<your_project_alias> --standard
./Build/alce r a=<your_project_alias> -std
```

# <ins>alce generate</ins>

Generates various entities within the project context, streamlining development processes.

<h2>Generate Component</h2>

### Command Syntax

```bash
./Build/alce generate component=<ComponentName>
./Build/alce g c=<ComponentName>
```

Creates a new component within the designated directory structure.

### File Structure

```bash
Source
  |-> Alce
  |    |-> Engine
  |    |     |-> Components
  |    |     |     |-> (New Component)
```

<h2>Generate Scene</h2> 

### Command Syntax

```bash
./Build/alce generate scene=<SceneName>
./Build/alce g s=<SceneName>
```

Creates a new scene within the specified directory structure.

### File Structure

```bash
Source
  |-> Project
  |    |-> Scenes
  |    |     |-> (New Scene)
```
<h2>Generate Object</h2> 

### Command Syntax

```bash
./Build/alce generate object=<SceneName>@<ObjectName>
./Build/alce g o=<SceneName>@<ObjectName>
```

Generates a new game object within a designated scene.

### File Structure

```bash
Source
  |-> Project
  |    |-> Scenes
  |    |     |-> (Scene)
  |    |     |     |-> (New Game Object)
```

<h2>Generate Implementation</h2> 

Generates the implementation of declarations within a .hpp file. Placing a comment <ins>//@impl</ins> above a declaration in the .hpp file triggers the creation of the basic structure within the corresponding .cpp file's implementation region, expediting the development process.

For instance, given the declaration in the .hpp file:

```cpp
class Particle
{
  //@impl
  void SetDensity(float density);
};
```
The following structure will be generated in the respective .cpp file within the implementation region:

```cpp
#pragma region implementation

  void Particle::SetDensity(float density)
  {
    
  }

#pragma endregion
```

