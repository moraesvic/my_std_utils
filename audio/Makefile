make:
	gcc gen_sin_wave.c -lm -o gen_sin_wave
	./gen_sin_wave
	ffmpeg -f u16le -ar 44100 -ac 1 -i out.raw -y out.flac
	vlc out.flac
	rm out.raw