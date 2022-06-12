cmake_minimum_required(VERSION 3.8)
project (procgen)

if (WIN32)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/bin")
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/bin")
else()
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
endif()

set(CMAKE_C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(TCOD tcod)
if (WIN32)
  set(TCOD libtcod)
  
  include_directories(lib/ lib/raylib/include lib/libtcod/include)
  link_directories(lib/raylib/lib lib/libtcod)
  link_libraries(libtcod raylib)

  set(warning_compiler_options /W3 /wd"4267" /wd"4305" /wd"4244")
  # /Ox used for raygui.h
  # /Od disables optimization to speed compilation.
  # /Ob controls inline function expansion.
  add_compile_options(${warning_compiler_options} /MD /Od /Ob0 /JMC)
endif()

add_subdirectory(lib/chunky)
add_subdirectory(lib/roamlib)

function(add_target TARGET INCLUDES LIBS)
  file(GLOB APP_C "src/${TARGET}/*.c")
  add_executable(${TARGET} ${APP_C})
  target_include_directories(${TARGET} PUBLIC "${TARGET}/" ${INCLUDES})
  
  if (WIN32)
    target_link_libraries(${TARGET} raylib opengl32 winmm ${LIBS})
  else()
    target_link_libraries(${TARGET} m raylib dl pthread ${LIBS})
  endif()
  
endfunction()

add_target(00_hello_world "" "")
add_target(01_fractals "" "")
add_target(02_images "" "")
add_target(03_tcod "" ${TCOD})
add_target(04_roamlib "lib/" "chunky;roamlib")
add_target(05_mesh "lib/;lib/raygui/src" "chunky;${TCOD}")
