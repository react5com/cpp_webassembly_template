#!/bin/bash
#set -euo pipefail

BUILD_DIR=build_wasm
BUILD_TYPE=${1:-Release}
NUM_JOBS=$(sysctl -n hw.ncpu 2>/dev/null || echo 1)
mkdir -p "${BUILD_DIR}"
cd "${BUILD_DIR}"

EMSDK=~/emsdk
if [ ! -d "${EMSDK}" ]; then
    echo "Emscripten SDK not found in ${EMSDK}."
    echo "Please install it by following the instructions at https://emscripten.org/docs/getting_started/downloads.html"
    exit 1
fi

echo "Setting up Emscripten environment..."
source ${EMSDK}/emsdk_env.sh

echo "Building WebAssembly with Emscripten..."

# Configure with Emscripten toolchain
emcmake cmake .. -DCMAKE_BUILD_TYPE="${BUILD_TYPE}" #-DCMAKE_VERBOSE_MAKEFILE=ON

# Build the project
emmake cmake --build . --config "${BUILD_TYPE}" -- -j"${NUM_JOBS}" 2>&1 | tee build.log
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

#emmake ctest --verbose