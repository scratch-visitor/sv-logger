# sv-logger

> one header file library

---

- [sv-logger](#sv-logger)
  - [Interface](#interface)
    - [Preprocessor](#preprocessor)
    - [Free Functions](#free-functions)
    - [log format](#log-format)
  - [Build Environment](#build-environment)
    - [Windows](#windows)

---

## Interface

### Preprocessor

- `trace`: log current function name.
- `scope_trace`: log current scope begin/end.

```cpp
trace;

{
  scope_trace(test);
}
```

### Free Functions

- `log({string})`: log input string.
- `log({format}, {arg0}, ...)`: log input format string with arguments.
- `on_error({error_code}, {tag})`: log error.

```cpp
log("test");
log("{} is {}", 2, "two");
on_error(boost::asio::error_code::operation_aborted, "on_accept");
```

### log format

- format: `[{timestamp}] {content}`

```cpp
[2024-08-01 23:47:11] main
```

## Build Environment

- use `manifest mode` of `vcpkg` for third-party libraries.
- use `cmake` for build-system.
  - use `ninja` for generator.
  - use `clang` for compiler.

### Windows

use `winget` tool to install dev-tools.

```powershell
winget install Kitware.CMake Ninja-build.Ninja LLVM.LLVM
```