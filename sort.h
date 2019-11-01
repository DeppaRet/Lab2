#pragma once
int shell_sort(int **arr, int cols, int rows, int &comparisons, int &permutations);
void bubble_sort(int **arr, int rows, int cols, int &comparisons, int &permutations);
void selection_sort(int **arr, int cols, int rows, int &comparisons, int &permutations);
void insert_sort(int **arr, int cols, int rows, int &comparisons, int &permutations);
void fast_sort(int **arr, int cur_idx, bool allow_cycle, int rows, int cols, int top_lim, int &comparisons, int &permutations);