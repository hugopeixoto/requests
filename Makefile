LD=clang
CXX=clang++
CXXFLAGS += -Wall -pedantic -Werror -std=c++11 -stdlib=libc++
LDFLAGS += -lcurl -lc++

all: test librequests.a

librequests.a: requests.o
	$(AR) rcs $@ $^

test: main.o librequests.a
	$(LD) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf *.o test librequests.a
