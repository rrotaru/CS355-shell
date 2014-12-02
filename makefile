novash: src/*.c
	cc src/*.c -o build/novash

debug: src/*.c
	cc src/*.c -g -o build/novash
