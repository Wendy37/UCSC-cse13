#include "universe.h"
#include <errno.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define Delay 50000
#define OPTIONS "tsn:i:o:"

int get_rc(FILE *infile, int *rows, int *cols) {
  fscanf(infile, "%d %d", rows, cols);
  return 0;
}

void initialize(Universe *u) {
  for (int i = 0; i < uv_rows(u); i++) {
    for (int j = 0; j < uv_cols(u); j++) {
      uv_dead_cell(u, i, j);
    }
  }
}

void swap_pointer(Universe *(*a), Universe *(*b)) {
  Universe *temp = *a;
  *a = *b;
  *b = temp;
}

int new_gen(Universe *current, Universe *new) {
  for (int i = 0; i < uv_rows(current); i++) {
    for (int j = 0; j < uv_cols(current); j++) {
      if (uv_get_cell(current, i, j) &&
          (uv_census(current, i, j) == 2 ||
           uv_census(current, i, j) == 3)) { // rule 1
        uv_live_cell(new, i, j);
      } else if (!uv_get_cell(current, i, j) && uv_census(current, i, j) == 3) {
        uv_live_cell(new, i, j); // rule 2
      } else {                   // rule 3
        uv_dead_cell(new, i, j);
      }
    }
  }
  return 0;
}

int ncurses(Universe *A, Universe *B, int generation) {
  initscr();
  noecho();
  curs_set(FALSE);
  for (int gen = 0; gen < generation; gen++) {
    clear();
    for (int i = 0; i < uv_rows(A); i++) {
      for (int j = 0; j < uv_cols(A); j++) {
        if (uv_get_cell(A, i, j)) {
          mvprintw(i, j, "o");
          refresh();
        } else {
          mvprintw(i, j, " ");
          refresh();
        }
      }
    }
    usleep(Delay);
    new_gen(A, B);
    swap_pointer(&A, &B);
  }
  endwin();
  return 0;
}

int ncurses_s(Universe *A, Universe *B, int generation) {
  for (int i = 0; i < generation; i++) {
    new_gen(A, B);
    swap_pointer(&A, &B);
  }
  return 0;
}

int main(int argc, char **argv) {
  int opt = 0;
  FILE *infile = stdin;
  FILE *outfile = stdout;
  int rows = 0;
  int cols = 0;
  bool toroidal = false;
  bool silence = false;
  char temp[100];
  int generation = 100;
  while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
    switch (opt) {
    case 't':
      toroidal = true;
      break;
    case 's':
      silence = true;
      break;
    case 'n':
      strcpy(temp, optarg);
      sscanf(temp, "%d", &generation);
      break;
    case 'i':
      if (optarg != NULL) {
        infile = fopen(optarg, "r");
      }

      if (infile == NULL || errno == EINVAL) {
        fprintf(stderr, "%s is an invalid file.\n", optarg);
        exit(1);
      }
      break;
    case 'o':
      if (optarg != NULL) {
        outfile = fopen(optarg, "w");
      }
      break;
    default:
      fprintf(stderr, "Usage: %s -[tsnio]\n", argv[0]);
    }
  }
  get_rc(infile, &rows, &cols);

  Universe *A = uv_create(rows, cols, toroidal);
  Universe *B = uv_create(rows, cols, toroidal);

  initialize(A);
  initialize(B);

  if (uv_populate(A, infile) == false) {
    fprintf(stderr, "Failed to populate the universe.\n");
    exit(1);
  }

  if (silence == true) {
    ncurses_s(A, B, generation);
  } else if (silence == false) {
    ncurses(A, B, generation);
  }

  uv_print(A, outfile);
  uv_delete(A);
  uv_delete(B);

  return 0;
}
