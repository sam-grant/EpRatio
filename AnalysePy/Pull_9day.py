from ROOT import TCanvas, TH1D, TFile, TStyle, TLegend, TPaveStats, TDirectory, THistPainter
import numpy as np

def pull(EpVal, LasVal, EpErr, LasErr):
    sigma = np.sqrt(np.square(EpErr) + np.square(LasErr))
    return (LasVal - EpVal) / sigma

def draw(h1, h2, name, title):
    # Get stats of h1
    h1.Draw()
    gPad.Update()
    statBox1 = h1.FindObject("stats")
    
    c = TCanvas("c1","",800,600)
    leg = TLegend(0.76,0.76,0.89,0.89)
    leg.AddEntry(h1,"E/p")
    leg.AddEntry(h2,"Laser")
    leg.SetBorderSize(0)
    h1.SetStats(0)
    h1.SetLineColor(2)
    h2.SetLineColor(8)
    h1.SetLineWidth(5)
    h2.SetLineWidth(5)
    h1.SetTitle(title)
    h1.GetXaxis().CenterTitle(1)
    h1.GetYaxis().CenterTitle(1)
    h1.GetXaxis().SetTitleSize(.04)
    h1.GetYaxis().SetTitleSize(.04)
    h1.GetYaxis().SetTitleOffset(1.1);
    h1.GetXaxis().SetTitleOffset(1.1);
    h1.Draw()
    h2.Draw("same")
    leg.Draw("same")
    c.SaveAs(plotName)

EpFile = TFile.Open("RootFiles/LaserParameters_9day.root")
laserFile = TFile.Open("RootFiles/EpParameters_9day_Q.root")

histNames = ["tau_13","tau_19","amp_13","amp_19"]
plotNames = "pyPlots_9day/pyPull_9day.pdf"
titleNames = ";Pull [#sigma];Entries"

for ihist in range(0,4):

    EpHist = EpFile.Get(histNames[i])
    laserHist = laserFile.Get(histNames[i])

    for xtal in range(0,54):

        EpVal = EpHist.GetBinContent(xtal+1)
        EpErr = EpHist.GetBinContent(xtal+1)
                
        lasVal = laserHist.GetBinContent(xtal+1)
        lasErr = laserHist.GetBinError(xtal+1)

        

        

    if(i==0): EpHist.GetYaxis().SetRangeUser(2,13)
    if(i==1): EpHist.GetYaxis().SetRangeUser(2,13)
    if(i==2): EpHist.GetYaxis().SetRangeUser(0,0.08)
    if(i==3): EpHist.GetYaxis().SetRangeUser(0,0.03)

    draw(EpHist,laserHist,plotNames[i],titleNames[0])
    
