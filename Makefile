varmake: parsetree.c line.c parse.c varlist.c varcalc.c executor.c 
	gcc -o varmake parsetree.c line.c parse.c varlist.c varcalc.c executor.c -I. -lm --debug 