{ pkgs ? import <nixpkgs> {} }:
pkgs.mkShell {
  buildInputs = with pkgs; [
    SDL
    SDL_image
    SDL_ttf
    SDL_net
    clang
    gnumake
    pkg-config
    clang-tools
  ];
  shellHook = ''
    export CC=clang
    export CXX=clang++
  '';
}
