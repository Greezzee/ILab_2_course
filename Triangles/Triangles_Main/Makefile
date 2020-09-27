all: triangles

triangles: Main.o Space.o Collider.o PolygonCollider.o Coordinate.o
	g++ Main.o Space.o Collider.o PolygonCollider.o Coordinate.o -o triangles_main
	rm -rf *.o triangles

Main.o:
	g++ -c ../Triangles_Source/Main.cpp -lm

Space.o:
	g++ -c ../Triangles_Source/Space.cpp -lm

Collider.o:
	g++ -c ../Triangles_Source/Collider.cpp -lm

PolygonCollider.o:
	g++ -c ../Triangles_Source/PolygonCollider.cpp -lm

Coordinate.o:
	g++ -c ../Triangles_Source/Coordinate.cpp -lm

clean:
	rm -rf *.o triangles
