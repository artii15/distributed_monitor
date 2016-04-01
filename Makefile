all:
	mpic++ -Wall src/*.cpp src/messages/*.cpp src/exceptions/*.cpp main.cpp -o main -lpthread
