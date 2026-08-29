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
  
  shellHook = ''
    echo "Raylib development environment loaded!"
  '';
}