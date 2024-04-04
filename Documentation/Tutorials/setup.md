# Alce Engine Environment Setup Tutorial

### Table of Contents

1. [Prerequisites](#prerequisites)
2. [Compiler Setup](#step-1-compiler-setup)
3. [Download Alce Engine](#step-2-download-alce-engine)

# Prerequisites

Before proceeding, you must meet the following requirements to complete this tutorial:

* Operating System: Windows 10-11; we do not provide support for earlier versions.

As of now, Alce Engine is primarily focused on the Windows environment. However, we intend to expand the engine's usage to Mac and Linux platforms in the future.

# Step 1: Compiler Setup

In order to compile the project along with the Alce Engine CLI, you'll need the GCC 13.1.0 MinGW 32-bit compiler. There are several ways to install it, but in this tutorial, we'll use MSYS2, as this tool greatly simplifies the process.

Start by installing MSYS2 following the instructions on its [website](https://www.msys2.org/). Once the program is installed, launch it and run the following command within the integrated terminal:

```bash
$ pacman -S mingw-w64-i686-toolchain
```

After the installation is complete, navigate to your local folder "<i>C:\msys64</i>" and locate the mingw32 folder and its subfolder bin. Ensure it's not empty and contains the following files:

```bash
C:/msys64
    |-> mingw32
    |    |-> bin
    |    |    |-> (...)
    |    |    |-> g++.exe
    |    |    |-> gdb.exe
    |    |    |-> mingw32-make.exe
```

Copy the path of the folder "<i>C:\msys64\mingw32\bin</i>" and open the system variable editor.

The easiest way to do this is by typing "environment variable" into your Windows Search bar and clicking “Edit the system environment variables.”

<img src="./../resources/setup/setup_1.png" width="450px">

Once you’re in the “Advanced” tab, click on “Environment Variables...”

<img src="./../resources/setup/setup_2.png" width="450px">

In the "System Variables" section, select the "Path" variable and click "Edit."

<img src="./../resources/setup/setup_3.png" width="450px">

A new tab will open, click on "New" and paste the path.

<img src="./../resources/setup/setup_4.png" width="450px"> 

Once the changes are saved, open a new terminal (if you had one open before the previous process, close it as it may not yet recognize the commands) and run the following commands to verify the correct installation of the compiler:

```bash
g++ --version
mingw32-make --version
gdb --version
```

If you didn't receive an error message indicating that the command is not recognized in all three commands, congratulations, you have successfully installed the compiler. The toughest part of this tutorial is now behind you! :smile:

# Step 2: Download Alce Engine

Once the compiler is installed, everything is ready to start using the engine.

However, it's crucial to understand before moving forward: Alce Engine isn't a traditional installable software. Instead, to develop projects with this engine, you must obtain the source code from its repository by cloning or downloading it. This repository contains not only the source code but also the necessary compilation tools. This approach offers flexibility and streamlines the compilation process. Unlike traditional methods using CMake, Alce Engine utilizes a custom CLI programmed in Python specifically tailored to handle compilation and project building, enhancing usability to the fullest extent possible.

Having direct access to the engine's source code allows users the freedom to modify it according to their preferences, adding components, or even expanding its core functionality. While this decision may slightly increase compilation time for larger projects, it significantly reduces common linking issues often encountered in C++ development.

Now that we understand this, let's proceed to download the engine's repository. If you have Git installed, simply clone the repository using the following command:

```bash
git clone https://github.com/gabrielbeguren/AlceEngine
```

If, on the other hand, you don't have Git installed (though we highly recommend it), you can also download the source code as a zip file from the GitHub interface.

<img src="./../resources/setup/setup_5.png">
