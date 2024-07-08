# Class: value_wrapper

Class for wrapping parameters and return value of functions, used mostly by the dynamic_hook system.

## Functions (2)

### `get()`

Get the value currently contained by the wrapper.

- **Returns:**
  - `any`: The current value.

**Example Usage:**
```lua
any = value_wrapper:get()
```

### `set(new_value)`

Set the new value contained by the wrapper.

- **Parameters:**
  - `new_value` (any): The new value.

**Example Usage:**
```lua
value_wrapper:set(new_value)
```


