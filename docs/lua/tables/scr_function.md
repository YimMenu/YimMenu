# Table: scr_function

Table for calling GTA script functions. Needs to be called in the fiber pool.

## Functions (2)

### `call_script_function(script_name, function_name, pattern, return_type_string, args_)`

Calls a script function. Returns the return value as the given type.

- **Parameters:**
  - `script_name` (string): Name of the script.
  - `function_name` (string): Name of the function.
  - `pattern` (string): Pattern to scan for within the script.
  - `return_type_string` (string): Return type of the function.
  - `_args` (table): Arguments to pass to the function.

**Example Usage:**
```lua
local value = scr_function.call_script_function("freemode", "wear_sunglasses_at_night", "69 42 06 66", "bool", {
  { "int", 69 },
  { "float", 4.20 },
  { "int", 666 }
})
```

### `call_script_function(script_name, instruction_pointer, return_type_string, args_)`

Calls a script function directly using the function position. Returns the return value as the given type.

- **Parameters:**
  - `script_name` (string): Name of the script.
  - `function_name` (string): Name of the function.
  - `instruction_pointer` (integer): Position of the function within the script.
  - `return_type_string` (string): Return type of the function.
  - `_args` (table): Arguments to pass to the function.

**Example Usage:**
```lua
local value = scr_function.call_script_function("freemode", 0xE792, "string", {
  { "int", 191 }
})
```