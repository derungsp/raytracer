program: src/main.o src/Vector2D.o
	g++ src/main.o src/Vector2D.o -o program

src/main.o: src/main.cpp src/Vector2D.h
	g++ -c src/main.cpp -o src/main.o

src/Vector2D.o: src/Vector2D.cpp src/Vector2D.h
	g++ -c src/Vector2D.cpp -o src/Vector2D.o

clean:
	rm -f src/*.o program