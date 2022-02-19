CC=g++

FLAGS=-I ../include -I ../vendor/include -std=c++14 -stdlib=libc++ -fPIC -isystem /usr/local/include -isystem /Library/Developer/CommandLineTools/usr/bin/../include/c++/v1 -isystem /Library/Developer/CommandLineTools/usr/lib/clang/11.0.3/include -isystem /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include -isystem /Library/Developer/CommandLineTools/usr/include -isystem /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks -I ./deps -L ./deps -l portaudio -framework CoreServices -framework CoreFoundation -framework AudioUnit -framework AudioToolbox -framework CoreAudio -g


default:
	rm -rf bin
	mkdir bin
	${CC} src/main.cpp src/wavetables.cpp src/AudioProcess.cpp src/connect.cpp src/utils/ordinal.cpp src/play.cpp src/TypedSignalBuffer.cpp src/programs/goBoop.cpp src/components/**.cpp ${FLAGS} -o bin/play
