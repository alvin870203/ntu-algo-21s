# CC and CFLAGS are varilables
CC = g++
CFLAGS = -c
AR = ar
ARFLAGS = rcv
# -c option ask g++ to compile the source files, but do not link.
# -g option is for debugging version
# -O2 option is for optimized version
DBGFLAGS = -g
OPTFLAGS = -O2

all	: bin/mps
	@echo -n ""

# optimized version
bin/mps		   : mps_tool_opt.o main_opt.o src
			$(CC) $(OPTFLAGS) mps_tool_opt.o main_opt.o -ltm_usage -Lsrc -o bin/mps
main_opt.o	   : src/main.cpp src/tm_usage.h src/mps_tool.h
			$(CC) $(CFLAGS) $< -Isrc -o $@
mps_tool_opt.o : src/mps_tool.cpp src/mps_tool.h
			$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@

# DEBUG version
dpg : bin/mps_dbg
	@echo -n ""

bin/mps_dbg	   : mps_tool_dbg.o main_dbg.o src
			$(CC) $(DBGFLAGS) mps_tool_dbg.o main_dbg.o -ltm_usage -Lsrc -o bin/mps_dbg
main_dbg.o	   : src/main.cpp src/tm_usage.h src/mps_tool.h
			$(CC) $(CFLAGS) $< -Isrc -o $@
mps_tool_dbg.o : src/mps_tool.cpp src/mps_tool.h
			$(CC) $(CFLAGS) $(DBGFLAGS) $< -o $@

src: src/srctm_usage.a

src/srctm_usage.a: tm_usage.o
	$(AR) $(ARFLAGS) $@ $<
tm_usage.o: src/tm_usage.cpp src/tm_usage.h
	$(CC) $(CFLAGS) $<

# clean all the .o and executable files
clean:
		rm -rf *.o src/*.a src/*.o bin/*
