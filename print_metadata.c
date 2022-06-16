#include "main.h"

void print_metadata(Metadata* list, int len, int selection, int offset){
	int row = 0, col = 0;
	bsize(&row, &col);
	--row;
	int start = max(0, selection-row+1+offset);
	int end = min(len, row+start);
	for(int i = start; i < end; i++){
		if (selection == i) fputc('>', stdout);
		else fputc(' ', stdout);
		fputs(list[i].name, stdout);
		if (selection == i) fputc('<', stdout);
		else fputc(' ', stdout);
		for(int j = 0; j < 15-strlen(list[i].name); j++){
			fputc(' ', stdout);
		}
		fputc('\t', stdout);
		fputs(list[i].val, stdout);
		fputc('\n', stdout);
	}
}
