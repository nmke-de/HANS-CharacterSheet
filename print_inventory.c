#include "main.h"

void print_inventory(Item *list, int len_i, int selection, int offset){
	int row = 0, col = 0;
	bsize(&row, &col);
	--row;
	int start = max(0, selection-row+1+offset);
	int end = min(len_i, row+start);
	for(int i = start; i < end; i++){
		if (selection == i) fputs(">> ", stdout);
		else fputs("   ", stdout);
		fputs(itoa(list[i].count, 10), stdout);
		fputc('\t', stdout);
		fputs(list[i].name, stdout);
		fputc('\n', stdout);
	}
}
