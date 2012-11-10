include ../Make.properties

all: compiler.o asm.o lexical.o parser.o symbol.o token.o table.o production.o expression.o 

SRC = compiler.cpp asm.cpp lexical.cpp parser.cpp symbol.cpp token.cpp table.cpp production.cpp expression.cpp

include $(SRC:.cpp=.d)

%.d: %.cpp
	set -e; rm -f $@; \
	$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

clean:
	rm -f *.o
	rm -f *.d
