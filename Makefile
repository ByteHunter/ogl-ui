BINARY_NAME=app.exe

build:
	g++ gui.cpp main.cpp -lopengl32 -lfreeglut -lgdi32 -lwinspool -lcomdlg32 -o ${BINARY_NAME}

run:
	@./${BINARY_NAME}

