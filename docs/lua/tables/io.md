# Table: io

Table for file manipulation. Modified for security purposes.

## Functions (2)

### `open()`

- **Returns:**
  - `file_handle`: file handle or nil if can't read / write to the given path.

**Example Usage:**
```lua
file_handle = io.open()
```

### `exists()`

- **Returns:**
  - `boolean`: True if the passed file path exists

**Example Usage:**
```lua
boolean = io.exists()
```


