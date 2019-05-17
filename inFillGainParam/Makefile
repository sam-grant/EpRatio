Target = gainFitter_xtal.exe csv_to_ROOT.exe MIP_plotter.exe params_vs_xtal.exe

ROOTFLAGS = $(shell root-config --cflags)
ROOTLIBS = $(shell root-config --libs)

all:$(Target)

csv_to_ROOT.exe: csv_to_ROOT.cc
	g++ -o $@ csv_to_ROOT.cc $(Objects) $(ROOTFLAGS) $(ROOTLIBS)


gainFitter_xtal.exe: gainFitter_xtal.cc
	g++ -o $@ gainFitter_xtal.cc $(Objects) $(ROOTFLAGS) $(ROOTLIBS)

MIP_plotter.exe: MIP_plotter.cc
	g++ -o $@ MIP_plotter.cc $(Objects) $(ROOTFLAGS) $(ROOTLIBS)

params_vs_xtal.exe: params_vs_xtal.cc
	g++ -o $@ params_vs_xtal.cc $(Objects) $(ROOTFLAGS) $(ROOTLIBS)
clean:
	rm *exe
