# Table: memory

Table containing helper functions related to process memory.

## Functions (7)

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
-- Check the implementation of the asmjit::TypeId get_type_id function if you are unsure what to use for return type / parameters types
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

### `dynamic_call(return_type, param_types, target_func_ptr)`

**Example Usage:**
```lua
-- the sig in this example leads to an implementation of memcpy_s
local ptr = memory.scan_pattern("48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 20 49 8B D9 49 8B F0 48 8B FA")
if ptr:is_valid() then
     local dest_size = 8
     local dest_ptr = memory.allocate(dest_size)
     dest_ptr:set_qword(0)

     local src_size = 8
     local src_ptr = memory.allocate(src_size)
     src_ptr:set_qword(123)

     -- Check the implementation of the asmjit::TypeId get_type_id function if you are unsure what to use for return type / parameters types
     local func_to_call_test_global_name = memory.dynamic_call("int", {"void*", "uint64_t", "void*", "uint64_t"}, ptr)
     -- print zero.
     log.info(dest_ptr:get_qword())
     -- note: don't pass memory.pointer objects directly when you call the function, but use get_address() instead.
     local call_res_test = _G[func_to_call_test_global_name](dest_ptr:get_address(), dest_size, src_ptr:get_address(), src_size)
     -- print 123.
     log.info(dest_ptr:get_qword())
end
```

- **Parameters:**
  - `return_type` (string): Type of the return value of the function to call.
  - `param_types` (table<string>): Types of the parameters of the function to call.
  - `target_func_ptr` (memory.pointer): The pointer to the function to call.

- **Returns:**
  - `string`: Key name of the function that you can now call from lua.

**Example Usage:**
```lua
string = memory.dynamic_call(return_type, param_types, target_func_ptr)
```


