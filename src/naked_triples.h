#pragma once

#include "sudoku.h"
typedef struct NakedTriples_impl
{
    Cell *cells[3];
} Triple;




int naked_triples(SudokuBoard *p_board);