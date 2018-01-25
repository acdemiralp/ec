**What is an entity-component (ec-)table?**  
A table where the rows correspond to entities and columns correspond to component types.
Each entry is a particular entity's particular component (or null if the entity does not have that type of component). 
Rows (entities) are created/destroyed at run-time however columns (types of components) must be specified at compile-time. 
It corresponds to a scene from a non-technical perspective.  

Example:
  
| name      | audio_listener | audio_source | button | camera | collider | light | mesh  | transform |
|:--------- |:-------------- |:------------ |:------ |:------ |:-------- |:----- |:----- |:--------- |
| "terrain" | null           | null         | null   | null   | {...}    | null  | {...} | {...}     |
| "wind"    | null           | {...}        | null   | null   | null     | null  | null  | {...}     |
| "sun"     | null           | null         | null   | null   | null     | {...} | null  | {...}     |
| "player"  | {...}          | null         | null   | {...}  | {...}    | null  | {...} | {...}     |
| "ui"      | null           | null         | {...}  | null   | {...}    | null  | null  | {...}     |
&nbsp;

**What is an entity?**  
Simply a handle referring to a row in an ec-table.

**What is a component?**  
A data type representing a particular aspect of an entity. 
It is not required to derive from a base class.  
Examples: `audio_source, audio_listener, button, camera, collider, light, mesh, name, transform, ...`

**What is a system?**  
A system regularly traverses an ec-table, and processes the components relevant to it. 
It is not required to derive from a base class.  
Examples: `audio_system, physics_world, renderer, ui_system, ...`

**Limitations**  
An entity can only have one of each component type since multiple identical types are not allowed in the ec-table.