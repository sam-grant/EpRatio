Target = gain_sag_function.exe gain_energy_function.exe gainFitter.exe cmap.exe
ROOTFLAGS = $(shell root-config --cflags)
ROOTLIBS = $(shell root-config --libs)

all:$(Target)

gain_sag_function.exe: gain_sag_function.cc
	g++ -o $@ gain_sag_function.cc $(Objects) $(ROOTFLAGS) $(ROOTLIBS)

gainFitter.exe: gainFitter.cc
	g++ -o $@ gainFitter.cc $(Objects) $(ROOTFLAGS) $(ROOTLIBS)

gain_energy_function.exe: gain_energy_function.cc
	g++ -o $@ gain_energy_function.cc $(Objects) $(ROOTFLAGS) $(ROOTLIBS)

cmap.exe: cmap.cc
	g++ -o $@ cmap.cc $(Objects) $(ROOTFLAGS) $(ROOTLIBS)
clear:
	rm *exe
