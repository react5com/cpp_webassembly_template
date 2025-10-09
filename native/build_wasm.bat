@echo off
setlocal enabledelayedexpansion

if not defined BUILD_DIR (
    set "BUILD_DIR=build_wasm"
)
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
cd "%BUILD_DIR%"

if not defined EMSDK (
    set "EMSDK=%USERPROFILE%\emsdk"
)
if not exist "%EMSDK%" (
    echo "Emscripten SDK not found in %EMSDK%."
    echo "Please install it by following the instructions at https://emscripten.org/docs/getting_started/downloads.html"
    exit 1
)

echo "Setting up Emscripten environment..."
call %EMSDK%\emsdk_env.bat

echo Building WebAssembly with Emscripten...

rem Configure with Emscripten toolchain
call emcmake cmake .. 

rem Build the project
call emmake cmake --build . > build_wasm.log 2>&1

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

