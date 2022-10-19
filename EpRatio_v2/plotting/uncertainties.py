from ROOT import TFile, TF1, TPaveStats
import math as math
import pandas as pd
from plotFunc import *

# Define percentage uncertainty
def perUnc(laserAmp, EpAmp):
	# return math.sqrt(abs(pow(laserAmp,2)-pow(EpAmp,2)))/laserAmp
	return (laserAmp-EpAmp)/laserAmp

# Define percentage uncertainty uncertainty
def perUncErr(laserAmp, laserAmpErr, EpAmp, EpAmpErr): 
	t1 = (EpAmp*laserAmpErr) / pow(laserAmp,2);
	t2 = EpAmpErr / laserAmp;
	return math.sqrt(pow(t1,2) + pow(t2,2))

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

	frac = []
	frac_err = []
	x = []
	xe = []

	for j in range(len(ep_a)):

		frac.append(perUnc(l_a[j], ep_a[j]))
		frac_err.append(perUncErr(l_a[j], l_da[j], ep_a[j], ep_da[j]))
		x.append(j+1)
		xe.append(0)
		# print(frac_err[j]



	tgr = DefineScatErrors(x, xe, frac, frac_err)
	# Fit a line to the fucker
	lineFit = TF1("lineFit", "pol 0")

	lineFit.SetLineWidth(3)
	# gStyle->SetOptStat(10); 
  	gStyle.SetOptFit(110)
  	statBox = tgr.FindObject("stats"); 
  	# statBox.SetLineWidth(0)

  # tps1->SetX1NDC(0.11);
  # tps1->SetX2NDC(0.50);
  # tps1->SetY1NDC(0.69);
  # tps1->SetY2NDC(0.89);
	tgr.Fit(lineFit)
	DrawScat(tgr,";Fit number;#Delta#alpha/#alpha","../images/"+names[i]+"/fracUnc_"+names[i])


	# laser.drop([0,1], axis=0, inplace=True)
	# xtals = ep['Xtal'].tolist()
	# print(laser)
	# epAlpha = ep['Alpha'].tolist()
	# epAlphaErr = ep['dAlpha'].tolist()
	# lasAlpha = laser['Alpha'].tolist()
	# lasAlphaErr = laser['dAlpha'].tolist()
	# laser = laser.drop(xtals, inplace=True)
	# print(laser)
	# indices = []
	# for j in range(len(xtals)):

	# 	# print(int(laser[(laser['Xtal']==xtals[j]) & (laser['Calo']==calos[j])].index))
	#  	indices = laser[(laser['Xtal']!=xtals[j]) & (laser['Calo']!=calos[j])].index
	# # # 	print(index)
	# 	laser.drop(laser.index[indices], inplace=True)

	# print(laser)
	# if(laser['Xtal']==ep['Xtal']): print(laser)


	# print(ep['Xtal'].tolist())
	# # Recreate dataframe selecting crystals which appear in the EpRatio file (isin method)
	# laser=laser[laser['Xtal'].isin(ep['Xtal'].tolist())] # & (laser['Calo'].isin(ep['Calo'].tolist()))]
	# # laser=laser[laser['Calo'].isin(ep['Calo'].tolist())] # & (laser['Calo'].isin(ep['Calo'].tolist()))]

	# xtals = ep['Xtal'].tolist()
	# epAlpha = ep['Alpha'].tolist()
	# epAlphaErr = ep['dAlpha'].tolist()
	# lasAlpha = laser['Alpha'].tolist()
	# lasAlphaErr = laser['dAlpha'].tolist()

	# for j in range(len(xtals)): 

	#  	if(laser.loc[])




			# print(ep['Alpha'])
	# Now, get the uncertainties
	# unc = perUnc[laser['Alpha'],ep['Alpha']]
