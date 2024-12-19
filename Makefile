CC = g++
CFLAGS = -g -Wall -std=c++11
TARGET = signal-echo

all: $(TARGET)

$(TARGET): signal-echo.cpp
	$(CC) $(CFLAGS) -o $(TARGET) signal-echo.cpp

clean:
	rm -f $(TARGET)

