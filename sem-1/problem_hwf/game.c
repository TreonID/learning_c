#include <stdio.h>
#include <stdlib.h>

#include "logic.h"

#define MAX_TURNS 200
#define MAX_MATCHES 200

int read_value() {
  int res, x;
  res = scanf("%d", &x); 
  if (res != 1) {
    fprintf(stderr, "Input error\n");
    abort();
  }
  return x;
}


void print_hello_total(int try) {
  if (try == 0)
    printf("Hello, it's fibonacci game!\nHow many matches will there be at the start?\n");
  else
    printf("Please, try again\n");  
  printf("From 2 to %d:\n", MAX_MATCHES);
}


void print_who_first(int try) {
  if (try == 0)
    printf("Ok, who takes first?\n");
  else
    printf("Bad choise, try again, who takes first?\n");
  printf("1 - You\n2 - PC\n");
}


void print_turn_player(int try, int max_to_get) {
  if (try == 0)
    printf("How many matches do you want to take? ");
  else
    printf("Bad choise, try again. How many matches do you want to take? ");
  printf("From 1 to %d\n", max_to_get);
}


void print_short_result(int total, int *turns, int count) {
  printf("%d:", total);
  for (int i = 0; i < count; ++i) {
    if (i+1 != count)
      printf("%d,", turns[i]);
    else
      printf("%d!", turns[i]);
  }
  printf("\n");
}

void game_start(int silent_interface) {

  int total = 0, total_on_start = 0, who_turn = 0, try = 0;
  int max_to_get = 0, turn = 0;
  int turns[MAX_TURNS] = {0};
  int turn_id = 0;

  while ( !((total >= 2) && (total <= MAX_MATCHES)) ) {
    if (!silent_interface)
      print_hello_total(try);
    try++;
    total = read_value();
  }
  
  max_to_get = total - 1;
  total_on_start = total;

  try = 0;
  while((who_turn != 1) && (who_turn != 2)) {
    if (!silent_interface)
      print_who_first(try);
    try++;
    who_turn = read_value();
  }
  
 
  while(max_to_get < total) {
    if (!silent_interface)
      printf("Total matches: %d Max to get: %d\n", total, max_to_get);

    if (who_turn == 1) {
      try = 0;
      turn = 0;
      while ( !((turn >= 1) && (turn <= max_to_get)) ) {
        if (!silent_interface)
          print_turn_player(try, max_to_get);
        try++;
        turn = read_value();
      }
      if (!silent_interface)
        printf("You get %d matches\n\n", turn);

    }
    
    if (who_turn == 2) {
        turn = next_turn(total, max_to_get);
        if (!silent_interface)
          printf("PC get %d matches\n\n", turn);
    }
    total = total - turn;
    turns[turn_id] = turn;
    turn_id++;
    max_to_get = 2 * turn;
    who_turn = (who_turn == 1) ? 2 : 1;
  }
  
  if (!silent_interface) {
    printf("Total matches: %d Max to get: %d\n", total, max_to_get);
    if(who_turn == 2)
      printf("You lost, try again, study the algorithms ;)\n");
    else
      printf("You won, hooray!\n");
  }
  print_short_result(total_on_start, turns, turn_id);
}
