BINARY_NAME=app.exe

build:
	del ${BINARY_NAME}
	g++ gui.cpp main.cpp -lopengl32 -lglut -lgdi32 -lwinspool -lcomdlg32 -o ${BINARY_NAME}

build-alt:
	gcc gui.cpp main.cpp -lopengl32 -lglut -lgdi32 -lwinspool -lcomdlg32 -o ${BINARY_NAME}

run:
	@./${BINARY_NAME}

