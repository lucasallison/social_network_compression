CXX = g++
CFLAGS = -Wall -Wextra -Wno-unused-result -Wno-unused-parameter -Wno-unused-but-set-variable -O3 
CXXFLAGS = $(CFLAGS) -std=c++11
TARGET = main
OBJDIR = obj

SIM_SORT_PATH = similarity_sort

all:	$(TARGET)

main:	$(OBJDIR)/main.o $(OBJDIR)/edge_sort.o $(OBJDIR)/sim_sort.o
	$(CXX) $(CFLAGS) -o $@ $^

$(OBJDIR)/sim_sort.o:	$(SIM_SORT_PATH)/sim_sort.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o:	%.cpp 
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJDIR)/*o
	rm -f $(TARGET)
