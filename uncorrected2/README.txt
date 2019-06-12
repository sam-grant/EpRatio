Plotting code for gain uncorrected ntuples 

6/10/2019

Just use plotter_time_normalised_xtal.C!


Latest quality cuts: 
/unix/muons/g-2/omegaEU/v9_17_01_new/

plotter_uncorrected_quality.C is designed to read these

merged_uncorrected2.root used for talk 2

merged_uncorrected_new.root used for talk 2.5

everything beyond that is just iterations of "new"

...

plotter_uncorrected_crystals.C

is an attempt to generate root files to normalise the time disitributions on a crystal by crystal basis:

gain_by_xtal.root is just gain per xtal AFTER 60 us.

t_by_xtal.root is the time dists per xtal

....


nearly everything else is junk


