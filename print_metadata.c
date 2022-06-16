#include "main.h"

void print_metadata(Metadata* list, int len, int selection, int offset){
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
		for(int j = 0; j < 15-strlen(list[i].name); j++){
			bputc(' ');
		}
		bputc('\t');
		bputs(list[i].val);
		bputc('\n');
	}
}
