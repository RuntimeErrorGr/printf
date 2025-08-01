# iocla_printf

A lightweight, custom implementation of the standard `printf` function in C, supporting basic format specifiers and direct system-level output via `write`.

## Features

- Supports the following format specifiers:
  - `%d` — Signed decimal integers
  - `%u` — Unsigned decimal integers
  - `%x` — Hexadecimal (lowercase)
  - `%c` — Single characters
  - `%s` — Null-terminated strings
  - `%%` — Literal percent sign

- Handles:
  - Negative integers
  - Zero-padding via internal logic
  - Basic string and memory handling without relying on `printf`

## Implementation Details

- Uses `write(1, ...)` for direct output to `stdout`
- Manual conversion of integers using custom `itoa`, `utoa`, and `htoa` functions
- Custom string utility functions: `strrev`, `strlwr`
- Variable argument processing with `stdarg.h`

## Limitations

- No support for floating-point formats (`%f`)
- No field width, precision, or flags (e.g. `%05d`)
- Basic error handling
- Minimal memory safety (relies on manual allocation and freeing)

## Example

```c
iocla_printf("Hello, %s! Your score is %d%% (hex: %x)\n", "Alice", 93, 93);
```

## Build & Run
```
gcc -o printf_example your_file.c
./printf_example
```
