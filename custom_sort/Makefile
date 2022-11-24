CXX = g++
CFLAGS = -Wall -Wextra -Wno-unused-result -Wno-unused-parameter -Wno-unused-but-set-variable -O3 
CXXFLAGS = $(CFLAGS) -std=c++11
TARGET = main

all:	$(TARGET)

main:	main.o edge_sort.o 
	$(CXX) $(CFLAGS) -o $@ $^

%.o:	%.cc
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *o
	rm -f $(TARGET)
