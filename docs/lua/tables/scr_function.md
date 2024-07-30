# Table: scr_function

Table for calling GTA script functions. Needs to be called in the fiber pool.

## Functions (10)

### `call_void(script_name, pattern, _args)`

Calls a void script function.

- - **Parameters:**
  - `script_name` (string): Name of the script.
  - `pattern` (string): Pattern to scan for within the script.
  - `_args` (table): Arguments to pass to the function.


**Example Usage:**
```lua
scr_function.call_void(script_name, pattern, _args)
```

### `call_int(script_name, pattern, _args)`

Calls an integer script function.

- - **Parameters:**
  - `script_name` (string): Name of the script.
  - `pattern` (string): Pattern to scan for within the script.
  - `_args` (table): Arguments to pass to the function.

- **Returns:**
  - `integer`: The return value of the function.


**Example Usage:**
```lua
integer = scr_function.call_int(script_name, pattern, _args)
```

### `call_float(script_name, pattern, _args)`

Calls a float script function.

- - **Parameters:**
  - `script_name` (string): Name of the script.
  - `pattern` (string): Pattern to scan for within the script.
  - `_args` (table): Arguments to pass to the function.

- **Returns:**
  - `float`: The return value of the function.


**Example Usage:**
```lua
float = scr_function.call_float(script_name, pattern, _args)
```

### `call_string(script_name, pattern, _args)`

Calls a string script function.

- - **Parameters:**
  - `script_name` (string): Name of the script.
  - `pattern` (string): Pattern to scan for within the script.
  - `_args` (table): Arguments to pass to the function.

- **Returns:**
  - `string`: The return value of the function.


**Example Usage:**
```lua
string = scr_function.call_string(script_name, pattern, _args)
```

### `call_vec3(script_name, pattern, _args)`

Calls a Vector3 script function.

- - **Parameters:**
  - `script_name` (string): Name of the script.
  - `pattern` (string): Pattern to scan for within the script.
  - `_args` (table): Arguments to pass to the function.

- **Returns:**
  - `string`: The return value of the function.


**Example Usage:**
```lua
Vector3 = scr_function.call_vec3(script_name, pattern, _args)
```

### `call_void(script_name, ip, _args)`

Calls a void script function.

- - **Parameters:**
  - `script_name` (string): Name of the script.
  - `ip` (integer): Position of the function within the script.
  - `_args` (table): Arguments to pass to the function.


**Example Usage:**
```lua
scr_function.call_void(script_name, ip, _args)
```

### `call_int(script_name, ip, _args)`

Calls an integer script function.

- - **Parameters:**
  - `script_name` (string): Name of the script.
  - `ip` (integer): Position of the function within the script.
  - `_args` (table): Arguments to pass to the function.

- **Returns:**
  - `integer`: The return value of the function.


**Example Usage:**
```lua
integer = scr_function.call_int(script_name, ip, _args)
```

### `call_float(script_name, ip, _args)`

Calls a float script function.

- - **Parameters:**
  - `script_name` (string): Name of the script.
  - `ip` (integer): Position of the function within the script.
  - `_args` (table): Arguments to pass to the function.

- **Returns:**
  - `float`: The return value of the function.


**Example Usage:**
```lua
float = scr_function.call_float(script_name, ip, _args)
```

### `call_string(script_name, ip, _args)`

Calls a string script function.

- - **Parameters:**
  - `script_name` (string): Name of the script.
  - `ip` (integer): Position of the function within the script.
  - `_args` (table): Arguments to pass to the function.

- **Returns:**
  - `string`: The return value of the function.


**Example Usage:**
```lua
string = scr_function.call_string(script_name, ip, _args)
```

### `call_vec3(script_name, ip, _args)`

Calls a Vector3 script function.

- - **Parameters:**
  - `script_name` (string): Name of the script.
  - `ip` (integer): Position of the function within the script.
  - `_args` (table): Arguments to pass to the function.

- **Returns:**
  - `string`: The return value of the function.


**Example Usage:**
```lua
Vector3 = scr_function.call_vec3(script_name, ip, _args)
```