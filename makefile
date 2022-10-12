carnival: driver.o patron.o ride.o WorldTour.o Teacups.o MagicCarpet.o
	g++ -o carnival driver.o patron.o ride.o WorldTour.o Teacups.o MagicCarpet.o

driver.o: driver.cpp
	g++ -c driver.cpp

patron.o: patron.cpp patron.h
	g++ -c patron.cpp

ride.o: ride.cpp ride.h
	g++ -c ride.cpp

WorldTour.o: WorldTour.h WorldTour.cpp
	g++ -c WorldTour.cpp

Teacups.o: Teacups.h Teacups.cpp
	g++ -c Teacups.cpp

MagicCarpet.o: MagicCarpet.h MagicCarpet.cpp
	g++ -c MagicCarpet.cpp

clean:
	rm *.o carnival