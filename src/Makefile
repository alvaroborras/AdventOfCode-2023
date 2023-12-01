CC = g++
CFLAGS = -Wall -O3 -march=native -std=c++20

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

all: $(TARGET)

$(TARGET): $(TARGET).o
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o $(TARGET)