#include <string.h>
#include <unistd.h>
#include <alloca.h>
#include "BarnabasBox/barnabas.h"
#include "BarnabasBox/Itoa/itoa.h"
#ifndef MAIN_H
#define MAIN_H

#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)

#define MAX_STAT_NAME 27
#define MAX_INV_NAME 100
#define MAX_META_VAL 20

typedef struct {
	char *name;
	int val;
} Attribute;

typedef struct {
	char name[MAX_STAT_NAME];
	int val;
	Attribute *type[2];
} Stat;

typedef struct {
	char name[MAX_INV_NAME];
	int count;
} Item;

typedef struct {
	char *name;
	char val[MAX_META_VAL];
} Metadata;

void print_metadata(Metadata *list, int len, int selection, int offset);
void print_attributes(Attribute *list, int len, int selection, int offset);
void print_stats(Stat *list, int len, int selection, int offset);
void print_inventory(Item *list, int len, int selection, int offset);
int main(int, char **);
const char* map_attr(Attribute *);
const char attr_index(Attribute *);
Stat default_stat();
Item default_item();
void read_stats(Stat *, int, FILE *, Attribute *);

#endif
