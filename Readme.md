# Raytracer

# Minimal Raytracer

A lightweight, CPU-based raytracer written in C using [Raylib](https://www.raylib.com/). It renders a procedurally shaded 3D sphere with animation and basic diffuse lighting entirely on the CPU, updating an image buffer transferred to the GPU each frame.

## Features

* Custom 3D vector and ray-sphere intersection math
* Lambertian diffuse lighting with ambient light calculation
* Real-time CPU-to-GPU texture streaming via Raylib
* Zero external assets required

## Building and Running

### Prerequisites

You need a C compiler (like `gcc`) and `raylib` installed. If you use Nix, you can set up a quick development shell with all required dependencies:

```nix
{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = with pkgs; [
    raylib
    glfw
    mesa
    xorg.libX11
    xorg.libXcursor
    xorg.libXrandr
    xorg.libXinerama
    xorg.libXi
  ];
}

```

### Compilation

Compile the source code by linking Raylib and math libraries:

```bash
gcc main.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o raytracer

```

### Execution

Run the compiled binary:

```bash
./raytracer

```
