#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
PREFIX_DIR="$ROOT_DIR/deps/sdl1"
BUILD_ROOT="${TMPDIR:-/tmp}/blobwar-deps"
SRC_DIR="$BUILD_ROOT/src"

export PATH="/opt/homebrew/bin:$PATH"

mkdir -p "$SRC_DIR" "$PREFIX_DIR"

download() {
  local url="$1"
  local filename="$2"
  if [[ ! -f "$SRC_DIR/$filename" ]]; then
    curl -fL "$url" -o "$SRC_DIR/$filename"
  fi
}

extract_clean() {
  local archive="$1"
  local dirname="$2"
  rm -rf "$SRC_DIR/$dirname"
  tar -xzf "$SRC_DIR/$archive" -C "$SRC_DIR"
}

build_sdl_net() {
  local dir="$SRC_DIR/SDL_net-1.2.8"
  (
    cd "$dir"
    CC=/usr/bin/clang CXX=/usr/bin/clang++ ./configure \
      --prefix="$PREFIX_DIR" \
      --with-sdl-prefix=/opt/homebrew \
      --disable-sdltest
    make -j4
    make install
  )
}

build_sdl_ttf() {
  local dir="$SRC_DIR/SDL_ttf-2.0.11"
  (
    cd "$dir"
    FREETYPE_CONFIG=/opt/homebrew/bin/freetype-config CC=/usr/bin/clang CXX=/usr/bin/clang++ ./configure \
      --prefix="$PREFIX_DIR" \
      --with-sdl-prefix=/opt/homebrew \
      --disable-sdltest
    # Demo programs may fail to link on recent macOS; only lib+headers are needed.
    make -j4 || true
    make install-exec-am install-data-am
  )
}

build_sdl_image() {
  local dir="$SRC_DIR/SDL_image-1.2.12"
  (
    cd "$dir"
    CC=/usr/bin/clang CXX=/usr/bin/clang++ OBJC=/usr/bin/clang ./configure \
      --prefix="$PREFIX_DIR" \
      --with-sdl-prefix=/opt/homebrew \
      --disable-sdltest
    make -j4
    make install
  )
}

download "https://www.libsdl.org/projects/SDL_net/release/SDL_net-1.2.8.tar.gz" "SDL_net-1.2.8.tar.gz"
download "https://www.libsdl.org/projects/SDL_ttf/release/SDL_ttf-2.0.11.tar.gz" "SDL_ttf-2.0.11.tar.gz"
download "https://www.libsdl.org/projects/SDL_image/release/SDL_image-1.2.12.tar.gz" "SDL_image-1.2.12.tar.gz"

extract_clean "SDL_net-1.2.8.tar.gz" "SDL_net-1.2.8"
extract_clean "SDL_ttf-2.0.11.tar.gz" "SDL_ttf-2.0.11"
extract_clean "SDL_image-1.2.12.tar.gz" "SDL_image-1.2.12"

build_sdl_net
build_sdl_ttf
build_sdl_image

echo "SDL1 deps installed in: $PREFIX_DIR"
