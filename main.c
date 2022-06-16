#include <stdlib.h>
#include "main.h"

int main(int argc, char **argv){
	// filename
	char *filename = argc > 1 ? argv[1] : "CHAR";
	if(access(filename, R_OK|W_OK) != 0) return 1;
	// Init BarnabasBox
	binit();
	// User input
	char c;
	// Selected item
	int selection = 0;
	// Read values
	FILE *f = fopen(filename, "rb");
	// Read hitpoints
	int hitpoints = fgetc(f);
	// Read attribute and stat values
	int len_a = 6;
	Attribute *attrs = alloca(sizeof(Attribute) * len_a);
	{
		char *attr_names[6] = {"Stärke", "Geschick", "Intelligenz", "Bildung", "Charisma", "Glück"};
		for(int i = 0; i < len_a; i++) {
			attrs[i].name = attr_names[i];
			attrs[i].val = fgetc(f);
		}
	}
	int len_i = fgetc(f); // Number of inventory items
	int new_len_i = len_i; // Handle deleted items
	int len_s = fgetc(f); // Number of stats
	int new_len_s = len_s; // Handle deleted stats
	Stat *stats = malloc(sizeof(Stat) * len_s); // Array of stats
	for(int i = 0; i < len_s; i++) {
		stats[i] = default_stat();
		stats[i].val = fgetc(f);
	}
	//fclose(f);
	// Read statnames
	// Read also the attribute each stat is based on!
	//f = fopen(filename2, "r");
	read_stats(stats, len_s, f, attrs);
	//fclose(f);
	// Read inventory
	Item *inventory = malloc(sizeof(Item) * len_i);
	//f = fopen(filename3, "r");
	for (int j = 0; j < len_i; j++) {
		char tmp;
		int i = 0;
		inventory[j] = default_item();
		// Read item count
		char buf[MAX_INV_NAME];
		while (i < 9 && (buf[i] = fgetc(f)) != EOF && buf[i] <= '9' && buf[i] >= '0') i++;
		if (buf[i] == EOF) break; //Error
		for (; i < 9; i++) buf[i] = 0;
		inventory[j].count = atoi(buf);
		i = 0;
		// Read item name
		while (i < MAX_INV_NAME && (buf[i] = fgetc(f)) != EOF && buf[i] != '\n') i++;
		tmp = buf[i];
		for (; i < MAX_INV_NAME; i++) buf[i] = 0;
		strncpy(inventory[j].name, buf, MAX_INV_NAME);
		if (tmp == EOF) break;
	}
	//fclose(f);
	// Read metadata
	int len_m = 6;
	//f = fopen(filename4, "r");
	Metadata *metas = alloca(sizeof(Metadata) * len_m);
	{
		char *meta_names[6] = {"Name", "Klasse", "Alter", "Wohnort", "Herkunft", "Trefferpunkte"};
		for (int i = 0; i < len_m - 1; i++) {
			int j = 0;
			metas[i].name = meta_names[i];
			// Read meta data value
			while (j < MAX_META_VAL && (metas[i].val[j] = fgetc(f)) != EOF && metas[i].val[j] != '\n') j++;
			for (; j < MAX_META_VAL; j++) metas[i].val[j] = 0;
		}
		char *buf = itoa(hitpoints, 10);
		int buflen = strlen(buf);
		metas[len_m - 1].name = meta_names[len_m - 1];
		strncpy(metas[len_m - 1].val, buf, buflen);
		for(int i = buflen; i < MAX_META_VAL; i++) metas[len_m - 1].val[i] = 0;
	}
	fclose(f);
	// Offset is an aesthetic property when displaying lists.
	int offset = 2;
	// Mode 0 = print metadata, Mode 1 = print attributes, Mode 2 = print stats, Mode 3 = print inventory
	int mode = 0;
	// Lengths / number of maximum lines for each mode
	int* len[4] = {&len_m, &len_a, &len_s, &len_i};
	// Print list
	print_metadata(metas, len_m, selection, offset);
	while((c = fgetc(stdin)) != 'q'){
		switch (c) {
			case 'j':
				if (selection < *len[mode] - 1) ++selection;
				break;
			case 'k':
				if (selection > 0) --selection;
				break;
			case 'h':
				if (mode > 0) --mode;
				if (selection > *len[mode]) selection = *len[mode] - 1;
				break;
			case 'l':
				if (mode < 3) ++mode;
				if (selection > *len[mode]) selection = *len[mode] - 1;
				break;
			case 'g':
				selection = 0;
				break;
			case 'G':
				selection = *len[mode] - 1;
				break;
			case '\n':
				if (mode == 0 && selection != *len[mode] - 1) bread(metas[selection].val, MAX_META_VAL, "New value: ");
				else if (mode == 2) bread(stats[selection].name, MAX_STAT_NAME, "Change name of stat: ");
				else if (mode == 3) bread(inventory[selection].name, MAX_INV_NAME, "Rename item: ");
				break;
			case '+':
				if (mode == 0 && selection == *len[mode] - 1 && hitpoints < 20) {
					char *buf = itoa(++hitpoints, 10);
					int buflen = strlen(buf);
					strncpy(metas[len_m - 1].val, buf, buflen);
					for(int i = buflen; i < MAX_META_VAL; i++) metas[len_m - 1].val[i] = 0;
				} else if (mode == 1 && attrs[selection].val < 50) ++attrs[selection].val;
				else if (mode == 2 && stats[selection].val < 50 && stats[selection].val >= 0) ++stats[selection].val;
				else if (mode == 3 && inventory[selection].count >= 0) ++inventory[selection].count;
				break;
			case '-':
				if (mode == 0 && selection == *len[mode] - 1 && hitpoints > 0) {
					char *buf = itoa(--hitpoints, 10);
					int buflen = strlen(buf);
					strncpy(metas[len_m - 1].val, buf, buflen);
					for(int i = buflen; i < MAX_META_VAL; i++) metas[len_m - 1].val[i] = 0;
				} else if (mode == 1 && attrs[selection].val > 0) --attrs[selection].val;
				else if (mode == 2 && stats[selection].val > 0) --stats[selection].val;
				else if (mode == 3 && inventory[selection].count > 0) --inventory[selection].count;
				break;
			case 'J':
				if (mode == 2 && selection < *len[mode] - 1) {
					Stat tomove = stats[selection];
					stats[selection] = stats[selection + 1];
					stats[selection + 1] = tomove;
					++selection;
				} else if (mode == 3 && selection < *len[mode] - 1) {
					Item tomove = inventory[selection];
					inventory[selection] = inventory[selection + 1];
					inventory[selection + 1] = tomove;
					++selection;
				}
				break;
			case 'K':
				if (mode == 2 && selection > 0) {
					Stat tomove = stats[selection];
					stats[selection] = stats[selection - 1];
					stats[selection - 1] = tomove;
					--selection;
				} else if (mode == 3 && selection > 0) {
					Item tomove = inventory[selection];
					inventory[selection] = inventory[selection - 1];
					inventory[selection - 1] = tomove;
					--selection;
				}
				break;
			case '*':
				if (mode == 2) {
					char tmp[3];
					++len_s;
					++new_len_s;
					stats = realloc(stats, sizeof(Stat) * len_s);
					stats[len_s - 1] = default_stat();
					bread(stats[len_s - 1].name, MAX_STAT_NAME, "New stat name: ");
					bread(tmp, 3, "Base attribute (/012345): ");
					if (*tmp >= '0' && *tmp <= '5') {
						stats[len_s - 1].type[0] = &(attrs[*tmp - '0']);
						bread(tmp, 3, "Second base attribute (/012345): ");
						if(*tmp >= '0' && *tmp <= '5')stats[len_s - 1].type[1] = &(attrs[*tmp - '0']);
					}
				} else if (mode == 3) {
					char tmp[9];
					++len_i;
					++new_len_i;
					inventory = realloc(inventory, sizeof(Item) * len_i);
					inventory[len_i - 1] = default_item();
					bread(inventory[len_i - 1].name, MAX_INV_NAME, "Name your item: ");
					bread(tmp, 9, "How many? ");
					inventory[len_i - 1].count = atoi(tmp);
				}
				break;
			case '_':
				if (mode == 2) {
					--new_len_s;
					stats[selection].val = -1;
					stats[selection].type[0] = NULL;
					stats[selection].type[1] = NULL;
				} else if (mode == 3) {
					--new_len_i;
					inventory[selection].count = -1;
				}
				break;
			default:
				continue;
		}
		bwash();
		// Print list
		switch (mode) {
			case 0:
				print_metadata(metas, len_m, selection, offset);
				break;
			case 1:
				print_attributes(attrs, len_a, selection, offset);
				break;
			case 2:
				print_stats(stats, len_s, selection, offset);
				break;
			case 3:
				print_inventory(inventory, len_i, selection, offset);
				break;
			default:
				mode = 1;
				print_attributes(attrs, len_a, selection, offset);
				break;
		}
	}
	// Save file
	f = fopen(filename, "wb");
	fputc(hitpoints, f);
	for(int i = 0; i < len_a; i++) {
		fputc(attrs[i].val, f);
	}
	fputc(new_len_i, f);
	fputc(new_len_s, f);
	for(int i = 0; i < len_s; i++) {
		if (stats[i].val >= 0) fputc(stats[i].val, f);
	}
	//fclose(f);
	//f = fopen(filename2, "w");
	for(int i = 0; i < len_s; i++) {
		if (stats[i].val < 0) continue;
		fputs(stats[i].name, f);
		fputc('\t', f);
		fputc(attr_index(stats[i].type[0]), f);
		if (stats[i].type[1] != NULL) fputc(attr_index(stats[i].type[1]), f);
		fputc('\n', f);
	}
	//fclose(f);
	//f = fopen(filename3, "w");
	for(int i = 0; i < len_i; i++) {
		if (inventory[i].count < 0) continue;
		fputs(itoa(inventory[i].count, 10), f);
		fputc('\t', f);
		fputs(inventory[i].name, f);
		fputc('\n', f);
	}
	//fclose(f);
	//f = fopen(filename4, "w");
	for(int i = 0; i < len_m - 1; i++) {
		fputs(metas[i].val, f);
		fputc('\n', f);
	}
	fclose(f);
	bquit();
	free(stats);
	free(inventory);
	return 0;
}
