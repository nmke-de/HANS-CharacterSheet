#include "main.h"

void print_skills(char **list, int len_i, int selection, int offset){
	int row = 0, col = 0;
	bsize(&row, &col);
	--row;
	int start = max(0, selection-row+1+offset);
	int end = min(len_i, row+start);
	for(int i = start; i < end; i++){
		if (selection == i) bputc('>');
		else bputc(' ');
		bputs(list[i]);
		if (selection == i) bputc('<');
		else bputc(' ');
		bputc('\n');
	}
}
