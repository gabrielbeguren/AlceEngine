<p align="center">
<img src="./Build/Assets/logo.png">
</p>

<h1 align="center">Alce Game Engine</h1>

<p align="center">
<img src="https://img.shields.io/badge/C++-20-00599C?style=flat-square&logo=c%2B%2B">
<img src="https://img.shields.io/badge/SFML-v2.6.1-8CC445?logo=SFML&style=flat-square">
<a href="LICENSE"><img src="https://img.shields.io/badge/license-MIT-informational?style=flat-square"/></a>
</p>

Alce Game Engine is a feature-rich game engine based on SFML and Box2D, designed to simplify the development of 2D games. Its primary goal is to provide a comprehensive suite of tools and components that streamline the creation process—from physics simulations and animations to user interface management and local storage.

# News and Updates

### > (03/03/2025) Release: Alce Runtime Language (ARL)

A lightweight, human-readable command language designed for dynamic scene development and modification during runtime. It allows you to make real-time changes without the need for recompilation, streamlining iterative workflows in applications such as game development or interactive simulations.
 
Just write your prompts in the console while the game is running!

[ARL Documentation](Documentation/ARL/ARL.md)


# Features

* Components:
    * [Animation2d](Source/Alce/Engine/Components/Animation2d/)
    * [Camera](Source/Alce/Engine/Components/Camera/)
    * [ParticleSystem](Source/Alce/Engine/Components/ParticleSystem/)
    * [Raycast2d](Source/Alce/Engine/Components/Raycast2d/)
    * [Rigidbody2d](Source/Alce/Engine/Components/Rigidbody2d/)
    * [SpriteRenderer](Source/Alce/Engine/Components/SpriteRenderer/)

* UIElements (User Interface):
    * [Button](Source/Alce/Engine/UI/Button/)
    * [Image](Source/Alce/Engine/UI/Image/)
    * [Text](Source/Alce/Engine/UI/Text/)
    * [TextInput](Source/Alce/Engine/UI/TextInput/)

* Core Modules:
    * [Kernel](Source/Alce/Engine/Core/Kernel/): engine's core module.
    * [Audio](Source/Alce/Engine/Core/Audio/): shared audio management module.
    * [Storage](Source/Alce/Engine/Core/Storage): LocalStorage-like management module.
    * [Chrono](Source/Alce/Engine/Core/Chrono/): time handling module.
    * [Debug](Source/Alce/Engine/Core/Debug/): log/tracking module.
    * [Input](Source/Alce/Engine/Core/Input/): keyboard/mouse input management module.
    * [Math](Source/Alce/Engine/Core/Math/): math engine module.
* Utils:
    * [Collections](Source/Alce/Engine/Core/Collections/): Custom Dictionary and List data structures.
    * [String](Source/Alce/Engine/Core/String/): sf::String Wrapper Class.
    * [Json](Source/Alce/Engine/Core/Json/): easy-to-use rapidjson's wrapper class.
    * [FileSystem](Source/Alce/Engine/Core/FileSystem/): file and folder management classes.
* [Alce CLI](Documentation/CLI/cli.md)

# Setup

Learn how to set up Alce Engine with ease through [this tutorial](./Documentation/Tutorials/setup.md).

### Requirements

Minimun requirements:
* GCC 32bit v13.1.0^ (g++, mingw32-make, gdb)
* Windows 10, 11

Recommended:
* Python v3.1.0^

# Contact

For any professional inquiries, please contact me at gabrielbeguren@outlook.com. If you wish to contribute ideas or report any bugs, feel free to use the tools that GitHub provides.

# External Libraries used by Alce Engine

* <img src="https://www.sfml-dev.org/images/favicon.ico" style="width: 18px; position: relative; top: 2px"> [SFML](https://github.com/SFML/SFML) under the [ZLIB license](https://github.com/SFML/SFML?tab=Zlib-1-ov-file#readme)
* <img src="https://box2d.org/images/logo.svg" style="width: 23px; position: relative; top: 1px"> [Box2d](https://github.com/erincatto/box2d) under the [MIT license](https://github.com/erincatto/box2d?tab=MIT-1-ov-file#readme)
* <img src="https://raw.githubusercontent.com/MiguelMJ/Candle/master/doc/logo.svg" style="width: 19px; position: relative; top: 2px"> [Candle](https://github.com/MiguelMJ/Candle) under the [MIT license](https://github.com/MiguelMJ/Candle?tab=MIT-1-ov-file#readme)
* <img src="https://github.com/fluidicon.png" style="width: 20px; position: relative; top: 3px"> [RichText](https://github.com/skyrpex/RichText) under [public domain](https://github.com/skyrpex/RichText?tab=License-1-ov-file#readme)
* <img src="https://raw.githubusercontent.com/Tencent/rapidjson/master/doc/logo/rapidjson.png" style="width: 60px; position: relative; top: 3px"> [rapidjson](https://github.com/Tencent/rapidjson) under the [MIT license](https://github.com/Tencent/rapidjson?tab=License-1-ov-file#readme)
