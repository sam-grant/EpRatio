Target = Pull.exe

ROOTFLAGS = $(shell root-config --cflags)
ROOTLIBS = $(shell root-config --libs)

all:$(Target)

Pull.exe: Pull.C
	g++ -o $@ Pull.C $(Objects) $(ROOTFLAGS) $(ROOTLIBS)

clean:
	rm *exe
