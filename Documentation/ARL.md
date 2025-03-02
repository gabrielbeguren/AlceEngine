# Alce Runtime Language (ARL) Usage Guide

ARL is a lightweight, human-readable command language designed for dynamic scene development and modification during runtime. It allows you to make real-time changes without the need for recompilation, streamlining iterative workflows in applications such as game development or interactive simulations.

---
## 1. Syntax

Commands can be executed un group using semicolons as separators:

For example ```system;window;``` will execute first the order "system" and then "window".

You can also write comments, just like in other languages, there are 2 ways to do so:
* Single line comments with ```//``` or ```#```.
* Multiple line comments with ```/* */```.

- **Example:**
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


## 2. Command List

### system
- **Description:** Displays System Data.
- **Syntax:** ```system;```
- **Example:**
  ```system;```

### window
- **Description:** Displays window data.
- **Syntax:** ```window;```
- **Example:**
  ```window;```

### screen
- **Description:** Displays screen data.
- **Syntax:** ```screen;```
- **Example:**
  ```screen;```

### stop
- **Description:** Stops reading inputs and disables the physics simulation.
- **Syntax:** ```stop;```
- **Example:**
  ```stop;```

### play
- **Description:** Starts reading again inputs and enables the physics simulation.
- **Syntax:** ```play;```
- **Example:**
  ```play;```

### help
- **Description:** Displays help for a subcommand.
- **Syntax:** ```help <subcommand>;```
- **Example:**
  ```help system;```

### standby
- **Description:** Configures standby mode with an option.
- **Syntax:** ```standby <option>;```
- **Example:**
  ```standby on;```

### grid scale
- **Description:** Sets the grid scale with a float value.
- **Syntax:** ```grid scale <value>;```
- **Example:**
  ```grid scale 2.5;```

### change to
- **Description:** Changes the current scene to the specified one.
- **Syntax:** ```change to <scene>;```
- **Example:**
  ```change to SceneA;```

### add object
- **Description:** Adds an object with a class name and alias.
- **Syntax:** ```add object <className> as <alias>;```
- **Example:**
  ```add object Player as mainCharacter;```

### add component
- **Description:** Adds a component with a class name to an alias.
- **Syntax:** ```add component <className> to <alias>;```
- **Example:**
  ```add component Physics to Player;```

### delete object
- **Description:** Deletes an object by its alias.
- **Syntax:** ```delete object <alias>;```
- **Example:**
  ```delete object mainCharacter;```

### enable object
- **Description:** Enables an object by its alias.
- **Syntax:** ```enable object <alias>;```
- **Example:**
  ```enable object mainCharacter;```

### disable object
- **Description:** Disables an object by its alias.
- **Syntax:** ```disable object <alias>;```
- **Example:**
  ```disable object mainCharacter;```

### set object
- **Description:** Sets a field of an object to a value.
- **Syntax:** ```set object <alias> <field> as <value>;```
- **Example:**
  ```set object Player speed as 10;```

