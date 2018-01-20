**Definitions**

- What is an entity-component (ec-)table?
  - A table where the rows correspond to entities and columns correspond to component types.
  - Each entry is a particular entity's particular component (or null if the entity does not have that type of component).
  - Rows (entities) are created/destroyed at run-time however columns (types of components) must be specified at compile-time.

- What is an entity?
  - Simply an index (`std::size_t`) referring to a row in an ec-table.

- What is a component?
  - A data type representing a particular aspect of an entity.
  - Examples: `audio_source, audio_listener, button, camera, collider, light, mesh, transform, ...`

- What is a system?
  - A system regularly traverses an ec-table, and processes the components relevant to it.
  - Systems use compile-time defined keys to select relevant entities in an ec-table.
  - A key consists of one or more component types (columns), which have to be existent on an entity (row) for the system to be able to process it. One can think of keys as the component requirements of a system.

**Example ec-table**

| name      | audio_listener | audio_source | button | camera | collider | light | mesh  | transform |
|:--------- |:-------------- |:------------ |:------ |:------ |:-------- |:----- |:----- |:--------- |
| "terrain" | null           | null         | null   | null   | {...}    | null  | {...} | {...}     |
| "wind"    | null           | {...}        | null   | null   | null     | null  | null  | {...}     |
| "sun"     | null           | null         | null   | null   | null     | {...} | null  | {...}     |
| "player"  | {...}          | null         | null   | {...}  | {...}    | null  | {...} | {...}     |
| "ui"      | null           | null         | {...}  | null   | {...}    | null  | null  | {...}     |

**Example systems**

- `audio_system<component_key<audio_listener, transform>, component_key<audio_source, transform>>`
- `physics_system<component_key<collider, transform>>`
- `renderer<component_key<camera, transform>, component_key<light, transform>, component_key<mesh, transform>>`
- `ui_system<component_key<button, collider, transform>>`

**Implementation**

The ec-table must be in such a form that it is trivial to:
- Insert or remove an entity (row).
- Iterate through all entities (rows).
- Iterate through all entities (rows) containing one or more component types (columns).

Until now, a `std::vector<std::tuple<types...>>` would suffice but in addition, the following should also be efficient:
- Query an entity's components        (select row  , given row index).
- Query an entity's component by type (select entry, given row index and column type).
- Query a component's entity          (select row  , given entry).

The issue is when allowing row insertion/removal from the middle, the index cannot be relied upon for access to the entities. 
Instead it is possible to hold a component for entity metadata (e.g. id, name) and query by the equivalence of it. This requires 
a search for entity (`std::find_if`). 

An alternative is to use an associative container: `std::unordered_map<std::size_t, std::tuple<types...>>`

The systems do not necessarily derive from a common interface and only need to hold:
- A pointer to the ec-table they are processing.
- A set of typedefs consisting of one or more component types to query the ec-table with.

**Limitations**

- An entity can only have one of each component type since multiple identical types are not allowed in the ec-table.

**TODO**

Find a better way to create systems which require more than one key.