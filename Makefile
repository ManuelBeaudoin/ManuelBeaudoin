CXX=$(g++)
CFLAGS= $(-std=c++17 -Wall) 

src=$(wildcard *.cpp)

echec: $(src)
  $(CXX) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
  rm -rf *.o

#g++ Classes.cpp Partie.cpp Main.cpp FinPartie.cpp -o echec -std=c++17 -Wall
