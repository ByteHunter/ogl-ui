BINARY_NAME=app.exe

build:
	g++ gui.cpp main.cpp -static -lopengl32 -lgdi32 -lwinspool -lcomdlg32 -o ${BINARY_NAME}

run:
	@./${BINARY_NAME}

