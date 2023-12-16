# Alce Command Line Interface (CLI)

The Alce Command Line Interface (CLI) provides functionality for building and managing Alce projects directly from a command shell.

## <ins>Requirements</ins>

* Windows 10, 11 (64/32bit)
* GCC v13.1.0^

## <ins>Compilation Command</ins>

Initiates the compilation of a project using an alias name. There are two compilation methods available for building the project:

* <ins>__Full Compilation__</ins>: This method includes all files inside the <ins>./Source</ins> folder in the compilation queue. It is recommended for releases and major tests.
  
* <ins>__Express Compilation__</ins>: This method only includes the last modified files inside the <ins>./Source</ins> folder in the compilation queue. It is recommended for minor changes and quick adjustments.

__By default, full compilation will be the chosen method.__

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

#### Command Syntax
```bash
./Build/alce [--compile, -c] [--alias, -a]=alias_name [--full, -f]|[--express, -e]
```

#### Usage Examples

> Compile the project using default values:

```bash
./Build/alce --compile --alias=your_project_alias 
./Build/alce -c -a=your_project_alias
```

> Compile the project using the express method:

```bash
./Build/alce --compile --alias=your_project_alias --express
./Build/alce -c -a=your_project_alias -e
```

> Compile the project using the full method:

```bash
./Build/alce --compile --alias=your_project_alias --full
./Build/alce -c -a=your_project_alias -f
```

## <ins>Run Command</ins>


## <ins>Generation Command</ins>



