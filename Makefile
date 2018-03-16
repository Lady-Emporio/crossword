CC=g++
SOURCE=main.cpp bd.cpp
LIB=-lsqlite3
LIB_PATH=-L.
VERSION=-std=c++11
all:
	$(CC) $(SOURCE) $(LIB_PATH) $(LIB) $(VERSION)