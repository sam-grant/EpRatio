Target = gainFitter_xtal.exe inFillGainParams_laser_xtal.exe inFillGainParams_Ep_xtal.exe MIP_plotter.exe params_vs_xtal.exe 2D_plots.exe stat_pull.exe 2D_plots_pull.exe  1D_plots.exe scatter_plots.exe xtal_map.exe frac_shift.exe versus_shift.exe combined_1D.exe combined_2D.exe

ROOTFLAGS = $(shell root-config --cflags)
ROOTLIBS = $(shell root-config --libs)

all:$(Target)

combined_1D.exe: combined_1D.cc
	g++ -o $@ combined_1D.cc $(Objects) $(ROOTFLAGS) $(ROOTLIBS)

combined_2D.exe: combined_2D.cc
	g++ -o $@ combined_2D.cc $(Objects) $(ROOTFLAGS) $(ROOTLIBS)

versus_shift.exe: versus_shift.cc
	g++ -o $@ versus_shift.cc $(Objects) $(ROOTFLAGS) $(ROOTLIBS)

frac_shift.exe: frac_shift.cc
	g++ -o $@ frac_shift.cc $(Objects) $(ROOTFLAGS) $(ROOTLIBS)

inFillGainParams_laser_xtal.exe: inFillGainParams_laser_xtal.cc
	g++ -o $@ inFillGainParams_laser_xtal.cc $(Objects) $(ROOTFLAGS) $(ROOTLIBS)

xtal_map.exe: xtal_map.cc
	g++ -o $@ xtal_map.cc $(Objects) $(ROOTFLAGS) $(ROOTLIBS)

inFillGainParams_Ep_xtal.exe: inFillGainParams_Ep_xtal.cc
	g++ -o $@ inFillGainParams_Ep_xtal.cc $(Objects) $(ROOTFLAGS) $(ROOTLIBS)

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

clean:
	rm *exe
