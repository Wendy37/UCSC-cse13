#include "universe.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Universe {
  int rows;
  int cols;
  bool **grid;
  bool toroidal;
};

Universe *uv_create(int rows, int cols, bool toroidal) {
  Universe *u = (Universe *)calloc(4, sizeof(Universe));
  u->rows = rows;
  u->cols = cols;
  u->toroidal = toroidal;
  u->grid = (bool **)calloc(rows, sizeof(bool *));
  for (int i = 0; i < rows; i++) {
    u->grid[i] = (bool *)calloc(cols, sizeof(bool));
  }
  return u;
}

bool uv_toroidal(Universe *u) { return u->toroidal; }

int uv_rows(Universe *u) { return u->rows; }

int uv_cols(Universe *u) { return u->cols; }

void uv_delete(Universe *u) {
  for (int i = 0; i < uv_rows(u); i++) {
    free(u->grid[i]);
  }
  free(u->grid);
  free(u);
  return;
}

bool uv_inbound(Universe *u, int r, int c) {
  if ((r >= uv_rows(u)) || (c >= uv_cols(u)) || (r < 0) || (c < 0)) {
    return false;
  } else {
    return true;
  }
}

void uv_live_cell(Universe *u, int r, int c) {
  if (uv_inbound(u, r, c)) {
    u->grid[r][c] = true;
  }
  return;
}

void uv_dead_cell(Universe *u, int r, int c) {
  if (uv_inbound(u, r, c)) {
    u->grid[r][c] = false;
  }
  return;
}

bool uv_get_cell(Universe *u, int r, int c) {
  if (uv_inbound(u, r, c)) {
    return u->grid[r][c];
  } else {
    return false;
  }
}

bool uv_populate(Universe *u, FILE *infile) {
  int row, col;
  bool format = true;
  int count = 0;
  while (!feof(infile) && format == true) {
    count = fscanf(infile, "%d %d\n", &row, &col);
    if (count != 2 || !uv_inbound(u, row, col)) {
      format = false;
    } else {
      uv_live_cell(u, row, col);
    }
  }
  return format;
}

int new_row(int rows, int r) { // rows is the univers' number of rows, r is the
                               // of cell which is out of bounds.
  int r_n = r;
  if (r < 0) {
    r_n = (rows + r) % rows;
  } else if (r >= rows) { // r = rows
    r_n = (rows - r) % rows;
  }
  return r_n; // r is alternative row
}

int new_col(int cols, int c) { // cols is the univers' number of cols, c is the
                               // of cell which is out of bounds.
  int c_n = c;
  if (c < 0) {
    c_n = (cols + c) % cols;
  } else if (c >= cols) { // r = rows
    c_n = (cols - c) % cols;
  }
  return c_n; // c is alternative col
}

int uv_census(Universe *u, int r, int c) {
  int live = 0;
  if (!uv_toroidal(u)) { // flat universe
    for (int i = c - 1; i < c + 2; i++) {
      if (uv_inbound(u, r - 1, i) && uv_get_cell(u, r - 1, i)) {
        live++;
      }
    }
    for (int i = c - 1; i < c + 2; i += 2) {
      if (uv_inbound(u, r, i) && uv_get_cell(u, r, i)) {
        live++;
      }
    }
    for (int i = c - 1; i < c + 2; i++) {
      if (uv_inbound(u, r + 1, i) && uv_get_cell(u, r + 1, i)) {
        live++;
      }
    }
  } else { // toroidal universe
    for (int i = c - 1; i < c + 2; i++) {
      if (uv_inbound(u, r - 1, i) && uv_get_cell(u, r - 1, i)) {
        live++;
      } else if (!uv_inbound(u, r - 1, i) &&
                 uv_get_cell(u, new_row(uv_rows(u), r - 1),
                             new_col(uv_cols(u), i))) {
        live++;
      }
    }
    for (int i = c - 1; i < c + 2; i += 2) {
      if (uv_inbound(u, r, i) && uv_get_cell(u, r, i)) {
        live++;
      } else if (!uv_inbound(u, r, i) && uv_get_cell(u, new_row(uv_rows(u), r),
                                                     new_col(uv_cols(u), i))) {
        live++;
      }
    }
    for (int i = c - 1; i < c + 2; i++) {
      if (uv_inbound(u, r + 1, i) && uv_get_cell(u, r + 1, i)) {
        live++;
      } else if (!uv_inbound(u, r + 1, i) &&
                 uv_get_cell(u, new_row(uv_rows(u), r + 1),
                             new_col(uv_cols(u), i))) {
        live++;
      }
    }
  }
  return live;
}

void uv_print(Universe *u, FILE *outfile) {
  for (int i = 0; i < uv_rows(u); i++) {
    for (int j = 0; j < uv_cols(u); j++) {
      if (uv_get_cell(u, i, j) == true) {
        fprintf(outfile, "%s", "o");
      } else {
        fprintf(outfile, "%s", ".");
      }
    }
    fprintf(outfile, "%s", "\n");
  }
  fclose(outfile);
}
