final: main.o AdjLis.o Timer.hpp
	g++ main.o AdjLis.o -o main

main.o: main.cpp
	g++ -c main.cpp -o main.o 

AdjLis.o: AdjacencyList.cpp AdjacencyList.hpp
	g++ -c AdjacencyList.cpp -o AdjLis.o

clean:
	rm main.o AdjLis.o

