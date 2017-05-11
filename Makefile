a.out: main.cc class.h
	g++ -std=c++11 main.cc class.h
clean: 
	rm a.out
