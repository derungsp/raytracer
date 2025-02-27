program: src/main.o src/Vector2D.o src/Vector3D.o src/Ray.o src/Color.o
	g++ src/main.o src/Vector2D.o src/Vector3D.o src/Ray.o src/Color.o -o program

src/main.o: src/main.cpp src/Vector2D.h src/Vector3D.h src/Ray.h src/Color.h
	g++ -c src/main.cpp -o src/main.o

src/Vector2D.o: src/Vector2D.cpp src/Vector2D.h
	g++ -c src/Vector2D.cpp -o src/Vector2D.o

src/Vector3D.o: src/Vector3D.cpp src/Vector3D.h
	g++ -c src/Vector3D.cpp -o src/Vector3D.o

src/Ray.o: src/Ray.cpp src/Ray.h src/Vector3D.h
	g++ -c src/Ray.cpp -o src/Ray.o

src/Color.o: src/Color.cpp src/Color.h
	g++ -c src/Color.cpp -o src/Color.o

clean:
	rm -f src/*.o program