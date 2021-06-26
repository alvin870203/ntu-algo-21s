# CC and CFLAGS are varilables
CC = g++
CFLAGS = -c
# -c option ask g++ to compile the source files, but do not link.
# -O3 option is for optimized version
OPTFLAGS = -O3

all	: bin/cb
	@echo -n ""

# optimized version
bin/cb		   : main_opt.o src
			$(CC) $(OPTFLAGS) main_opt.o
main_opt.o	   : src/main.cpp
			$(CC) $(CFLAGS) $< -Isrc -o $@

# clean all the .o and executable files
clean:
		rm -rf *.o src/*.a src/*.o bin/* a.out
