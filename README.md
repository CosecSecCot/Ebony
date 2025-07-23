# Ebony - Ray Tracing Engine

Ebony is a simple ray tracing engine, inspired by "Ray Tracing in One Weekend"
by Peter Shirley. It serves as a learning project and a foundation for future
rendering experiments.

<img width="1392" height="860" alt="Screenshot 2025-07-23 at 2 45 10 PM" src="https://github.com/user-attachments/assets/9342ff6d-a371-4ce8-9982-6bdf8d2e7399" />
<img width="1392" height="860" alt="Screenshot 2025-07-23 at 2 50 04 PM" src="https://github.com/user-attachments/assets/d0883ae3-92e1-4217-b4f0-573edcdf7af0" />


## Getting Started

```sh
# Clone the repository
git clone https://github.com/CosecSecCot/Ebony.git
cd Ebony

# Build
mkdir build
cd build
cmake .. && cmake --build .
```

Executable is going to be in:

```sh
# For Debug build
./bin/Debug/ebony-engine/

# For Release build
./bin/Release/ebony-engine/
```


## Architecture Overview


## Current Progress
- [x] ~~ Red triangle in ImGui Viewport~~
- [x] Renderer + OpenGL abstractions
- [x] UI system working with panels
- [x] Environment + lighting settings panel
- [x] Scene with `Sphere` objects
- [ ] Object abstraction
- [ ] Mesh rendering
- [ ] Camera control
- [ ] Texture/material abstraction
- [ ] Save scenes, materials, etc. in config files


---
