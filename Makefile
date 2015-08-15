LD=clang
CXX=clang++

CXXFLAGS += -Wall -pedantic -Werror -std=c++11 -stdlib=libc++
LDFLAGS += -lc++

CXXFLAGS += -Isrc/
LDFLAGS += -lcurl

SRC=src/hugopeixoto/requests.cc
LIB=libhugopeixoto-requests.a

OBJ=$(SRC:.cc=.o)
all: test $(LIB)

$(LIB): $(OBJ)
	$(AR) rcs $@ $^

test: main.o $(LIB)
	$(LD) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf test main.o $(OBJ) $(LIB)
