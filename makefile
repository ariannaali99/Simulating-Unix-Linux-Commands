all: myls mysearch mystat mytail

myls: myls-Arianna.c
	gcc -o myls myls-Arianna.c

mysearch: mysearch-Arianna.c
	gcc -o mysearch mysearch-Arianna.c

mystat: mystat-Arianna.c
	gcc -o mystat mystat-Arianna.c

mytail: mytail-Arianna.c
	gcc -o mytail mytail-Arianna.c