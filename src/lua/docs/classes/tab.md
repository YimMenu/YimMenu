# Class: tab

Class for representing a tab within the GUI.

## Functions (8)

### `add_button(name, callback)`

Add a button to the gui tab.

- **Parameters:**
  - `name` (string): Text written inside the button.
  - `callback` (function): function that will be called when the button is clicked.

**Exemple Usage:**
```lua
tab:add_button(name, callback)
```

### `add_text(name)`

Add text to the gui tab.

- **Parameters:**
  - `name` (string): Text that will be written.

- **Returns:**
  - `text`: the text object instance.

**Exemple Usage:**
```lua
text = tab:add_text(name)
```

### `add_checkbox(name)`

Add a checkbox widget to the gui tab.

- **Parameters:**
  - `name` (string): Text that will be written next to the checkbox.

- **Returns:**
  - `checkbox`: the checkbox object instance.

**Exemple Usage:**
```lua
checkbox = tab:add_checkbox(name)
```

### `add_sameline()`

- **Returns:**
  - `sameline`: the sameline object instance.

**Exemple Usage:**
```lua
sameline = tab:add_sameline()
```

### `add_separator()`

- **Returns:**
  - `separator`: the separator object instance.

**Exemple Usage:**
```lua
separator = tab:add_separator()
```

### `add_input_int(name)`

- **Parameters:**
  - `name` (string): Text that will be written next to the input field.

- **Returns:**
  - `input_int`: the input_int object instance.

**Exemple Usage:**
```lua
input_int = tab:add_input_int(name)
```

### `add_input_float(name)`

- **Parameters:**
  - `name` (string): Text that will be written next to the input field.

- **Returns:**
  - `input_float`: the input_float object instance.

**Exemple Usage:**
```lua
input_float = tab:add_input_float(name)
```

### `add_input_string(name)`

- **Parameters:**
  - `name` (string): Text that will be written next to the input field.

- **Returns:**
  - `input_string`: the input_string object instance.

**Exemple Usage:**
```lua
input_string = tab:add_input_string(name)
```


