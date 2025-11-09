#!/bin/bash
set -euo pipefail

BUILD_DIR=build
BUILD_TYPE=${1:-Release}

NUM_JOBS=$(sysctl -n hw.ncpu 2>/dev/null || echo 1)

mkdir -p "${BUILD_DIR}"
cd "${BUILD_DIR}"

echo "Configuring native build (CMAKE_BUILD_TYPE=${BUILD_TYPE})..."
cmake .. -DCMAKE_BUILD_TYPE="${BUILD_TYPE}" -DCMAKE_TOOLCHAIN_FILE="${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"

echo "Building (jobs=${NUM_JOBS})..."
cmake --build . --config "${BUILD_TYPE}" -- -j"${NUM_JOBS}" 2>&1 | tee build.log

if [ "${PIPESTATUS[0]:-0}" -eq 0 ] || [ "${PIPESTATUS[1]:-0}" -eq 0 ]; then
    echo ""
    echo "Native build successful. Artifacts can be found in: $(pwd)"
else
    echo "Build failed. Check build.log for details."
    exit 1
fi
echo "Running tests..."
ctest --output-on-failure -C "${BUILD_TYPE}"