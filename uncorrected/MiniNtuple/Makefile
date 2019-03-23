C++ = g++
C_FLAGS = -g

ROOTCFLAGS=$(shell root-config --cflags)
ROOTLIBS=$(shell root-config --libs)
NTUPLE_DEPS=Ntuple_dict.so Ntuple_Classes.h

SOURCES = $(shell find . -name "*.C")

all : $(SOURCES:.C=)

clean:
	rm Ntuple_dict* $(SOURCES:.C=)


Ntuple_dict.so: LinkDef.h Ntuple_Classes.h
	rootcling -f Ntuple_dict.c  -p $<
	$(C++) -shared -c $(ROOTCFLAGS) $(C_FLAGS) Ntuple_dict.c -o Ntuple_dict.so


Skimmer: Skimmer.C Skimmer.h $(NTUPLE_DEPS)  Skimmer.C Skimmer.h ../Reader.o 
	$(C++) $(ROOTCFLAGS) $(C_FLAGS) -I.. Ntuple_dict.so ../Reader.o  $<  -o Skimmer $(ROOTLIBS)


##generic rule for any plotter:
#%: Ntuple_Classes.h %.h %.C  
#	$(C++) $(ROOTCFLAGS) $(C_FLAGS)  $^ -o $@ Ntuple_dict.so $(ROOTLIBS)


%: %.C Plotter.h $(NTUPLE_DEPS) 
	$(C++) $(ROOTCFLAGS) $(C_FLAGS) Ntuple_dict.so $< -o $@ $(ROOTLIBS)


#%: %.C Plotter.h Reader.o
#	$(C++) $(ROOTCFLAGS) $(C_FLAGS) Reader.o $<  -o $@  $(ROOTLIBS)



