all:
	g++ -DOSX=1 -Iinclude/ -Isrc/UCB/ -o jezzball src/* -lGL -lGLU -lglut

install:
	cp ./jezzball /bin/
