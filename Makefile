CXX=g++
CFLAGS=-std=c++17 -c 

src=$(wildcard *.cpp)
srcO=$(src:.cpp=.o)

Echec.out: $(srcO)
	@$(CXX) $^ -o $@

%.o: %.cpp
	@$(CXX) $< $(CFLAGS) 

.PHONY: echec
echec:Echec.out
	@./Echec.out

.PHONY: clean
clean:
	rm -rf *.o
