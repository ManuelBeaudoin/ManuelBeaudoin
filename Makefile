CXX=$(g++)
CFLAGS= $(-std=c++17 -Wall) 

src = $(wildcard *.c)
obj = $(src:.c=.o)

myprog: $(obj)
  $(CXX) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
  rm -f $(obj) myprog

#g++ Classes.cpp Partie.cpp Main.cpp FinPartie.cpp -o echec -std=c++17 -Wall
