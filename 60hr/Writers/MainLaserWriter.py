# Read laser parameters and dump then into a ROOT file
# Sam Grant
# Oct 2019

from ROOT import TH1D, TCanvas, TFile
import pandas as pd
import numpy as np
from array import array

def Draw1D(h1, title, output):

	c1 = TCanvas("c1"," ",800,600)

	h1.SetTitle(title)

	h1.GetXaxis().CenterTitle(1)
	h1.GetYaxis().CenterTitle(1)
	h1.GetXaxis().SetTitleSize(.04)
	h1.GetYaxis().SetTitleSize(.04)
	h1.GetXaxis().SetTitleOffset(1.1)
	h1.GetYaxis().SetTitleOffset(1.1)

	h1.SetLineWidth(3)
	h1.SetLineColor(1)
	h1.SetMarkerColor(1)

	h1.Draw()
	output.Write()

# Book output
outputFilePath = "../ROOT/LaserParametersProduction_60hr.root"
outputFile = TFile.Open(outputFilePath,"RECREATE")

inFile = "../Txt/latest60.txt"

# Read in space delimited txt file, no header
data = pd.read_csv(inFile, header=None, delim_whitespace=True) 

# Slice columns, row by column, and dump everything into seperate arrays
xtals = np.array(data.iloc[0:54,2])

amp13 = np.array(data.iloc[0:54,2])
amp19 = np.array(data.iloc[54:108,2])

ampErr13 = np.array(data.iloc[0:54,3])
ampErr19 = np.array(data.iloc[54:108,3])

tau13 = np.array(data.iloc[0:54,4])
tau19 = np.array(data.iloc[54:108,4])

tauErr13 = np.array(data.iloc[0:54,5])
tauErr19 = np.array(data.iloc[54:108,5])

valuesArray = [tau13,tau19,amp13,amp19]
errorsArray = [tauErr13,tauErr19,ampErr13,ampErr19]

# Stick with old naming convention
histNames = ["tau_13","tau_19","amp_13","amp_19"]

for ihist in range(0,4):

	hist = TH1D(histNames[ihist],"",54,-0.5,53.5)

	for xtal in range(0,54):

		hist.SetBinContent(xtal+1,valuesArray[ihist][xtal])
		hist.SetBinError(xtal+1,errorsArray[ihist][xtal])


	Draw1D(hist,";xtal;value",outputFile)

outputFile.Close()
print("Created "+outputFilePath)