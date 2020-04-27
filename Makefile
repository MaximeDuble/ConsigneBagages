main2: partie2Test.o Ticket.o vConsigne.o vBagage.o
	g++ partie2Test.o Ticket.o vConsigne.o vBagage.o -o main2

#main1 : partie1Test.o Ticket.o Consigne.o
#	g++ partie1Test.o Ticket.o Consigne.o -o main1

partie1Test.o : partie1Test.cpp
	g++ -c partie1Test.cpp

partie2Test.o : partie2Test.cpp
	g++ -c partie2Test.cpp

Ticket.o : Ticket.cpp
	g++ -c Ticket.cpp

Consigne.o : Consigne.cpp
	g++ -c Consigne.cpp

vConsigne.o : vConsigne.cpp
	g++ -c vConsigne.cpp

vBagage.o : vBagage.cpp
	g++ -c vBagage.cpp

clear:
	rm *.o