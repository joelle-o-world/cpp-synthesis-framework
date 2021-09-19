CC=g++

FLAGS=-I ../include -I ../vendor/include -std=c++14 -stdlib=libc++ -fPIC -isystem /usr/local/include -isystem /Library/Developer/CommandLineTools/usr/bin/../include/c++/v1 -isystem /Library/Developer/CommandLineTools/usr/lib/clang/11.0.3/include -isystem /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include -isystem /Library/Developer/CommandLineTools/usr/include -isystem /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks


runtest: 
	rm -rf bin
	mkdir bin
	${CC} src/main.cpp src/wavetables.cpp ${FLAGS} -o bin/test && bin/test | play -r 44100 -b 32 -e float -c 1 -t raw -

