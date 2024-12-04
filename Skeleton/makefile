# Clean up old object and executable files
all: clean compile link run

clean:
	rm -f Skeleton/bin/*.o main

# Ensure bin directory exists
Skeleton/bin:
	mkdir -p Skeleton/bin

# Compile source files into object files
compile: Skeleton/bin
	@echo "Compiling source code"
	g++ -g -c -Wall -Weffc++ -std=c++11 -o Skeleton/bin/main.o src/main.cpp -Iinclude
	g++ -g -c -Wall -Weffc++ -std=c++11 -o Skeleton/bin/Auxiliary.o src/Auxiliary.cpp -Iinclude
	g++ -g -c -Wall -Weffc++ -std=c++11 -o Skeleton/bin/Facility.o src/Facility.cpp -Iinclude
	g++ -g -c -Wall -Weffc++ -std=c++11 -o Skeleton/bin/SelectionPolicy.o src/SelectionPolicy.cpp -Iinclude
	g++ -g -c -Wall -Weffc++ -std=c++11 -o Skeleton/bin/settlement.o src/settlement.cpp -Iinclude
	g++ -g -c -Wall -Weffc++ -std=c++11 -o Skeleton/bin/plan.o src/plan.cpp -Iinclude
	g++ -g -c -Wall -Weffc++ -std=c++11 -o Skeleton/bin/Simulation.o src/simulation.cpp -Iinclude
	g++ -g -c -Wall -Weffc++ -std=c++11 -o Skeleton/bin/Action.o src/Action.cpp -Iinclude

# Link the object files into the final executable
link:
	@echo "Linking Object files"
	g++ -o bin/main Skeleton/bin/*.o 

run:
	@echo "Running the program"
	./bin/main ./config_file.txt
