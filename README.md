# Raylib + tcod procedural generation examples in C

2D graphics procedural generation library and examples based on [raylib](https://github.com/raysan5/raylib) and and [tcod](https://github.com/libtcod/libtcod) libraries and written in pure C.

## Install

Build and install [raylib](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux#build-raylib-using-make) and [tcod](https://github.com/libtcod/libtcod/tree/master/buildsys/autotools#building-libtcod) libraries. 

## Configure && build

Create `build` directory in the root directory, `cd` to `build` directory and run

```
cmake ..
```

Staying in `build` directory, type

```
make
```

to compile and run the program.

## Run

Create `bin` directory in the root directory. `cd` to `bin/` and run

```
./main
```

to run the program.

### Run from chunky or roamlib

```
cd /Users/darko/Development/procgen2d/ && bash.exe build.sh -t 05_mesh
```

## clangd

"clangd understands your C++ code and adds smart features to your editor: code completion, compile errors, go-to-definition and more."

Install [clangd](https://clangd.llvm.org/installation.html).

When you `cmake` the project, `compile_commands.json` will be created in `build` directory. Symlink it (or simply copy it) to the root directory. To symlink it, `cd` to the root and

```
ln -s build/compile_commands.json .
```
