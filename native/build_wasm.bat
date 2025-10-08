@echo off
setlocal enabledelayedexpansion

set "BUILD_DIR=build_wasm"
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
cd "%BUILD_DIR%"

echo Setting up Emscripten environment...
call %USERPROFILE%\emsdk\emsdk_env.bat

echo Building WebAssembly with Emscripten...

rem Configure with Emscripten toolchain
emcmake cmake .. 

rem Build the project
emmake cmake --build . > build_wasm.log 2>&1

rem Check for generated files
if exist WebassemblyTemplate.js (
  if exist WebassemblyTemplate.wasm (
    echo.
    echo Build successful! Files generated in build_wasm directory.
    echo   - WebassemblyTemplate.js: Main JavaScript module
    echo   - WebassemblyTemplate.wasm: WebAssembly binary
    echo   - WebassemblyTemplate.d.ts: TypeScript definitions
  ) else (
    echo Build may have failed. Check for error messages above.
  )
) else (
  echo Build may have failed. Check for error messages above.
)

