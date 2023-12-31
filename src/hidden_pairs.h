#pragma once

#include "sudoku.h"
typedef struct HiddenPairs_impl
{
    Cell *cell1;
    Cell *cell2;
    int *arr;  
} HiddenPairs;

int hidden_pairs(SudokuBoard *p_board);
void find_hidden_pairs(Cell **p_cells, HiddenPairs *hidden_pairs, int *p_counter);


