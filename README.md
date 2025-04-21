## Build Prequisites
- CMake 3.28.3+ Installed
- C++ 17
- Qt6 Installed
## Build Instructions
- mkdir build
- cd build
- cmake ..
- cmake --build .
## Application Details
- Peer-to-Peer (P2P) Chat Room App
- Port Forwarding Is Required For WAN (Not LAN)
    - Default Application Port = 9090
- Client IPs Are Exposed To Room Host 
## VSCode Settings
#### To apply format on save with .clang-format, add the following file at the path .vscode/settings.json:
```
{
    "[cpp]": {
        "editor.formatOnSave": true,
    }
} 
```