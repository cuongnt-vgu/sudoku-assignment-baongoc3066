#include "hidden_singles.h"
#include <stdio.h>
#include <stdlib.h>

int hidden_singles(SudokuBoard *p_board)
{

    int counter = 0;
    HiddenSingle hidden_singles[BOARD_SIZE * BOARD_SIZE];

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        find_hidden_single(p_board->p_rows[i], hidden_singles, &counter);
        find_hidden_single(p_board->p_cols[i], hidden_singles, &counter);
        find_hidden_single(p_board->p_boxes[i], hidden_singles, &counter);
    }

    for (int i = 0; i < counter; i++)
    {
        set_candidates(hidden_singles[i].p_cell, &(hidden_singles[i].value), 1);
    }
    return counter;
}
int find_hidden_single_values(Cell **p_cells, int *hidden_single_values)
{
    int counters = 0;
    int candidate_counter[BOARD_SIZE] = {0};

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (p_cells[i]->num_candidates ==1 )
        {
            continue;
        }

        int *candidates = get_candidates(p_cells[i]);
        for (int j = 0; j < p_cells[i]->num_candidates; j++)
        {
            candidate_counter[candidates[j] - 1] += 1;
        }
        free(candidates);
    }

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (candidate_counter[i] == 1)
        {
            hidden_single_values[counters] = i + 1;
            counters += 1;
        }
    }

    return counters;
}

void find_hidden_single(Cell **p_cells, HiddenSingle *p_hidden_singles,
                        int *p_counter) 
{
    int hidden_single_values[BOARD_SIZE] = {0};
    int number_single_value_found = find_hidden_single_values(p_cells, hidden_single_values);
    for (int i = 0; i < number_single_value_found; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if  (p_cells[j]->num_candidates == 1)
            {
                continue;
            }

            int *candidates = get_candidates(p_cells[j]);
            for (int k = 0; k < p_cells[j]->num_candidates; k++)
            {
                if (candidates[k] == hidden_single_values[i]) 
                {
                    bool exist = false;
                    for (int l = 0; l < *p_counter; l++)
                    {
                        if (p_hidden_singles[l].p_cell == p_cells[j])
                        {
                            exist = true;
                            break;
                        }
                    }

                    if (!exist)
                    {
                        p_hidden_singles[*p_counter].p_cell = p_cells[j];
                        p_hidden_singles[*p_counter].value = hidden_single_values[i];
                        *p_counter += 1;
                        break;
                    }
                }
            }
            free(candidates);
        }
    }
}
