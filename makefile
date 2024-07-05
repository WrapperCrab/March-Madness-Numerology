#workaround for windows powershell
ifeq ($(OS),Windows_NT)
RM = del /Q /F
CP = copy /Y
ifdef ComSpec
SHELL := $(ComSpec)
endif
ifdef COMSPEC
SHELL := $(COMSPEC)
endif
else
RM = rm -rf
CP = cp -f
endif

Numerology: main.o 2024alg.o
	g++ main.o 2024alg.o -o Numerology

main.o: main.cpp 2024alg.h
	g++ -c main.cpp

2024alg.o: 2024alg.cpp 2024alg.h
	g++ -c 2024alg.cpp

clean:
	-$(RM) Numerology.exe *.o

run: Numerology
	./Numerology
