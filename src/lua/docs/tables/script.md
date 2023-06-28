# Table: script

Table containing helper functions related to gta scripts.

## Functions (4)

### `register_looped(name, func)`

Registers a function that will be looped as a gta script.

- **Parameters:**
  - `name` (string): name of your new looped script
  - `func` (function): function that will be executed in a forever loop.

**Exemple Usage:**
```lua
script.register_looped(name, func)
```

### `run_in_fiber(func)`

Executes a function inside the fiber pool, you can call natives inside it.

- **Parameters:**
  - `func` (function): function that will be executed once in the fiber pool, you can call natives inside it.

**Exemple Usage:**
```lua
script.run_in_fiber(func)
```

### `yield()`

Yield execution.

**Exemple Usage:**
```lua
script.yield()
```

### `sleep(ms)`

Sleep for the given amount of time, time is in milliseconds.

- **Parameters:**
  - `ms` (integer): The amount of time in milliseconds that we will sleep for.

**Exemple Usage:**
```lua
script.sleep(ms)
```


