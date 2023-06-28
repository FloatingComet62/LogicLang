src := $(wildcard src/*.c)
out := logiclang
cflags := -O3 -std=c99

linux: build_linux run_linux
debug: build_debug_linux run_debug_linux
windows: build_windows run_windows
build_debug_linux:
	gcc $(src) -o $(out) $(cflags) -g
run_debug_linux:
	gdb ./$(out)
build_linux:
	gcc $(src) -o $(out) $(cflags)
run_linux:
	./$(out) main.ll
build_windows:
	gcc $(src) -o $(out).exe $(cflags)
run_windows:
	./$(out).exe main.ll 
clean_linux:
	rm $(out)
clean_windows:
	rm $(out).exe
