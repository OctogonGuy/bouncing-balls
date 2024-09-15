bouncing_balls: bin clean src/main.cpp src/util.h src/util.cpp src/ball.h src/ball.cpp
	g++ src/ball.h src/util.h src/util.cpp src/ball.cpp src/main.cpp -lSDL2 -o bin/bouncing_balls

bin:
	mkdir bin

clean:
	rm -f bin/*
