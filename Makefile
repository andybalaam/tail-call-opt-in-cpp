
all:
	ulimit -S -s 4096; scons && ulimit -S -s 16 && ./tail_call
