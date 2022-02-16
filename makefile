ddi: main.c
	gcc -g -Wall main.c -o ddi

test: ddi
	./ddi psw FFC50006 A0000030

debug: ddi
	gdb ddi --args ddi psw FFC50001 8000001A
