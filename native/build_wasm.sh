#!/bin/bash
set -euo pipefail

BUILD_DIR=build_wasm
mkdir -p "${BUILD_DIR}"
cd "${BUILD_DIR}"

echo "Setting up Emscripten environment..."
source ~/emsdk/emsdk_env.sh

echo "Building WebAssembly with Emscripten..."

# Configure with Emscripten toolchain
emcmake cmake .. #-DCMAKE_VERBOSE_MAKEFILE=ON

# Build the project
emmake cmake --build . 2>&1 | tee build_wasm.log
# -- VERBOSE=0
# Check for generated files
if [ -f WebassemblyTemplate.js ] && [ -f WebassemblyTemplate.wasm ]; then
    echo ""
    echo "Build successful! Files generated in build_wasm directory."
    echo "  - WebassemblyTemplate.js: Main JavaScript module"
    echo "  - WebassemblyTemplate.wasm: WebAssembly binary"
    echo "  - WebassemblyTemplate.d.ts: TypeScript definitions"
else
    echo "Build may have failed. Check for error messages above."
fi

emmake ctest --verbose