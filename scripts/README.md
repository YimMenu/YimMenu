# Scripts

This directory contains a collection of scripts used to generate certain parts of the code base.

## Doc Gen

`doc_gen.py` is used to generate the Lua documentation that's provided by YimMenu.
It relies on specifically formatted code comments to generate Lua documentation.

## Generate Natives

`generate_natives.py` is responsible for generating the `src/natives.hpp` and `src/invoker/crossmap.hpp` files.

It takes a `natives.json` from [here](https://github.com/alloc8or/gta5-nativedb-data) and a `crossmap.txt` file which needs follow a certain format of:
```csv
[first_seen_native_hash]<comma>[current_native_hash]
```

Example:
```csv
0xE1A0450ED46A7812,0x11FD21BA1B765FE2
0x39BE7CEA8D9CC8E6,0x5F7C6361179DFFC4
0x3C5FD37B5499582E,0x54BC5E0B6A29AE8A
0xE2A99A9B524BEFFF,0x1FDE21A286357401
0x51F1A8E48C3D2F6D,0xD1BAD83E70275AEB
0x0A6D923DFFC9BD89,0x93693D93BD53ACB1
0x112CEF1615A1139F,0x203607236413B185
0xD47A2C1BA117471D,0x4F3198DEED415E95
0xC2F7FE5309181C7D,0xCFE92984BF3486D5
0x23789E777D14CE44,0x2B3725FC402B94A8
0x350AA5EBC03D3BD2,0x606408352C7741AD
0x498C1E05CE5F7877,0x59E8FA762FB527C5
...
```

## Natives Gen

`natives_gen.py` is used to generate the Lua bindings for all the natives currently present in the menu.
It'll read through the `src/natives.hpp` file and generate the appropriate bindings under `src/lua/natives/`.