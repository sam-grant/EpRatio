# Format Station 12 Crystal 24 fit for presentation

from ROOT import TFile, TCanvas, TH1D, gStyle, gPad, TPaveStats, TF1

file = TFile.Open("../ROOT/PlotsTimeXtalFidCorr_9day.root")

h = file.Get("St13_Ep_vs_t_24")

c = TCanvas("c","",800,600)

gStyle.SetStatFormat("6.3g");
h.Draw()
gPad.Update()

# Typical ROOT nonsense!
# gStyle.SetOptStat(10)
# gStyle.SetOptFit(1)
gStyle.SetOptStat(0)

# statBox = h.FindObject("stats")
# statBox.SetBorderSize(0)
# statBox.SetX1NDC(0.49)
# statBox.SetX2NDC(0.89)
# statBox.SetY1NDC(0.65)
# statBox.SetY2NDC(0.88)

# gPad.Update()
h.SetLineWidth(3)

# Fit a pol0 to set the y-range
lineFit = TF1("lineFit", "pol 0")
lineFit.SetLineWidth(0)
h.Fit(lineFit,"Q")
norm = lineFit.GetParameter(0)
h.Scale(1./norm)

h.GetXaxis().CenterTitle(1)
h.GetYaxis().CenterTitle(1)
h.GetXaxis().SetTitleSize(.04)
h.GetYaxis().SetTitleSize(.04)
h.GetYaxis().SetTitleOffset(1.25)
h.GetXaxis().SetTitleOffset(1.1)

h.GetYaxis().SetRangeUser(0.99,1.01)

h.GetXaxis().SetRangeUser(0,4.2*23)

h.SetTitle(";In fill time [#mus];E/p")

h.Draw()

c.SaveAs("../TestPlots/St12Xtal24Corr_9day.pdf")