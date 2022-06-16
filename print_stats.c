#include "main.h"

void print_stats(Stat* list, int len, int selection, int offset){
	int row = 0, col = 0;
	bsize(&row, &col);
	--row;
	int start = max(0, selection-row+1+offset);
	int end = min(len, row+start);
	for(int i = start; i < end; i++){
		// Determine contributing base attribute
		int max_attr = 0;
		if (list[i].type[0] != NULL && list[i].type[1] != NULL) max_attr = max(list[i].type[0]->val, list[i].type[1]->val);
		else if (list[i].type[0] != NULL) max_attr = list[i].type[0]->val;
		if (selection == i) fputc('>', stdout);
		else fputc(' ', stdout);
		fputs(list[i].name, stdout);
		if (selection == i) fputc('<', stdout);
		else fputc(' ', stdout);
		for(int j = 0; j < MAX_STAT_NAME-strlen(list[i].name); j++){
			fputc(' ', stdout);
		}
		fputc('\t', stdout);
		fputs(map_attr(list[i].type[0]), stdout);
		if (list[i].type[1] != NULL) {
			fputc('/', stdout);
			fputs(map_attr(list[i].type[1]), stdout);
		}
		fputc('\t', stdout);
		fputs(itoa((list[i].val + max_attr), 10), stdout);
		fputc('\t', stdout);
		fputs(itoa((list[i].val + max_attr) / 2, 10), stdout);
		fputc('\t', stdout);
		fputs(itoa((list[i].val + max_attr) / 5, 10), stdout);
		fputc('\n', stdout);
	}
}
