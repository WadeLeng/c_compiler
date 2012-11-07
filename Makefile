include Make.properties

TARGET = compiler
SRC = ./src/*.o

SRC_PATH = src

all: 
	(cd $(SRC_PATH) && $(MAKE) -f $(MAKEFILE)) || exit 1;
	$(CC) -o $(TARGET) $(SRC) $(CPPFLAGS) 

clean:
	(cd $(SRC_PATH) && $(MAKE) clean -f $(MAKEFILE)) || exit 1;
	rm $(TARGET) -f
