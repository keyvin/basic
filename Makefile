varmake: parsetree.c line.c parse.c varlist.c varcalc.c executor.c stdcall.o 
	gcc -o varmake parsetree.c line.c parse.c varlist.c varcalc.c executor.c stdcall.c -I. -lm --debug 
