

CC=g++
std= -std=c++11
CFLAGS=-c 


all: encode decode
	$(CC) $(std) encode.o user_functions.o -o encode
	$(CC) $(std) decode.o user_functions.o -o decode
encode: encode.o user_functions.o
	$(CC) $(std) encode.o user_functions.o -o encode

decode: decode.o user_functions.o
	$(CC) $(std) decode.o user_functions.o -o decode
decode.o: decode.cpp user_functions.o
	$(CC) $(std) -c decode.cpp

encode.o: encode.cpp user_functions.o
	$(CC) $(std) -c encode.cpp

user_functions.o: user_functions.cpp
	$(CC) $(std) -c user_functions.cpp