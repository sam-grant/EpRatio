# Calo fits

from ROOT import TFile, TCanvas, TH1D, TF1, gStyle, gPad, TPaveStats

file = TFile.Open("../ROOT/PlotsimeCalo_9day.root")

for calo in range(13,20,6):
  print(calo)

  h = file.Get("St"+str(calo)+"_Ep_vs_t")

  c = TCanvas("c","",800,600)

  lineFit = TF1("lineFit","pol 0")
  lineFit.SetLineWidth(0)
  h.Fit(lineFit)
  norm = lineFit.GetParameter(0)
  h.Scale(1./norm)
  h.GetYaxis().SetRangeUser(0.99,1.01)

  gStyle.SetStatFormat("6.3g");
  h.Draw()
  gPad.Update()

  # Typical ROOT nonsense!
  gStyle.SetOptStat(0)
  #gStyle.SetOptFit(1)
  #gStyle.SetOptStat(10)

  # statBox = h.FindObject("stats")
  # statBox.SetBorderSize(0)
  # statBox.SetX1NDC(0.49)
  # statBox.SetX2NDC(0.89)
  # statBox.SetY1NDC(0.65)
  # statBox.SetY2NDC(0.88)

  # gPad.Update()

  h.GetXaxis().CenterTitle(1)
  h.GetYaxis().CenterTitle(1)
  h.GetXaxis().SetTitleSize(.04)
  h.GetYaxis().SetTitleSize(.04)
  h.GetYaxis().SetTitleOffset(1.25)
  h.GetXaxis().SetTitleOffset(1.1)

  h.SetLineWidth(3)

  h.GetXaxis().SetRangeUser(0,4.2*23)

  h.SetTitle("Station "+str(calo-1)+";In fill time [#mus];E/p")

  h.Draw()

  c.SaveAs("../TestPlots/Calo"+str(calo)+"_9day.pdf")