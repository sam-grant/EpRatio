# Draw E vs p 2D plots, with no quality cuts, with calo vertex cuts, and with positron vertex cuts
# For the 9 day dataset
# Sam Grant - Oct 2019

from ROOT import TCanvas, TH2D, TFile, TStyle, gStyle

def draw(h1, plotName, title):
    gStyle.SetPalette(55)
    c = TCanvas("c","",800,600)
    h1.SetStats(0)
    h1.SetTitle(title)
    h1.GetXaxis().CenterTitle(1)
    h1.GetYaxis().CenterTitle(1)
    h1.GetXaxis().SetTitleSize(.04)
    h1.GetYaxis().SetTitleSize(.04)
    h1.GetYaxis().SetTitleOffset(1.1);
    h1.GetXaxis().SetTitleOffset(1.1);
    h1.GetXaxis().SetLimits(0,4)
    h1.GetYaxis().SetLimits(0,4)
    c.SetRightMargin(0.13)
    h1.Draw("COLZ")
    # h1.SetMaxDigits(2)
    c.SaveAs(plotName)

inputFileNames = ["../ROOT/RawDemoPlots_9day.root",
                "../ROOT/RawDemoPlotsCalo_9day.root",
                "../ROOT/RawDemoPlotsPositron_9day.root"]

plotNames = ["noCuts","caloVertexCuts","positronCuts"]

for i in range(0,3):

    inputFile = TFile.Open(inputFileNames[i])

    h1 = inputFile.Get("St13_E_vs_p")
    h2 = inputFile.Get("St19_E_vs_p")
    h1.Add(h2,+1)
    draw(h1,"../TestPlots/E_vs_p_"+plotNames[i]+".pdf",";Track momentum [GeV];Cluster energy [GeV]")