#include <stdio.h>
#include <stdlib.h>

#include "Display.h"

DisplayConfig config = {
    .scale = 3, .width = 320, .height = 256, .windowTitle = "Chunky"};

int main(int args, char* argv[]) {
  Run(config);
  exit(0);
}
