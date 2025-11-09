cmake_minimum_required(VERSION 3.13)
project(WebassemblyTemplate LANGUAGES CXX)
# Set C++ standard to 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# These checks are time-consuming to run on every build,
# run it manually with "npm run lint" or as part of the CI pipeline.
# Enable clang-tidy if available
# find_program(CLANG_TIDY_EXE NAMES clang-tidy)
# if(CLANG_TIDY_EXE)
#     message(STATUS "Found clang-tidy: ${CLANG_TIDY_EXE}")
#     set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE};-format-style=file;-extra-arg=-std=c++20")
# endif()

# # Optionally enable cppcheck
# find_program(CPPCHECK_EXE NAMES cppcheck)
# if(CPPCHECK_EXE)
#     message(STATUS "Found cppcheck: ${CPPCHECK_EXE}")
#     set(CMAKE_CXX_CPPCHECK
#         "${CPPCHECK_EXE};--enable=all;--inconclusive;--force;--std=c++20")
# endif()

include(CTest)
enable_testing()
# Build NlpLib first
add_subdirectory(libs/NlpLib)

file(GLOB_RECURSE ALL_CXX_SOURCE_FILES
    "${CMAKE_SOURCE_DIR}/libs/**/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/libs/**/src/*.hpp"
)

if(NOT ALL_CXX_SOURCE_FILES)
  message(WARNING "No C++ source files found with pattern ${CMAKE_SOURCE_DIR}/libs/**/*.cpp")
else()
  list(LENGTH ALL_CXX_SOURCE_FILES _num_sources)
  message(STATUS "Found ${_num_sources} C++ source file(s)")
endif()

add_custom_target(lint
    COMMAND clang-tidy ${ALL_CXX_SOURCE_FILES}
    # -p ${CMAKE_BINARY_DIR} # json-compilation-database causes errors finding std libs on macOS
    --extra-arg=-std=c++20
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Running clang-tidy on all source files ${CMAKE_SOURCE_DIR}"
)

add_custom_target(format
    COMMAND clang-format -i ${ALL_CXX_SOURCE_FILES}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Formatting all source files"
)

add_custom_target(static_analysis
    COMMAND cppcheck --enable=all --inconclusive --force --std=c++20 ${ALL_CXX_SOURCE_FILES}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Running cppcheck on all source files"
)
# Emscripten-specific configuration
if(EMSCRIPTEN)
  add_executable(WebassemblyTemplate src/wasm_main.cpp)
  #target_link_libraries(WebassemblyTemplate PRIVATE -Wl,--whole-archive NlpLib -Wl,--no-whole-archive)
  target_link_libraries(WebassemblyTemplate PRIVATE NlpLib)

  # Set output directory for web files
  set_target_properties(WebassemblyTemplate PROPERTIES
      OUTPUT_NAME "WebassemblyTemplate"
      SUFFIX ".js"
  )
  
  if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(WebassemblyTemplate PRIVATE
        "SHELL:-fsanitize=address"
        "SHELL:-fsanitize-blacklist=${CMAKE_SOURCE_DIR}/lsan_suppressions.txt"
        #"SHELL:-fno-omit-frame-pointer"
    )
    target_link_options(WebassemblyTemplate PRIVATE
        "SHELL:-fsanitize=address"
    )
  endif()
  # Emscripten-specific linker flags
  target_link_options(WebassemblyTemplate PRIVATE
      "SHELL:-sALLOW_MEMORY_GROWTH=1"
      "SHELL:-sMODULARIZE=1"
      "SHELL:-sEXPORT_ES6=1"
      "SHELL:-lembind"
      "SHELL:--emit-tsd WebassemblyTemplate.d.ts"
      "SHELL:-sEXIT_RUNTIME=0"
      "SHELL:-gsource-map"
      "SHELL:-std=c++20"
      "SHELL:-sEXPORTED_RUNTIME_METHODS='[\"ccall\"]'"
  )
#   em++ ../src/main.cpp -o a.out.js -gsource-map -fsanitize=address \
#   -sEXPORTED_RUNTIME_METHODS='["ccall","cwrap"]' \
#   -sALLOW_MEMORY_GROWTH -sEXIT_RUNTIME=0 \
#   --emit-tsd interface.d.ts -sMODULARIZE -sEXPORT_ES6 \
#   -std=c++20 -lembind

  target_include_directories(WebassemblyTemplate PRIVATE "$ENV{EMSDK_DIR}/upstream/emscripten/system/include")
endif()