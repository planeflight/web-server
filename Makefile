CC = clang++
CFLAGS = -g -Wall -Wextra -Wcast-qual -Wconversion-null -Wformat-security -Wmissing-declarations -Woverlength-strings -Wpointer-arith -Wundef -Wunused-local-typedefs -Wunused-result -Wvarargs -Wvla -Wwrite-strings -DNOMINMAX -Werror -fno-omit-frame-pointer -std=c++20 -fPIC

PROFILE_FLAGS= -pg
LDFLAGS = -g
INCLUDE = -I.

SRC = src/main.cpp src/response.cpp src/server.cpp
OBJ = $(patsubst %.cpp, $(BIN)/%.o, $(SRC)) 

BIN = bin
EXEC = $(BIN)/server

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJ)
	mkdir -p $(BIN)
	$(CC) -o $@ $^ 

$(BIN)/%.o: %.cpp
	mkdir -p $(@D)
	$(CC) -o $@ -c $< $(CFLAGS) $(INCLUDE)

clean:
	rm -rf $(BIN)
