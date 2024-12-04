# Clean up old object and executable files
all: clean compile link run

clean:
	rm -f Skeleton/bin/*.o bin/main

# Ensure bin directory exists
Skeleton/bin:
	mkdir -p Skeleton/bin

# Compile source files into object files
compile: Skeleton/bin
	@echo "Compiling source code"
	g++ -g -c -Wall -Weffc++ -std=c++11 -o bin/main.o src/main.cpp -Iinclude
	g++ -g -c -Wall -Weffc++ -std=c++11 -o bin/Auxiliary.o src/Auxiliary.cpp -Iinclude
	g++ -g -c -Wall -Weffc++ -std=c++11 -o bin/Facility.o src/Facility.cpp -Iinclude
	g++ -g -c -Wall -Weffc++ -std=c++11 -o bin/SelectionPolicy.o src/SelectionPolicy.cpp -Iinclude
	g++ -g -c -Wall -Weffc++ -std=c++11 -o bin/settlement.o src/settlement.cpp -Iinclude
	g++ -g -c -Wall -Weffc++ -std=c++11 -o bin/plan.o src/Plan.cpp -Iinclude
	g++ -g -c -Wall -Weffc++ -std=c++11 -o bin/Simulation.o src/simulation.cpp -Iinclude
	g++ -g -c -Wall -Weffc++ -std=c++11 -o bin/Action.o src/Action.cpp -Iinclude

# Link the object files into the final executable
link:
	@echo "Linking Object files"
	g++ -o bin/main bin/*.o

run:
	@echo "Running the program"
	./bin/main ./config_file.txt

