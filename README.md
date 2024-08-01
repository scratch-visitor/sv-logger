# logger

> one header file library

---

- [logger](#logger)
  - [Build Environment](#build-environment)
    - [Windows](#windows)

---

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