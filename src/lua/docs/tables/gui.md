# Table: gui

Table containing functions for modifying the menu GUI.

## Functions (5)

### `get_tab(tab_name)`

- **Parameters:**
  - `tab_name` (string): Name of the tab to get.

- **Returns:**
  - `tab`: A tab instance which corresponds to the tab in the GUI.

**Exemple Usage:**
```lua
tab = gui.get_tab(tab_name)
```

### `show_message(title, message)`

Shows a message to the user with the given title and message.

- **Parameters:**
  - `title` (string)
  - `message` (string)

**Exemple Usage:**
```lua
gui.show_message(title, message)
```

### `show_warning(title, message)`

Shows a warning to the user with the given title and message.

- **Parameters:**
  - `title` (string)
  - `message` (string)

**Exemple Usage:**
```lua
gui.show_warning(title, message)
```

### `show_error(title, message)`

Shows an error to the user with the given title and message.

- **Parameters:**
  - `title` (string)
  - `message` (string)

**Exemple Usage:**
```lua
gui.show_error(title, message)
```

### `is_open()`

- **Returns:**
  - `bool`: Returns true if the GUI is open.

**Exemple Usage:**
```lua
bool = gui.is_open()
```


