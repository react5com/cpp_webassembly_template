@echo off
setlocal enabledelayedexpansion

if not defined BUILD_DIR (
    set "BUILD_DIR=build"
)

rem Build type (first arg) default Release
if "%~1"=="" (
    set "BUILD_TYPE=Release"
) else (
    set "BUILD_TYPE=%~1"
)

if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
cd /d "%BUILD_DIR%"

set "NUM_JOBS=%NUMBER_OF_PROCESSORS%"
if "%NUM_JOBS%"=="" set "NUM_JOBS=1"

echo Configuring native build (CMAKE_BUILD_TYPE=%BUILD_TYPE%)...
call cmake .. -DCMAKE_BUILD_TYPE="%BUILD_TYPE%" -DCMAKE_TOOLCHAIN_FILE="%VCPKG_ROOT%/scripts/buildsystems/vcpkg.cmake"

echo Building (jobs=%NUM_JOBS%)...
call cmake --build . --config "%BUILD_TYPE%" -- /m:%NUM_JOBS% > build.log 2>&1
if %ERRORLEVEL% neq 0 (
    echo Build failed. Check build.log for details.
    exit /b 1
)

echo.
echo Native build successful. Artifacts can be found in: %CD%

echo Running tests...
call ctest --output-on-failure -C "%BUILD_TYPE%"
endlocal
