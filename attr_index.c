#include "main.h"

const char attr_index(Attribute *a) {
	if (a == NULL)
		return '/';
	else if (strcmp(a->name, "Stärke") == 0)
		return '0';
	else if (strcmp(a->name, "Geschick") == 0)
		return '1';
	else if (strcmp(a->name, "Intelligenz") == 0)
		return '2';
	else if (strcmp(a->name, "Bildung") == 0)
		return '3';
	else if (strcmp(a->name, "Charisma") == 0)
		return '4';
	else if (strcmp(a->name, "Glück") == 0)
		return '5';
	else
		return '/';
}
