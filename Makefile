CC=g++

FLAGS=-I ../include -I ../vendor/include -std=c++14 -stdlib=libc++ -fPIC -isystem /usr/local/include -isystem /Library/Developer/CommandLineTools/usr/bin/../include/c++/v1 -isystem /Library/Developer/CommandLineTools/usr/lib/clang/11.0.3/include -isystem /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include -isystem /Library/Developer/CommandLineTools/usr/include -isystem /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks


play: 
	rm -rf bin
	mkdir bin
	${CC} src/main.cpp src/wavetables.cpp ${FLAGS} -o bin/play && bin/play | play -r 44100 -b 32 -e float -c 1 -t raw -

tests:
	${CC} src/parse/parse.spec.cc ${FLAGS} -o bin/parse.test && bin/parse.test
