varmake: parsetree.c line.c parse.c varlist.c varcalc.c 
	gcc -o varmake parsetree.c line.c parse.c varlist.c varcalc.c -I. -lm --debug