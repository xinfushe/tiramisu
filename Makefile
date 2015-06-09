#!bin/bash

CXX = g++
CFLAGS = -std=c++0x -O2 -c -fopenmp
LFLAGS = -std=c++0x -O2 -fopenmp
OBJS = CNNLayer.o CNNFeature.o Image.o Activation.o IO.o
OBJS_PATH = build/CNNLayer.o build/CNNFeature.o build/Image.o build/Activation.o build/IO.o


ALL: main

IO.o: src/IO.cpp include/IO.hpp
	$(CXX) $(CFLAGS) $< -o build/$@

CNNLayer.o: src/CNNLayer.cpp include/CNNLayer.hpp
	$(CXX) $(CFLAGS) $< -o build/$@

CNNFeature.o: src/CNNFeature.cpp include/CNNFeature.hpp
	$(CXX) $(CFLAGS) $< -o build/$@

Image.o: src/Image.cpp include/Image.hpp
	$(CXX) $(CFLAGS) $< -o build/$@

Activation.o: src/Activation.cpp include/Activation.hpp
	$(CXX) $(CFLAGS) $< -o build/$@

main: src/main.cpp $(OBJS)
	$(CXX) $(LFLAGS) $(OBJS_PATH) $< -o build/$@

clean : 
	rm -f build/*.o build/main
