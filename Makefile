a.out: main.cc class.h
	g++ -std=c++11 main.cc 
clean: 
	rm a.out
