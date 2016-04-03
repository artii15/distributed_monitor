all:
	mpic++ -Wall src/*.cpp src/communicators/*.cpp src/exceptions/*.cpp src/synchronizer/*.cpp src/synchronizer/messages/*.cpp main.cpp -o main -lpthread
