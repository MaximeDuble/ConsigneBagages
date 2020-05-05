main2: ./bin/partie2Test.o ./bin/Ticket.o ./bin/vConsigne.o ./bin/vMalette.o ./bin/vCylindre.o ./bin/vDemiSphere.o ./bin/vBagage.o
	g++ ./bin/partie2Test.o ./bin/Ticket.o ./bin/vConsigne.o ./bin/vMalette.o ./bin/vCylindre.o ./bin/vDemiSphere.o ./bin/vBagage.o -o main2

main1 : ./bin/partie1Test.o ./bin/Ticket.o ./bin/Consigne.o
	g++ ./bin/partie1Test.o ./bin/Ticket.o ./bin/Consigne.o -o main1

./bin/partie1Test.o : partie1Test.cpp
	g++ -c partie1Test.cpp -o ./bin/partie1Test.o

./bin/partie2Test.o : partie2Test.cpp
	g++ -c partie2Test.cpp -o ./bin/partie2Test.o

./bin/Ticket.o : ./sources/Ticket.cpp
	g++ -c ./sources/Ticket.cpp -o ./bin/Ticket.o

./bin/Consigne.o : ./sources/Consigne.cpp
	g++ -c ./sources/Consigne.cpp -o ./bin/Consigne.o

./bin/vConsigne.o : ./sources/vConsigne.cpp
	g++ -c ./sources/vConsigne.cpp -o ./bin/vConsigne.o

./bin/vBagage.o : ./sources/vBagage.cpp
	g++ -c ./sources/vBagage.cpp -o ./bin/vBagage.o

./bin/vMalette.o : ./sources/vMalette.cpp
	g++ -c ./sources/vMalette.cpp -o ./bin/vMalette.o

./bin/vCylindre.o : ./sources/vCylindre.cpp
	g++ -c ./sources/vCylindre.cpp -o ./bin/vCylindre.o

./bin/vDemiSphere.o : ./sources/vDemiSphere.cpp
	g++ -c ./sources/vDemiSphere.cpp -o ./bin/vDemiSphere.o

clear:
	rm ./bin/*.o