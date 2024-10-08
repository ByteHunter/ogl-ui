BINARY_NAME=app.exe

build:
	g++ -c gui.cpp
	g++ -c main.cpp
	g++ gui.o main.o -lopengl32 -lglut -lgdi32 -o ${BINARY_NAME}

run:
	@./${BINARY_NAME}

