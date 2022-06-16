#include "main.h"

void read_stats(Stat *stats, int len_s, FILE *f, Attribute *attrs) {
	int j = 0;
	char buf[MAX_STAT_NAME];
	int i, ref0, ref1;
	do {
		i = 0;
		ref0 = -1;
		ref1 = -1;
		// Read statname
		while (i < MAX_STAT_NAME && (buf[i] = fgetc(f)) != '\t' && buf[i] != EOF && buf[i] != '\n') i++;
		if (buf[i] == EOF || buf[i] == '\n') break; // Error
		for (; i < MAX_STAT_NAME; i++) buf[i] = 0;
		strncpy(stats[j].name, buf, i);
		// Read base stat 1
		if ((ref0 = fgetc(f) - '0') < -1 || ref0 > 5) break; // Error
		else if (ref0 == -1) stats[j].type[0] = NULL; // No base stat
		else stats[j].type[0] = &(attrs[ref0]);
		// Read possible base stat 2
		if ((ref1 = fgetc(f) - '0') == -38 /*'\n' - '0'*/) {stats[j].type[1] = NULL; goto loopend;} // No base stat 2
		else if (ref1 >= 0 || ref1 <= 5) stats[j].type[1] = &(attrs[ref1]); // No base stat 2
		else break;
		if(fgetc(f) != '\n') break; // Error
loopend:
		++j;
	} while (j < len_s);
}
