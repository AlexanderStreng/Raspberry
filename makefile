CC=g++
CFLAGS=-c -Wall -I./mongoose/include -I./server/include
VPATH=./server/src:./mongoose/src
LDFLAGS=
DIRS=server mongoose
SOURCES=server.cpp mongoose.c
OBJECTS=server.o mongoose.o
EXECUTABLE=piServer

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@echo "============="
	@echo "Linking the target $@"
	@echo "============="
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
	@echo -- Link finished --

server.o : server.h mongoose.h
	$(CC) $(CFLAGS) server.cpp -o

## Generic c++ compilation rule
%.o : %.cpp %.h
	@echo "============="
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo -- Compile finished --

## Generic c compilation rule
%.o : %.c %.h
	@echo "============="
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo -- Compile finished --

clean :
	@echo cleaning up in .
	-$(RM) -f $(EXE) $(OBJS) $(OBJLIBS)
	-for d in $(DIRS); do (cd $$d; $(MAKE) clean ); done

