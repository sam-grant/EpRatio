Target = gainFitter_xtal.exe inFillGainParams_laser_xtal.exe inFillGainParams_sam_xtal.exe MIP_plotter.exe params_vs_xtal.exe 2D_plots.exe stat_pull.exe 2D_plots_pull.exe stat_pull_1D.exe 1D_plots.exe scatter_plots.exe

ROOTFLAGS = $(shell root-config --cflags)
ROOTLIBS = $(shell root-config --libs)

all:$(Target)

inFillGainParams_laser_xtal.exe: inFillGainParams_laser_xtal.cc
	g++ -o $@ inFillGainParams_laser_xtal.cc $(Objects) $(ROOTFLAGS) $(ROOTLIBS)

inFillGainParams_sam_xtal.exe: inFillGainParams_sam_xtal.cc
	g++ -o $@ inFillGainParams_sam_xtal.cc $(Objects) $(ROOTFLAGS) $(ROOTLIBS)

1D_plots.exe: 1D_plots.cc
	g++ -o $@ 1D_plots.cc $(Objects) $(ROOTFLAGS) $(ROOTLIBS)

scatter_plots.exe: scatter_plots.cc
	g++ -o $@ scatter_plots.cc $(Objects) $(ROOTFLAGS) $(ROOTLIBS)

gainFitter_xtal.exe: gainFitter_xtal.cc
	g++ -o $@ gainFitter_xtal.cc $(Objects) $(ROOTFLAGS) $(ROOTLIBS)

MIP_plotter.exe: MIP_plotter.cc
	g++ -o $@ MIP_plotter.cc $(Objects) $(ROOTFLAGS) $(ROOTLIBS)

params_vs_xtal.exe: params_vs_xtal.cc
	g++ -o $@ params_vs_xtal.cc $(Objects) $(ROOTFLAGS) $(ROOTLIBS)

2D_plots.exe: 2D_plots.cc
	g++ -o $@ 2D_plots.cc $(Objects) $(ROOTFLAGS) $(ROOTLIBS)

stat_pull.exe: stat_pull.cc
	g++ -o $@ stat_pull.cc $(Objects) $(ROOTFLAGS) $(ROOTLIBS)

2D_plots_pull.exe: 2D_plots_pull.cc
	g++ -o $@ 2D_plots_pull.cc $(Objects) $(ROOTFLAGS) $(ROOTLIBS)

stat_pull_1D.exe: stat_pull_1D.cc
	g++ -o $@ stat_pull_1D.cc $(Objects) $(ROOTFLAGS) $(ROOTLIBS)


clean:
	rm *exe
