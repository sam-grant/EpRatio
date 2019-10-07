from ROOT import TCanvas, TF1, TH1D, TFile, TStyle, TLegend, TColor

def draw(h1, h2, plotName, title):
    c = TCanvas()
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
    h1.GetXaxis().SetTitleSize(.05)
    h1.GetYaxis().SetTitleSize(.05)
    h1.GetYaxis().SetTitleOffset(.8);
    h1.GetXaxis().SetTitleOffset(0.8);
    h1.Draw()
    h2.Draw("same")
    leg.Draw("same")
    c.SaveAs(plotName)

Ep = TFile.Open("RootFiles/LaserParameters_9day.root")
laser = TFile.Open("RootFiles/EpParameters_9day_Q.root")

histNames = ["tau_13","tau_19","amp_13","amp_19"]
plotNames = ["pyPlots_9day/St13ScatterTau.pdf","pyPlots_9day/St19ScatterTau.pdf",
             "pyPlots_9day/St13ScatterAmp.pdf","pyPlots_9day/St19ScatterAmp.pdf"]
titleNames = ["Station 12;Crystal Number;#tau [#mus]","Station 18;Crystal Number;#tau [#mus]",
              "Station 12;Crystal Number;#alpha""Station 18;Crystal Number;#alpha"]

for i in range(0,4):

    EpHist = Ep.Get(histNames[i])
    laserHist = laser.Get(histNames[i])

    if(i==0): EpHist.GetYaxis().SetRangeUser(2,13)
    if(i==1): EpHist.GetYaxis().SetRangeUser(2,13)
    if(i==2): EpHist.GetYaxis().SetRangeUser(0,0.08)
    if(i==3): EpHist.GetYaxis().SetRangeUser(0,0.03)

    draw(EpHist,laserHist,plotNames[i],titleNames[0])
    