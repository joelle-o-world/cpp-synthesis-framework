CC=g++

FLAGS=-I ../include -I ../vendor/include -std=c++14 -stdlib=libc++ -fPIC -isystem /usr/local/include -isystem /Library/Developer/CommandLineTools/usr/bin/../include/c++/v1 -isystem /Library/Developer/CommandLineTools/usr/lib/clang/11.0.3/include -isystem /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include -isystem /Library/Developer/CommandLineTools/usr/include -isystem /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks -I ./deps -L ./deps -l portaudio


default:
	rm -rf bin
	mkdir bin
	${CC} src/main.cpp src/wavetables.cpp ${FLAGS} -o bin/play


