#include "main.h"

const char *map_attr(Attribute *a) {
	static const char *res[7] = {
		"X",
		"ST",
		"GE",
		"IN",
		"BI",
		"CH",
		"GL"
	};
	if (a == NULL)
		return res[0];
	else if (strcmp(a->name, "Stärke") == 0)
		return res[1];
	else if (strcmp(a->name, "Geschick") == 0)
		return res[2];
	else if (strcmp(a->name, "Intelligenz") == 0)
		return res[3];
	else if (strcmp(a->name, "Bildung") == 0)
		return res[4];
	else if (strcmp(a->name, "Charisma") == 0)
		return res[5];
	else if (strcmp(a->name, "Glück") == 0)
		return res[6];
	else
		return res[0];
}
