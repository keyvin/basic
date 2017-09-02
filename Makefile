varmake: parsetree.c line.c parse.c varlist.c varcalc.c executor.c stdcall.c 
	gcc -o varmake stdcall.c parsetree.c line.c parse.c varlist.c varcalc.c executor.c -I. -lm -m32 --debug 
