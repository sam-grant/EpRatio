# Draw a gaussian / double gaussian fits

# macro was not completed 

from ROOT import TH1D, TCanvas 

def FancyDraw1D(hist1, title, fname): 

	c0 = TCanvas("","",800,600)

	#hist1.SetStats(0)

	hist1.SetTitle(title)
			
	hist1.GetXaxis().SetTitleSize(.04)
	hist1.GetYaxis().SetTitleSize(.04)
	hist1.GetXaxis().SetTitleOffset(1.1)
	hist1.GetYaxis().SetTitleOffset(1.1)
	hist1.GetXaxis().CenterTitle(1)
	hist1.GetYaxis().CenterTitle(1)
 	hist1.GetYaxis().SetMaxDigits(4)

	hist1.SetLineWidth(3)
	hist1.SetLineColor(1)	
	hist1.SetLineColor(1)

	# c0.SetLogy()

	hist1.Draw()

	# c0.SetGrid()
	
	c0.SaveAs(fname+".png")
	c0.SaveAs(fname+".pdf")

# Get file

dataset="EG";

nGauss = "singleGauss"
dataset = "EG"

fname = "../../plots/plotsEpTimeCalo_"+nGauss+"_"+dataset+".root";


