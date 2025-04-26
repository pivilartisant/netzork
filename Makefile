default:
	gcc -std=c99 -Wall -Werror -fsanitize=address  -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL -Llib -Iinclude -lraylib  main.c -o main 

run:
	make && ./main
