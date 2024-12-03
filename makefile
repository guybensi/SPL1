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
	g++ -g -c -Wall -Weffc++ -std=c++11 -o Skeleton/bin/main.o Skeleton/src/main.cpp -ISkeleton/include
	g++ -g -c -Wall -Weffc++ -std=c++11 -o Skeleton/bin/Auxiliary.o Skeleton/src/Auxiliary.cpp -ISkeleton/include
	g++ -g -c -Wall -Weffc++ -std=c++11 -o Skeleton/bin/Facility.o Skeleton/src/Facility.cpp -ISkeleton/include
	g++ -g -c -Wall -Weffc++ -std=c++11 -o Skeleton/bin/SelectionPolicy.o Skeleton/src/SelectionPolicy.cpp -ISkeleton/include
	g++ -g -c -Wall -Weffc++ -std=c++11 -o Skeleton/bin/settlement.o Skeleton/src/settlement.cpp -ISkeleton/include
	g++ -g -c -Wall -Weffc++ -std=c++11 -o Skeleton/bin/plan.o Skeleton/src/plan.cpp -ISkeleton/include
	g++ -g -c -Wall -Weffc++ -std=c++11 -o Skeleton/bin/Simulation.o Skeleton/src/simulation.cpp -ISkeleton/include
	g++ -g -c -Wall -Weffc++ -std=c++11 -o Skeleton/bin/Action.o Skeleton/src/Action.cpp -ISkeleton/include

# Link the object files into the final executable
link:
	@echo "Linking Object files"
	g++ -o bin/main Skeleton/bin/*.o

run:
	@echo "Running the program"
	./bin/main ./Skeleton/config_file.txt

