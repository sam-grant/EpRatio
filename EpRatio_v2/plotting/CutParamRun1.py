from ROOT import TFile, TLine

from plotFunc import *

LoadPlotFunc()

eFracMaxCut = 0.8

inFile = TFile.Open("cutParamPlots_Run1.root")

hists = [ "S12_caloVertexClusterTimeDiff", "S18_caloVertexClusterTimeDiff", "caloVertexClusterRadialDiff", "logEoverP", "eFracMax_noCut", "EvsP" ]

qual = [ "noQ", "cQ", "pQ", "lQ" ] 

for i_qual in range(len(qual)):

	plots = []

	for i_hists in range(len(hists)):

		if(hists[i_hists] != "eFracMax_noCut"): name = hists[i_hists]+"_"+qual[i_qual]
		else: name = hists[i_hists]
		plots.append(inFile.Get(name))


	# Time difference
	plots[0].GetXaxis().SetRangeUser(-15,10)
	FancyDraw1DOverlay4YLine(plots[0], plots[1], ";Vertex-cluster time difference, #Deltat, [ns];Track-cluster matches", "caloVertexClusterTimeDiff_"+qual[i_qual])

	# Radial difference
	plots[2].GetXaxis().SetRangeUser(0,50)
	plots[2].SetStats(0)
	FancyDraw1DYLine(plots[2],";Vertex-cluster radial position difference, #DeltaR, [mm];Track-cluster matches", "caloVertexClusterRadialDiff_"+qual[i_qual], 30)

	plots[3].GetXaxis().SetRangeUser(-4,2)
	plots[3].SetStats(0)
	FancyDraw1D2YLine(plots[3],";Log(E/p);Track-cluster matches", "logEoverP_"+qual[i_qual])

	# plots[3].GetXaxis().SetRangeUser(-4,2)
	plots[4].SetStats(0)
	FancyDraw1DYLine(plots[4],";Fraction of cluster energy in the most energetic crystal;Clusters", "eFracMax_noCut", 0.8)

	plots[5].SetStats(0)
	plots[5].GetXaxis().SetLimits(0,3.2)
	plots[5].GetYaxis().SetLimits(0,3.2)
	FancyDraw2D(plots[5],";Track momentum [GeV];Cluster energy [GeV]","EvsP_"+qual[i_qual])

		# Plot
# 		if(hist[i_hist]="EvsP"):
# 			plot.GetYaxis().SetLimits(0,3.2)
# 			plot.GetXaxis().SetLimits(0,3.2)
# 			FancyDraw2D(plot,";Cluster energy [GeV];Track momentum [GeV]",name)

# 		elif(hists[i_hist]="eFracMax"):
# 			FancyDraw1DYLine(plot,";Fraction of cluster energy in the most energetic crystal;Clusters", name, eFracMaxCut)

#       	elif(hists[i_hist]="S12_caloVertexClusterTimeDiff" or hists[i_hist]="S18_caloVertexClusterTimeDiff"):
#       		FancyDraw1D(plot, ";Calo vertex time #minus cluster time [ns];Track-cluster matches", name)

#       	elif(hists[i_hist]="caloVertexClusterRadialDiff")





# FancyDraw1DYLine(hists[0],";Fraction of cluster energy in the most energetic crystal;Clusters","../images/Run1/CutParamPlots/eFracMax", cut)
# # Need to split into stations!
# FancyDraw1D(hists[1],";Calo vertex position #minus cluster position [mm];Track-cluster matches","../images/Run1/CutParamPlots/caloVertexClusterTimeDiff")
# FancyDraw1D(hists[2],";Calo vertex time #minus cluster time [ns];Track-cluster matches","../images/Run1/CutParamPlots/caloVertexClusterRadialDiff")
# FancyDraw1D(hists[3],";Track-cluster matches;Log(E/p)","../images/Run1/CutParamPlots/logEoverP")
# hists[4].GetYaxis().SetLimits(0,3.2)
# hists[4].GetXaxis().SetLimits(0,3.2)
# FancyDraw2D(hists[4],";Cluster energy [GeV];Track momentum [GeV]","../images/Run1/CutParamPlots/EvsP")


