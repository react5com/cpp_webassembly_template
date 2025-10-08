cmake_minimum_required(VERSION 3.15)
project(NlpLib LANGUAGES CXX)

enable_testing()

add_subdirectory(src)
#if(!EMSCRIPTEN)
    add_subdirectory(tests)
#endif()

install(TARGETS NlpLib
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/
    DESTINATION include
    FILES_MATCHING PATTERN "*.hpp"
)