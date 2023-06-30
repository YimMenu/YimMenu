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
  - `text`: The text object instance.

**Exemple Usage:**
```lua
text = tab:add_text(name)
```

### `add_checkbox(name)`

Add a checkbox widget to the gui tab.

- **Parameters:**
  - `name` (string): Text that will be written next to the checkbox.

- **Returns:**
  - `checkbox`: The checkbox object instance.

**Exemple Usage:**
```lua
checkbox = tab:add_checkbox(name)
```

### `add_sameline()`

Add a ImGui::SameLine.

- **Returns:**
  - `sameline`: The sameline object instance.

**Exemple Usage:**
```lua
sameline = tab:add_sameline()
```

### `add_separator()`

Add a ImGui::Separator.

- **Returns:**
  - `separator`: The separator object instance.

**Exemple Usage:**
```lua
separator = tab:add_separator()
```

### `add_input_int(name)`

Add a ImGui::InputInt.

- **Parameters:**
  - `name` (string): Text that will be written next to the input field.

- **Returns:**
  - `input_int`: The input_int object instance.

**Exemple Usage:**
```lua
input_int = tab:add_input_int(name)
```

### `add_input_float(name)`

Add a ImGui::InputFloat.

- **Parameters:**
  - `name` (string): Text that will be written next to the input field.

- **Returns:**
  - `input_float`: The input_float object instance.

**Exemple Usage:**
```lua
input_float = tab:add_input_float(name)
```

### `add_input_string(name)`

Add a ImGui::InputText.

- **Parameters:**
  - `name` (string): Text that will be written next to the input field.

- **Returns:**
  - `input_string`: The input_string object instance.

**Exemple Usage:**
```lua
input_string = tab:add_input_string(name)
```


