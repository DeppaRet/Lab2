#include <iostream>
#include <algorithm>
#include "sort.h"
using namespace std;

int shell_sort(int **arr, int rows, int cols, int &comparisons, int &permutations) {
	int tmp, j;
	for (int l = 0; l < cols; l++) {
		for (int k = rows / 2; k > 0; k /= 2) {
			for (int i = k; i < rows; i++) {
				tmp = arr[i][l];
				for (j = i; j >= k; j -= k) {
					comparisons++;
					if (tmp > arr[j - k][l]) {
						arr[j][l] = arr[j - k][l];
						permutations += 2;
					}
					else
						break;
				}
				arr[j][l] = tmp;
			}
		}
	}
	return 0;
}


void bubble_sort(int **arr, int rows, int cols, int &comparisons, int &permutations) {
	int temp;
	for (int j = 0; j < cols; j++) {
		for (int i = rows - 1; i > 0; i--) {
			for (int k = 0; k < i; k++){
				comparisons++;
				if (arr[k][j] < arr[k + 1][j]) {
					temp = arr[k][j];
					arr[k][j] = arr[k + 1][j];
					arr[k + 1][j] = temp;
					permutations += 2;
				}
			}
		}
	}
}


void selection_sort(int **arr, int rows, int cols, int &comparisons, int &permutations) {
	for (int l = 0; l < cols; l++) {
		for (int i = 0; i < rows - 1; i++) {
			int max_i = i;
			for (int j = i + 1; j < rows; j++) {
				comparisons++;
				if (arr[j][l] > arr[max_i][l]) {
					max_i = j;
				}
			}

			if (max_i != i) {
				int tmp;
				tmp = arr[i][l];
				arr[i][l] = arr[max_i][l];
				arr[max_i][l] = tmp;
				max_i = i;
				permutations += 2;
			}
		}
	}
}

void insert_sort(int ** arr, int cols, int rows, int &comparisons, int &permutations){
	int key;
	int j;
	for (int l = 0; l < cols; l++) {
		for (int i = 1; i < rows; i++) {
			key = arr[i][l];
			j = i - 1;
			comparisons++;
			while ((j >= 0) && (arr[j][l] < key)) {
				comparisons++;
				arr[j + 1][l] = arr[j][l];
				j = j - 1;
				permutations++;
			}
			arr[j + 1][l] = key;
			permutations++;
		}
	}
}


void fast_sort(int **arr, int cur_idx, bool allow_cycle, int rows, int cols, int top_lim, int &comparisons, int &permutations) {
	if (allow_cycle) {
		for (cur_idx; cur_idx < cols; cur_idx++) {
			int mid, tmp;
			int top_border = top_lim, bot_border = rows;
			mid = arr[(top_border + bot_border) / 2][cur_idx];
			do {
				while (arr[top_border][cur_idx] > mid) {
					top_border++;
					comparisons += 1;
				}
				while (arr[bot_border][cur_idx] < mid) {
					bot_border--;
					comparisons += 1;
				}
				if (top_border <= bot_border) {
					tmp = arr[top_border][cur_idx];
					arr[top_border][cur_idx] = arr[bot_border][cur_idx];
					arr[bot_border][cur_idx] = tmp;
					permutations += 1;
					top_border++;
					bot_border--;
				}
			} while (top_border < bot_border);
			if (top_lim < bot_border) {
				fast_sort(arr, cur_idx, false, bot_border, cols, top_lim, comparisons, permutations);
			}
			if (top_border < rows) {
				fast_sort(arr, cur_idx, false, rows, cols, top_border, comparisons, permutations);
			}
		}
	}
	else {
		int mid, tmp;
		int top_border = top_lim, bot_border = rows;
		mid = arr[(top_border + bot_border) / 2][cur_idx];
		do {
			while (arr[top_border][cur_idx] > mid) {
				top_border++;
				comparisons += 1;
			}
			while (arr[bot_border][cur_idx] < mid) {
				bot_border--;
				comparisons += 1;
			}
			if (top_border <= bot_border) {
				tmp = arr[top_border][cur_idx];
				arr[top_border][cur_idx] = arr[bot_border][cur_idx];
				arr[bot_border][cur_idx] = tmp;
				permutations += 1;
				top_border++;
				bot_border--;
			}
		} while (top_border < bot_border);

		if (top_lim < bot_border) {
			fast_sort(arr, cur_idx, false, bot_border, cols, top_lim, comparisons, permutations);
		}
		if (top_border < rows) {
			fast_sort(arr, cur_idx, false, rows, cols, top_border, comparisons, permutations);
		}
	}

}


