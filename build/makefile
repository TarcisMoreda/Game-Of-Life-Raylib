GoL: main.o game.o
	gcc main.o game.o -o GoL.bin -lraylib -lglfw -lGL -lopenal -lm -pthread -ldl -lX11 -lXrandr -lXinerama -lXi -lXxf86vm -lXcursor

main.o: ../main.c ../include/game.h
	gcc -c ../main.c

game.o: ../src/game.c ../include/game.h
	gcc -c ../src/game.c

clean:
	rm *.o GoL.bin