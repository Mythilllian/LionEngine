C++ cross-platform 2D game engine. Uses SDL for graphics and nlohmann/json for configuring the game and scenes.

Recommended Setup:
```
Game Directory
├── LionEngine
├── Assets
├── Build (automatically generated)
├── Config
├── Logs (automatically generated)
└── Scripts
```

Build:
```
cmake -B Build -S . && cmake --build Build
```