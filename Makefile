all: main

BarnabasBox/libbarnabas.a:
	make -C BarnabasBox -f Makefile

attr_index.o: attr_index.c main.h
	cproc -c -o attr_index.o attr_index.c

default_item.o: default_item.c main.h
	cproc -c -o default_item.o default_item.c

default_stat.o: default_stat.c main.h
	cproc -c -o default_stat.o default_stat.c

map_attr.o: map_attr.c main.h
	cproc -c -o map_attr.o map_attr.c

print_attributes.o: print_attributes.c main.h
	cproc -c -o print_attributes.o print_attributes.c

print_inventory.o: print_inventory.c main.h
	cproc -c -o print_inventory.o print_inventory.c

print_metadata.o: print_metadata.c main.h
	cproc -c -o print_metadata.o print_metadata.c

print_stats.o: print_stats.c main.h
	cproc -c -o print_stats.o print_stats.c

read_stats.o: read_stats.c main.h
	cproc -c -o read_stats.o read_stats.c

main.o: main.c main.h
	diet -Os gcc -c -o main.o main.c

main: main.o attr_index.o default_item.o default_stat.o map_attr.o print_attributes.o print_inventory.o print_metadata.o print_stats.o read_stats.o
	ld -static -s -z norelro -z noseparate-code -o main *.o BarnabasBox/libbarnabas.a /usr/lib/libc.a
