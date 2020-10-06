all: triangles

triangles: Test.o Space.o Collider.o PolygonCollider.o Coordinate.o
	g++ Test.o Space.o Collider.o PolygonCollider.o Coordinate.o -o triangles_unit_test -lgtest -lgtest_main -lpthread
	rm -rf *.o triangles

Test.o:
	g++ -c Test.cpp -lm -lgtest -lgtest_main -lpthread

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
