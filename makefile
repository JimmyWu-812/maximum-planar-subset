# CC and CFLAGS are varilables
CC = g++
CFLAGS = -c
AR = ar
ARFLAGS = rcv
# -c option ask g++ to compile the source files, but do not link.
# -g option is for debugging version
# -O2 option is for optimized version
DBGFLAGS = -g -D_DEBUG_ON_
OPTFLAGS = -O2

all	: bin/mps
	@echo -n ""

# optimized version
bin/mps			: main_opt.o
			$(CC) $(OPTFLAGS) main_opt.o -o bin/mps
main_opt.o 	   	: src/main.cpp
			$(CC) $(CFLAGS) $< -o $@
# bin/mps2			: test_opt.o
# 			$(CC) $(OPTFLAGS) test_opt.o -o bin/mps2
# test_opt.o 	   	: src/test.cpp
# 			$(CC) $(CFLAGS) $< -o $@

# DEBUG Version
# dbg : bin/NTU_sort_dbg
# 	@echo -n ""

# bin/NTU_sort_dbg	: sort_tool_dbg.o main_dbg.o lib
#			$(CC) $(DBGFLAGS) sort_tool_dbg.o main_dbg.o -ltm_usage -Llib -o bin/NTU_sort_dbg
# main_dbg.o 	   	: src/main.cpp lib/tm_usage.h
#			$(CC) $(CFLAGS) $< -Ilib -o $@
# sort_tool_dbg.o	: src/sort_tool.cpp src/sort_tool.h
#			$(CC) $(CFLAGS) $(DBGFLAGS) $< -o $@

# lib: lib/libtm_usage.a

# lib/libtm_usage.a: tm_usage.o
#	$(AR) $(ARFLAGS) $@ $<
# tm_usage.o: lib/tm_usage.cpp lib/tm_usage.h
#	$(CC) $(CFLAGS) $<

# clean all the .o and executable files
clean:
		rm -rf *.o lib/*.a lib/*.o bin/*

