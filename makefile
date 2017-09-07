CXX=g++
CXXFLAGS=-g

test.exe: Tokenise.o Machine.o Parse.o main.o
	$(CXX) $(CXXFLAGS) main.o Parse.o Machine.o Tokenise.o -o test.exe

Tokenise.o: Tokenise.h Tokenise.cpp
	$(CXX) $(CXXFLAGS) -c Tokenise.cpp

Machine.o: Machine.h Machine.cpp
	$(CXX) $(CXXFLAGS) -c Machine.cpp

Parse.o: Parse.h Parse.cpp
	$(CXX) $(CXXFLAGS) -c Parse.cpp

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp




