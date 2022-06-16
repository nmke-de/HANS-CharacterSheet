#include "main.h"

void print_attributes(Attribute* list, int len, int selection, int offset){
	int row = 0, col = 0;
	bsize(&row, &col);
	--row;
	int start = max(0, selection-row+1+offset);
	int end = min(len, row+start);
	for(int i = start; i < end; i++){
		if (selection == i) bputc('>');
		else bputc(' ');
		bputs(list[i].name);
		if (selection == i) bputc('<');
		else bputc(' ');
		for(int j = 0; j < 11-strlen(list[i].name); j++){
			bputc(' ');
		}
		bputc('\t');
		bputs(itoa(list[i].val * 2, 10));
		bputc('\t');
		bputs(itoa(list[i].val, 10));
		bputc('\t');
		bputs(itoa(list[i].val * 2/5, 10));
		bputc('\n');
	}
}
