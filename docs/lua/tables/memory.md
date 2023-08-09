# Table: memory

Table containing helper functions related to process memory.

## Functions (5)

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


