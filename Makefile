cli_exec:  com2 run
    
run:
	./Progra
    
com2:
	gcc  -Wall Progra.c -o Progra `pkg-config --cflags --libs gtk+-3.0` -export-dynamic  -lm
