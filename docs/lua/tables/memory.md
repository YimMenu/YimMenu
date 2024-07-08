# Table: memory

Table containing helper functions related to process memory.

## Functions (6)

### `scan_pattern(pattern)`

Scans the specified memory pattern within the "GTA5.exe" module and returns a pointer to the found address.

- **Parameters:**
  - `pattern` (string): byte pattern (IDA format)

- **Returns:**
  - `pointer`: A pointer to the found address.

**Example Usage:**
```lua
pointer = memory.scan_pattern(pattern)
```

### `handle_to_ptr(entity)`

- **Parameters:**
  - `entity` (number): script game entity handle

- **Returns:**
  - `pointer`: A rage::CDynamicEntity pointer to the script game entity handle

**Example Usage:**
```lua
pointer = memory.handle_to_ptr(entity)
```

### `ptr_to_handle(mem_addr)`

- **Parameters:**
  - `mem_addr` (pointer): A rage::CDynamicEntity pointer.

- **Returns:**
  - `number`: The script game entity handle linked to the given rage::CDynamicEntity pointer.

**Example Usage:**
```lua
number = memory.ptr_to_handle(mem_addr)
```

### `allocate(size)`

- **Parameters:**
  - `size` (integer): The number of bytes to allocate on the heap.

- **Returns:**
  - `pointer`: A pointer to the newly allocated memory.

**Example Usage:**
```lua
pointer = memory.allocate(size)
```

### `free(ptr)`

- **Parameters:**
  - `ptr` (pointer): The pointer that must be freed.

**Example Usage:**
```lua
memory.free(ptr)
```

### `dynamic_hook(hook_name, return_type, param_types, target_func_ptr, pre_callback, post_callback)`

**Example Usage:**
```lua
local ptr = memory.scan_pattern("some ida sig")
memory.dynamic_hook("test_hook", "float", {"const char*"}, ptr,
function(ret_val, str)

     --str:set("replaced str")
     ret_val:set(69.69)
     log.info("pre callback from lua", ret_val:get(), str:get())

     -- false for skipping the original function call
     return false
end,
function(ret_val, str)
     log.info("post callback from lua 1", ret_val:get(), str:get())
     ret_val:set(79.69)
     log.info("post callback from lua 2", ret_val:get(), str:get())
end)
```

- **Parameters:**
  - `hook_name` (string): The name of the hook.
  - `return_type` (string): Type of the return value of the detoured function.
  - `param_types` (table<string>): Types of the parameters of the detoured function.
  - `target_func_ptr` (memory.pointer): The pointer to the function to detour.
  - `pre_callback` (function): The function that will be called before the original function is about to be called. The callback must match the following signature: ( return_value (value_wrapper), arg1 (value_wrapper), arg2 (value_wrapper), ... ) -> Returns true or false (boolean) depending on whether you want the original function to be called.
  - `post_callback` (function): The function that will be called after the original function is called (or just after the pre callback is called, if the original function was skipped). The callback must match the following signature: ( return_value (value_wrapper), arg1 (value_wrapper), arg2 (value_wrapper), ... ) -> void

**Example Usage:**
```lua
memory.dynamic_hook(hook_name, return_type, param_types, target_func_ptr, pre_callback, post_callback)
```


