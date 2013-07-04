PROJECT = demo
CC = gcc
COMPILE_OPTIONS = -pedantic -Wall

HEADERS = loadBMP.h
SOURCE_FILES = loadBMP.c demo.c

all: $(PROJECT)

$(PROJECT):
	$(CC) $(SOURCE_FILES) -o $(PROJECT)

clean:
	rm -f $(PROJECT) demo.bmp
