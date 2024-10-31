

build: 
	gcc -O3 -Wall -o crear_estado_tests crear_estado_tests.c --std=c11

debug: 
	gcc -Wall -g3 -o crear_estado_tests.o crear_estado_tests.c --std=c11

