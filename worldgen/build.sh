#!/bin/sh
# Debian: clang, lld, wasi-libc, libclang-rt-dev-wasm32
set -eu
cd "$(dirname "$0")"
C=cubiomes
clang --target=wasm32-wasi --sysroot=/usr -O3 -fwrapv -DNDEBUG -I"$C" -mexec-model=reactor \
  -Wl,--no-entry -Wl,--initial-memory=33554432 -Wl,--max-memory=1073741824 \
  -Wl,--export=engine_init -Wl,--export=engine_biomes -Wl,--export=engine_biome_at \
  -Wl,--export=engine_biome_name -Wl,--export=engine_height_samples -Wl,--export=engine_structures -Wl,--export=engine_strongholds \
  -Wl,--export=engine_spawn -Wl,--export=engine_slime -Wl,--export=engine_alloc -Wl,--export=engine_free \
  engine.c "$C"/generator.c "$C"/biomes.c "$C"/layers.c "$C"/biomenoise.c "$C"/noise.c "$C"/finders.c "$C"/util.c -o cubiomes.wasm
printf 'To update the single-file site, replace its WASM_BASE64 constant with base64 of cubiomes.wasm.\n'
