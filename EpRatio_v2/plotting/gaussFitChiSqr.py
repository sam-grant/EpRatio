# Plot the reduced chi squareds for every double gaussian fit to E/p time slices

from ROOT import TFile, TH1D, TGraph, TF1, TCanvas, TLine
from array import array

def DefineScat(x_,y_):

        x, y = array('f'), array('f')
        n = 0
        n = len(y_)
        if(n==0):
                return

        print("n :"+str(n))
        for i in range(0,n):

#               frac = wrong_[i].GetEntries() / all_[i].GetEntries()
                # print(i)
                # print(x_[i])
                x.append(x_[i])

                #print(y_[i])
                y.append(y_[i])


                # print(str(DCAs_[i])+" * "+str(y_)+" * "+str(wrong_[i].GetEntries())+" * "+str(all_[i].GetEntries()))

        return TGraph(n,x,y)


def DrawScat(plot, title, fname):

    c2 = TCanvas("c2","",800,600)

    # Draw some boundary lines for acceptable chiSqr
    # line1 = TLine(0,1.5,4.2*50,1.5)
    # line2 = TLine(0,0.5,4.2*50,0.5)
    line1 = TLine(0,1.5,49,1.5)
    line2 = TLine(0,0.5,49,0.5)
    line1.SetLineStyle(3)
    line2.SetLineStyle(3)


    plot.SetTitle(title)
    plot.GetXaxis().SetTitleSize(.04)
    plot.GetYaxis().SetTitleSize(.04)
    plot.GetXaxis().SetTitleOffset(1.1)
    plot.GetYaxis().SetTitleOffset(1.25)
    plot.GetXaxis().CenterTitle(1)
    plot.GetYaxis().CenterTitle(1)
    # plot.GetYaxis().SetRangeUser(0.086,0.106)\
    # plot.GetYaxis().SetRangeUser(0.5,0.7)
    # plot.GetXaxis().SetRangeUser(-5,2500)
    plot.GetYaxis().SetMaxDigits(4)
    #plot.SetMarkerSize(3)
    #plot.SetLineWidth(3)
    plot.SetMarkerStyle(20) # Full circle
    #plot.SetMarkerColor(4)
    #plot.SetLineColor(4)
    plot.Draw("AP")
    plot.SetMinimum(0.25)
    line1.Draw("SAME")
    line2.Draw("SAME")
    c2.SetGridx()
    c2.SaveAs(fname+".C")
    c2.SaveAs(fname+".pdf")
    return

#
## Get file
dataset = "EG" #input("Enter run-1 dataset: 60h 9d EG:\n")
doubleGauss = True;
nGauss = "singleGauss"
if(doubleGauss): nGauss = "doubleGauss"

nGauss = "LanGaus"
#
#if(dataset == "60h" or dataset == "9d" or dataset == "EG"):
#	print("Using {dataset}")
#else:
#	print("Invalid dataset")

file = TFile.Open("../../plots/plotsEpTimeCalo_"+nGauss+"_"+dataset+".root")
print(file)
# Load chi squareds into an array
cycles = 50
binning = 4.2

for stn in range(12,19,6):
	
	chi_ = []
	time_ = []

	for i in range(cycles):

        hist = file.Get("GainCorr/S"+str(stn)+"/fitSlices/LandCalo_"+str(i))

		# Get hists
		#hist = file.Get("GainCorr/S"+str(stn)+"/gauss/GaussCalo_"+str(i))

		
		#if(doubleGauss==False): fit = hist.GetFunction("gFunc1") # Single gaussian fit (should be gFunc2)
		#elif(doubleGauss==True): fit = hist.GetFunction("gFunc2")# fit = hist.GetFunction("gFunc3") # Double gaussian fit (should be gFunc2)
        fit = hist.GetFunction("lgFunc")
		chi_.append(fit.GetChisquare() / fit.GetNDF())
		# time_.append(i*binning)
		time_.append(i)

	print(len(chi_),len(time_))
	gr = DefineScat(time_,chi_)
	# gr.GetXaxis().SetRangeUser(0,binning*cycles)
	gr.GetXaxis().SetRangeUser(0,cycles-1)

	#DrawScat(gr,";Time slice [#mus];#chi^{2}/NDF","../../images/S"+str(stn)+"_chiSquareSlices_"+dataset)
	DrawScat(gr,";Slice number;#chi^{2}/NDF","../../images/S"+str(stn)+"_chiSquareSlices_"+nGauss+"_"+dataset)



