from ROOT import TCanvas, TF1, TH1D, TFile, TStyle, TLegend, TColor

def draw(h1, h2, plotName, title):
    c = TCanvas("c","",800,600)
    leg = TLegend(0.11,0.69,0.39,0.89)
    leg.AddEntry(h1,"Laser")
    leg.AddEntry(h2,"E/p")
    leg.SetBorderSize(0)
    h1.SetStats(0)
    h1.SetLineColor(2)
    h1.SetMarkerColor(2)
    h2.SetLineColor(8)
    h2.SetMarkerColor(8)
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

laser = TFile.Open("../ROOT/LaserParametersProduction_9day.root")
Ep = TFile.Open("../ROOT/EpParameters_9day.root")

histNames = ["tau_13","tau_19","amp_13","amp_19"]
plotNames = ["../TestPlots/St13ScatterTau.pdf","../TestPlots/St19ScatterTau.pdf",
            "../TestPlots/St13ScatterAmp.pdf","../TestPlots/St19ScatterAmp.pdf"]
titleNames = [";Crystal Number;#tau [#mus]",";Crystal Number;#tau [#mus]",
            ";Crystal Number;#alpha",";Crystal Number;#alpha"]

for i in range(0,4):

    EpHist = Ep.Get(histNames[i])
    laserHist = laser.Get(histNames[i])

    if(i==0): laserHist.GetYaxis().SetRangeUser(2,13)
    if(i==1): laserHist.GetYaxis().SetRangeUser(2,16)
    if(i==2): laserHist.GetYaxis().SetRangeUser(0,0.055)
    if(i==3): laserHist.GetYaxis().SetRangeUser(0,0.03)

    draw(laserHist,EpHist,plotNames[i],titleNames[i])
    
