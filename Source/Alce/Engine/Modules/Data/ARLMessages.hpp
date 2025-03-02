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
      static ARLMessages arlm;
      return arlm;
    }

  private:

      friend class ARL_PROCESSOR;
        
String helpSystem = R"(
[system]
- Description: Displays system information, including OS, CPU, GPU, RAM, and DirectX version
)";

String helpWindow = R"(
[window]
- Description: Displays window data.
)";

String helpScreen = R"(
[screen]
- Description: Displays screen data.
)";

String helpStop = R"(
[stop]
- Description: Stops reading inputs and disables the physics simulation.
)";

String helpPlay = R"(
[play]
- Description: Starts reading again inputs and enables the physics simulation.
)";

String helpScene = R"(
[scene]
- Description: Displays the name of the current scene.
)";

String helpGrid = R"(
[grid]
- Description: Sets the grid scale with a float value.
- Syntax: grid scale <value>;
- Example:
    grid scale 2.5;
)";

String helpStandby = R"(
[standby]
  - Description: Enables or disables standby mode.
  - Syntax: standby <on|off>;
  - Example:
      standby on;
)";

String helpChange = R"(
[change]
  - Description: Changes the current scene to the specified one.
  - Syntax: change to <scene>;
  - Example:
      change to MyScene;
)";

String helpAdd = R"(
[add]
  - Description: Creates an object using a factory creator and assigns it an alias.
  - Syntax: add object <creator> <alias>;
  - Example:
      add Player mainCharacter;
)";

String helpDelete = R"(
[delete]
  - Description: Removes an object from the scene.
  - Syntax: delete object <alias>;
  - Example:
    delete object mainCharacter;
)";

String helpEnable = R"(
[enable]
  - Description: Enables an object or component.
  - Syntax: 
      enable object <alias>;
      enable component <component_id> from <alias>;
  - Example:
      enable object mainCharacter;
      enable component SpriteRenderer from mainCharacter;
)";
  
String helpDisable = R"(
[disable]
  - Description: Disables an object or component.
  - Syntax: 
      disable object <alias>;
      disable component <component_id> from <alias>;
  - Example:
      disable object mainCharacter;
      disable component SpriteRenderer from mainCharacter;
)";
  
String helpSet = R"(
[set]
  - Description: Modifies an object's property.
  - Syntax: set <alias> <field> <value>;
  - Example:
        set Player speed 10;
)";

String helpGet = R"(
[get]
  - Description: Retrieves the value of an object's property.
  - Syntax: get <alias> <field>;
  - Example:
        get Player speed;
)";

String helpList = R"(
[list]
  - Description: Lists all game objects in the current scene.
)";

String helpHas = R"(
[has]
  - Description: Checks if an object exists in the scene. Returns "True" or "False".
  - Syntax: has <alias>;
)";
  
  };
}