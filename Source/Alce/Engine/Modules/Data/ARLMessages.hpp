#pragma once

#include "../String/String.hpp"

#define ARLM ARLMessages::Instance()

namespace alce
{
    class ARLMessages
    {
    public:

        static ARLMessages& Instance()
		{
			static ARLMessages arlpm;
			return arlpm;
		}

    private:
        friend class ARL_PROCESSOR;

    String help = R"(
Commands can be executed un group using semicolons as separators:

For example "system;window;" will execute first the order "system" and then "window".

You can also write comments, just like in other languages, there are 2 ways to do so:
* Single line comments with "//" or "#".
* Multiple line comments with "/* */".

- Example:
```
/*
This is an example of an ARL Script 
with comments
*/

window; //Display window data
screen; //Display screen data
system; //Display system data
standby off; //Set "stand by" field as off 

#Now set current scene as "mainScene"
change to mainScene;
```
---

2. Basic Commands

[system]
- Description: Displays System Data.

[window]
- Description: Displays window data.

[screen]
- Description: Displays screen data.

[stop]
- Description: Stops reading inputs and disables the physics simulation.

[play]
- Description: Starts reading again inputs and enables the physics simulation.

[help]
- Description: Displays help for a subcommand.
- Syntax: help <subcommand>;
- Example:
  ```help system;```

[standby]
- Description: Configures standby mode with an option.
- Syntax: standby <option>;
- Example:
  ```standby on;```

[grid scale]
- Description: Sets the grid scale with a float value.
- Syntax: grid scale <value>;
- Example:
  ```grid scale 2.5;```

[grid size]
- Description: Sets the grid size with a float value.
- Syntax: grid size <value>;
- Example:
  ```grid size 10;```

[change to]
- Description: Changes the current scene to the specified one.
- Syntax: change to <scene>;
- Example:
  ```change to SceneA;```

[add object]
- Description: Adds an object with a class name and alias.
- Syntax: add object <className> as <alias>;
- Example:
  ```add object Player as mainCharacter;```

[add component]
- Description: Adds a component with a class name to an alias.
- Syntax: add component <className> to <alias>;
- Example:
  ```add component Physics to Player;```

[delete object]
- Description: Deletes an object by its alias.
- Syntax: delete object <alias>;
- Example:
  ```delete object mainCharacter;```

[delete component]
- Description: Deletes an alias' component by class name.
- Syntax: delete component <className> of <alias>;
- Example:
```delete component Rigidbody2d of Player;```

[enable object]
- Description: Enables an object by its alias.
- Syntax: enable object <alias>;
- Example:
  ```enable object mainCharacter;```

[enable component]
- Description: Enables an alias' component by class name.
- Syntax: enable component <className> of <alias>;
- Example:
```enable component SpriteRenderer of Player;```

[disable object]
- Description: Disables an object by its alias.
- Syntax: disable object <alias>;
- Example:
  ```disable object mainCharacter;```

[disable component]
- Description: Disables an alias' component by class name.
- Syntax: disable component <className> of <alias>;
- Example:
```disable component SpriteRenderer of Player;```

[set object]
- Description: Sets a field of an object to a value.
- Syntax: set object <alias> <field> as "<value>";
- Example:
  ```set object Player speed as "10";```

[set component]
- Description: Sets a field of a component to a value.
- Syntax: set component <className> <field> as "<value>";
- Example:
```set component SpriteRenderer transform.rotation of Player as "13";```
)";
        
    String helpSystem = R"(
[system]
- Description: Displays System Data.)";

    String helpWindow = R"(
[window]
- Description: Displays window data.)";

    String helpScreen = R"(
[screen]
- Description: Displays screen data.)";

    String helpStop = R"(
[stop]
- Description: Stops reading inputs and disables the physics simulation.)";

    String helpPlay = R"(
[play]
- Description: Starts reading again inputs and enables the physics simulation.)";

    String helpHelp = R"(
[help]
- Description: Displays help for a subcommand.
- Syntax: help <subcommand>;
- Example:
  ```help system;```)";

    String helpStandby = R"(
[standby]
- Description: Configures standby mode with an option.
- Syntax: standby <option>;
- Example:
  ```standby on;```)";

    String helpGridScale = R"(
[grid scale]
- Description: Sets the grid scale with a float value.
- Syntax: grid scale <value>;
- Example:
  ```grid scale 2.5;```)";

    String helpGridSize = R"(
[grid size]
- Description: Sets the grid size with a float value.
- Syntax: grid size <value>;
- Example:
  ```grid size 10;```)";

    String helpChangeTo = R"(
[change to]
- Description: Changes the current scene to the specified one.
- Syntax: change to <scene>;
- Example:
  ```change to SceneA;```)";

    String helpAddObject = R"(
[add object]
- Description: Adds an object with a class name and alias.
- Syntax: add object <className> as <alias>;
- Example:
  ```add object Player as mainCharacter;```)";

    String helpAddComponent = R"(
[add component]
- Description: Adds a component with a class name to an alias.
- Syntax: add component <className> to <alias>;
- Example:
  ```add component Physics to Player;```)";

    String helpDeleteObject = R"(
[delete object]
- Description: Deletes an object by its alias.
- Syntax: delete object <alias>;
- Example:
  ```delete object mainCharacter;```)";

    String helpDeleteComponent = R"(
[delete component]
- Description: Deletes an alias' component by class name.
- Syntax: delete component <className> of <alias>;
- Example:
```delete component Rigidbody2d of Player;```)";

    String helpEnableObject = R"(
[enable object]
- Description: Enables an object by its alias.
- Syntax: enable object <alias>;
- Example:
  ```enable object mainCharacter;```)";

    String helpEnableComponent = R"(
[enable component]
- Description: Enables an alias' component by class name.
- Syntax: enable component <className> of <alias>
- Example:
```enable component SpriteRenderer of Player;```)";

    String helpDisableObject = R"(
[disable object]
- Description: Disables an object by its alias.
- Syntax: disable object <alias>;
- Example:
  ```disable object mainCharacter;```)";

    String helpDisableComponent = R"(
[disable component]
- Description: Disables an alias' component by class name.
- Syntax: disable component <className> of <alias>;
- Example:
```disable component SpriteRenderer of Player;```)";

    String helpSetObject = R"(
[set object]
- Description: Sets a field of an object to a value.
- Syntax: set object <alias> <field> as "<value>";
- Example:
  ```set object Player speed as 10;```)";

    String helpSetComponent = R"(
[set component]
- Description: Sets a field of a component to a value.
- Syntax: set component <className> <field> as "<value>";
- Example:
```set component SpriteRenderer transform.rotation of Player as "13";```)";
    };
}