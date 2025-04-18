# VSCode Settings
### Build Instructions
- mkdir build
- cd build
- cmake ..
- cmake --build .
### To apply format on save with .clang-format, add the following file at the path .vscode/settings.json:
```
{
    "[cpp]": {
        "editor.formatOnSave": true,
    }
} 
```