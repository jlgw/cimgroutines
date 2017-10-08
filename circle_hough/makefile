CC = g++
CFLAGS = -lm -L/usr/X11R6/lib -lpthread -lX11
TARGET = demo
all: $(TARGET).cpp
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp
clean:
	$(RM) $(TARGET)
