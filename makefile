CC = g++
CFLAGS = -Wall -std=c++1z
OBJ = start_page.o
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

file_explorer: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^
