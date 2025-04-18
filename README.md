## Prequisites
- CMake 3.28.3+ Installed
- C++ 17
- Qt6 Installed
## Build Instructions
- mkdir build
- cd build
- cmake ..
- cmake --build .
## VSCode Settings
#### To apply format on save with .clang-format, add the following file at the path .vscode/settings.json:
```
{
    "[cpp]": {
        "editor.formatOnSave": true,
    }
} 
```