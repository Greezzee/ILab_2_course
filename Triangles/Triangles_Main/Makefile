all: triangles

triangles: Main.o Space.o Collider.o PolygonCollider.o Coordinate.o
	g++ Main.o Space.o Collider.o PolygonCollider.o Coordinate.o -o triangles_main -O2
	rm -rf *.o triangles

Main.o:
	g++ -c ../Triangles_Source/Main.cpp -lm -O2

Space.o:
	g++ -c ../Triangles_Source/Space.cpp -lm -O2

Collider.o:
	g++ -c ../Triangles_Source/Collider.cpp -lm -O2

PolygonCollider.o:
	g++ -c ../Triangles_Source/PolygonCollider.cpp -lm -O2

Coordinate.o:
	g++ -c ../Triangles_Source/Coordinate.cpp -lm -O2

clean:
	rm -rf *.o triangles
