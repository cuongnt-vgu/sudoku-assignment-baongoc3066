#pragma once

#include "sudoku.h"

typedef struct NakedPairs_impl
{
    Cell *p_cell1;
    Cell *p_cell2;

    int value1;
    int value2;
} NakedPairs;



void unset_pairs(Cell **p_cells, int value1, int value2, Cell *p_cell1, Cell *p_cell2);

void find_naked_pairs(Cell **p_cells, NakedPairs *p_naked_pairs, int *p_counter);
int naked_pairs(SudokuBoard *p_board);