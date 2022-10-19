from ROOT import TFile, TF1, TPaveStats, TH1D
import math as math
import pandas as pd
from plotFunc import *

def pull(laserAmp, laserAmpErr, EpAmp, EpAmpErr):
	sigma = math.sqrt(pow(EpAmpErr,2) + pow(laserAmpErr, 2)) 
	return (laserAmp - EpAmp) / sigma

EpInput = ["../text/EpRatio/60h.txt", "../text/EpRatio/HK.txt", "../text/EpRatio/9d.txt", "../text/EpRatio/EG.txt"]
laserInput = ["../text/Laser/60h.txt", "../text/Laser/HK.txt", "../text/Laser/9d.txt", "../text/Laser/EG.txt"]
names = ["60h", "HK", "9d", "EG"]

# loop thro datasets/files
for i in range(len(EpInput)): 

	# if(i!=0): continue

	# Read input
	ep = pd.read_csv(EpInput[i]) 
	laser = pd.read_csv(laserInput[i])

	ep_a = ep['Alpha'].tolist()
	l_a = laser['Alpha'].tolist()
	ep_da = ep['dAlpha'].tolist()
	l_da = laser['dAlpha'].tolist()

	hist = TH1D("","hist",20,-5,5)

	for j in range(len(ep_a)):
		pull_ = pull(l_a[j], l_da[j], ep_a[j], ep_da[j])
		if(abs(pull_)>3): print(i,j,pull_) 
		hist.Fill(pull_)

	gStyle.SetOptStat(111111);
	FancyDraw1DText(hist,";Pull [#sigma];Fits","../images/"+names[i]+"/pulls_"+names[i])