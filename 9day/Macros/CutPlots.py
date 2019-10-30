# Draw cut plots, with no quality cuts, with calo vertex cuts, and with positron vertex cuts
# For the 9 day dataset
# Sam Grant - Oct 2019

from ROOT import TCanvas, TLegend, TH2D, TFile, TStyle, gStyle


def draw(h1, h2, plotName, title, LR):

    c = TCanvas("c","",600,600)

    if(LR==0): l = TLegend(0.55,0.65,0.89,0.89)
    elif (LR==1): l = TLegend(0.11,0.65,0.49,0.89)

    l.AddEntry(h1,"Station 12")
    l.AddEntry(h2,"Station 18")
    l.SetBorderSize(0)

    h1.SetStats(0)
    h1.SetTitle(title)
    h1.GetXaxis().CenterTitle(1)
    h1.GetYaxis().CenterTitle(1)
    h1.GetXaxis().SetTitleSize(.04)
    h1.GetYaxis().SetTitleSize(.04)
    h1.GetYaxis().SetTitleOffset(1.2);
    h1.GetXaxis().SetTitleOffset(1.1);
    h1.GetYaxis().SetMaxDigits(3)
    h1.SetLineWidth(5)
    h2.SetLineWidth(5)
    h1.SetLineColor(4)
    h1.SetMarkerColor(4)
    h2.SetLineColor(2)
    h2.SetMarkerColor(2)
    # c.SetLeftMargin(0.13)
    h1.Draw()
    h2.Draw("same")
    l.Draw("same")
    # h1.SetMaxDigits(2)
    c.SaveAs(plotName)

inputFileNames = ["../ROOT/RawDemoPlots_9day.root",
                "../ROOT/RawDemoPlotsCalo_9day.root",
                "../ROOT/RawDemoPlotsPositron_9day.root"]

plotNames = ["noCuts","caloVertexCuts","positronCuts"]

histNames = ["dR","dt","logEop"]
# histNames19 = ["St19_dR","St19_dt","St19_logEop"]

titles = [";Track-cluster #DeltaR [ns];Entries",";Track-cluster #Deltat [ns];Entries",";Track-cluster Log(E/p);Entries"]

# fNames = ["pyPlots_9day/dR.pdf","pyPlots_9day/dt.pdf","pyPlots_9day/logEop.pdf"]

for i in range(0,3):

    inputFile = TFile.Open(inputFileNames[i])

    for j in range(0,3):

        h1 = inputFile.Get("St13_"+histNames[j])
        h2 = inputFile.Get("St19_"+histNames[j])
        print("histNames "+histNames[j])
        print("i "+str(i)+"; j "+str(j))
        LR = 0
        if (j==2): LR = 1
        draw(h1,h2,"../TestPlots/"+histNames[j]+"_"+plotNames[i]+".pdf",titles[j], LR)

