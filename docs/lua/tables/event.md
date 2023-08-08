# Table: event

Table for responding to various events. The list of events is available in the menu_event table.

## Functions (1)

### `register_handler(menu_event, func)`

Register a function that will be called each time the corresponding menu_event is triggered.

- **Parameters:**
  - `menu_event` (menu_event): The menu_event that we want to respond to.
  - `func` (function): The function that will be called.

**Example Usage:**
```lua
event.register_handler(menu_event, func)
```


