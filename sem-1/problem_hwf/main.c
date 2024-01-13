#include <stdio.h>
#include <stdlib.h>

#include "game.h"

int main(int argc, char *argv[]) {
  if (argc == 2) {
    if (argv[1][0] == '-' && argv[1][1] == 's')
      game_start(1);
    else 
      printf("Fibonacci game. Use -s argument for silent mode. Run without arguments for normal mode.\n");
  } else {
    game_start(0);
  }
}
