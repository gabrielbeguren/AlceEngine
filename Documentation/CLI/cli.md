# Alce Command Line Interface (CLI)

Alce Command Line Interface (CLI) provides functionality commands for building and managing Alce projects.

## <ins>Compilation Command</ins>

This command initiates a compilation of the project using an alias name. There are two compilation methods available for building the project:

* <u><ins>Full Compilation</ins></u>: This method includes all files inside the <u>./Source</u> folder in the compilation queue. It is recommended for releases and major tests.
  
* <u>__Express Compilation__</u>: This method only includes the last modified files inside the <u>./Source</u> folder in the compilation queue. It is recommended for minor changes and quick adjustments.

<u>By default, full compilation will be the chosen compilation method</u>.

Once compilation succeded, output files will be generated inside the <u>./Build/Out</u> folder, following the next scheme:

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

> Project compilation using default values:

```bash
./Build/alce --compile --alias=your_project_alias 
./Build/alce -c -a=your_project_alias
```

> Project express compilation

```bash
./Build/alce --compile --alias=your_project_alias --express
./Build/alce -c -a=your_project_alias -e
```

> Project full compilation

```bash
./Build/alce --compile --alias=your_project_alias --full
./Build/alce -c -a=your_project_alias -f
```

## <u>Run Command</u>


## <u>Generation Command</u>



