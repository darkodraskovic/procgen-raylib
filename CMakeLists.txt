cmake_minimum_required(VERSION 3.8)
project (boilerplate)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_C_STANDARD 11)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(lib/chunky)
add_subdirectory(lib/roamlib)

function(add_target TARGET INCLUDES LIBS)
  file(GLOB APP_C "src/${TARGET}/*.c")
  add_executable(${TARGET} ${APP_C})
  target_include_directories(${TARGET} PUBLIC "${TARGET}/" ${INCLUDES})
  target_link_libraries(${TARGET} m raylib dl pthread ${LIBS})
endfunction()

add_target(00_hello_world "" "")
add_target(01_fractals "" "")
add_target(02_images "" "")
add_target(03_tcod "" tcod)
add_target(04_chunky_roam "lib/" "chunky;roamlib")
