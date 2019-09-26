source := $(wildcard *.c *.cpp)

objects := $(addsuffix .o, $(basename $(source)))

$(objects) : $(source)
	g++ -c -I. -I/mingw64/include/c++/9.2.0/ -Wc++17-compat $^ -o $@

system: $(source)
	g++ -I. -I/mingw64/include/c++/9.2.0/ -Wc++17-compat $^ -o $@

all: system
        
clean:
	rm $(objects)
	rm coder.exe