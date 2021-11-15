all: clean compile link

link:
	g++ -o bin/studio bin/main.o bin/Workout.o bin/Trainer.o bin/Studio.o bin/Customer.o bin/Action.o

compile:
	g++ -g -Wall -Weffc++ -c -o bin/main.o src/main.cpp
	g++ -g -Wall -Weffc++ -c -o bin/Studio.o src/Studio.cpp
	g++ -g -Wall -Weffc++ -c -o bin/Workout.o src/Workout.cpp
	g++ -g -Wall -Weffc++ -c -o bin/Trainer.o src/Trainer.cpp
	g++ -g -Wall -Weffc++ -c -o bin/Customer.o src/Customer.cpp
	g++ -g -Wall -Weffc++ -c -o bin/Action.o src/Action.cpp
	-g -Wall -std=c++11

clean:
	rm -f bin/*