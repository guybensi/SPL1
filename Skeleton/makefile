# Rule for building the executable
all: SettlementTest

# Rule for linking the object files into the final executable
SettlementTest: main.o Settlement.o
	g++ -o bin/Settlement.o bin/main.o  

# Rule for compiling main.cpp into an object file
main.o : main.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Include -o bin/main.o src/main.cpp

# Rule for compiling Settlement.cpp into an object file
Settlement.o: Settlement.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Include -o bin/Settlement.o src/Settlement.cpp

# Rule for cleaning up object files and the executable
clean:
	rm -f main.o Settlement.o SettlementTest
