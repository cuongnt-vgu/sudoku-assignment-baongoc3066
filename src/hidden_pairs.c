#include "hidden_pairs.h"
#include <stdio.h>
#include <stdlib.h>
int hidden_pairs(SudokuBoard *p_board)
{
    int counter = 0;
    HiddenPairs hidden_pairs[BOARD_SIZE * BOARD_SIZE];

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        find_hidden_pairs(p_board->p_rows[i], hidden_pairs, &counter);
        find_hidden_pairs(p_board->p_cols[i], hidden_pairs, &counter);
        find_hidden_pairs(p_board->p_boxes[i], hidden_pairs, &counter);
    }

    for (int i = 0; i < counter; i++)
    {
        set_candidates(hidden_pairs[i].cell1, hidden_pairs[i].arr, 2);
        set_candidates(hidden_pairs[i].cell2, hidden_pairs[i].arr, 2);
    }

    for (int i = 0; i < counter; i++)
    {
        free(hidden_pairs[i].arr);
    }
    return counter;
}

void find_hidden_pairs(Cell **p_cells, HiddenPairs *p_hidden_pairs, int *p_counter)
{
    int hidden_pair_values[BOARD_SIZE] = {0};
    int candidate_counter[BOARD_SIZE] = {0};
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (p_cells[i]->fixed || p_cells[i]->num_candidates == 1)
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
    int counter = 0;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (candidate_counter[i] == 2)
        {
            hidden_pair_values[counter] = i + 1;
            counter++;
        }
    } 

    for (int m = 0; m < counter - 1; m++)
    {
        for (int n = m + 1; n < counter; n++)
        {
            int *pair = malloc(sizeof(int) * 2);
            pair[0] = hidden_pair_values[m];
            pair[1] = hidden_pair_values[n];
            bool flagged = false;
            int counters = 0;
            for (int i = 0; i < BOARD_SIZE; i++)
            {
                if (p_cells[i]->fixed || p_cells[i]->num_candidates <= 2)
                    continue;
                int *candidates = get_candidates(p_cells[i]);
                int same = 0;
                for (int j = 0; j < p_cells[i]->num_candidates; j++)
                {
                    if (candidates[j] == pair[0] || candidates[j] == pair[1])
                    {
                        same++;
                    }
                }
                if (same == 2)
                {
                    if (!flagged)
                    {
                        p_hidden_pairs[*p_counter].cell1 = p_cells[i];
                        flagged = true;
                    }
                    else
                    {
                        p_hidden_pairs[*p_counter].cell2 = p_cells[i];
                    }
                    counters++;
                }

                free(candidates);
            }
            if (counters != 2) 
            {
                free(pair);
                continue;
            }
            bool exist = false;
            for (int i = 0; i < *p_counter; i++)
            {
                if (p_hidden_pairs[i].cell1 == p_hidden_pairs[*p_counter].cell1 && p_hidden_pairs[i].cell2 == p_hidden_pairs[*p_counter].cell2)
                {
                    exist = true;
                    break;
                }
            }
            if (!exist)
            {
                p_hidden_pairs[*p_counter].arr = pair;
                *p_counter += 1;
            }
            else
            {
                free(pair);
            }
        }
    }
}