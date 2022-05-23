#include <stdio.h>
#include <stdlib.h>

#include "chunky/display.h"

DisplayConfig config = {
    .scale = 3, .width = 320, .height = 256, .windowTitle = "Proc Gen Mesh"};

int main(int args, char* argv[]) {
  Run(config);
  exit(0);
}
