# Alce Runtime Language (ARL) > Usage Guide

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

### help

Displays help information about available commands.

>  help <command\>

Example:
```
help set
```

---

### system

Displays system information such as OS version, CPU, GPU, RAM, and DirectX version.

>  system

---

### screen

Displays information about the current screen.

>  screen

---

### window

Displays information about the current application window.

>  window

---

### stop

Pauses the current scene.

>  stop

---

### play

Resumes the current scene.

>  play

---

### exit

Exits the application.

>  exit

---

### switch

Toggles between development and production modes.

>  switch

---

### list

Lists all game objects in the current scene.

>  list

---

### standby

Enables or disables standby mode.

>  standby <on|off>

Example:
```
standby on
```

---

### scene

Displays the name of the current scene.

>  scene

---

### grid

Sets the grid scale of the current scene.

>  grid <value\>

Example:
```
grid 10
```

---

### has

Checks if a game object with a specific alias exists in the current scene.

>  has <alias\>

Example:
```
has player1
```

---

### change

Changes the current scene.

>  change to <scene_name\>

Example:
```
change to MainMenu
```

---

### add

Adds a new game object to the scene using a factory creator.

>  add <creator\> <alias\>

Example:
```
add Enemy enemy1
```

---

### set

Sets a property of a game object.

>  set <alias\> <field\> <value\>

Example:
```
set enemy1 health 100
```

---

### get

Retrieves a property value of a game object.

>  get <alias\> <field\>

Example:
```
get enemy1 health
```

---

### delete

Deletes a game object from the scene.

>  delete <alias\>

Example:
```
delete enemy1
```

---

### enable

Enables a game object or component.

> enable object <alias\>

> enable component <componentId> from <alias>

Example:
```
enable object enemy1

enable component SpriteRenderer from enemy1
```

---

### disable

Disables a game object or component.

> disable object <alias>

> disable component <componentId> from <alias>

Example:
```
disable object enemy1

disable component collider from enemy1
```