# Alce Command Line Interface (CLI)

The Alce Command Line Interface (CLI) provides functionality for building and managing Alce projects directly from a command shell.

## <ins>Requirements</ins>

* Windows 10, 11 (64/32bit)
* GCC v13.1.0^

## <ins>alce init</ins>

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

## <ins>alce compile</ins>

### Command Syntax
```bash
./Build/alce [compile, c] [alias, a]=<alias_name> [mode, m]=<development|release> [--full, -f]|[--express, -e]
```

Compiles the project using an alias name. 

### Compilation Method

There are two compilation methods available:

* <ins>__Full Compilation__</ins>: This method includes all files inside the <ins>./Source</ins> folder in the compilation queue. It is recommended for releases and major tests.
  
* <ins>__Express Compilation__</ins>: This method only includes the last modified files inside the <ins>./Source</ins> folder in the compilation queue. It is recommended for minor changes and quick adjustments.

Once compilation succeded, output files will be generated inside the <ins>./Build/Out</ins> folder, following the next scheme:

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

## <ins>alce run</ins>

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

## <ins>alce generate</ins>

### Command Syntax

```bash
./Build/alce [generate, g] [component, c]=<component_name>|[scene, s]=<scene_name>|[object, o]=<scene_name>@<object_name>|[implementation, i]=<<object@scene_name@object_name>|<scene@scene_name>|<component@component_name>>
```

Generates and/or modifies files based on a schematic.

### Generation Types:

* __Component:__
* __Scene:__
* __Object:__
