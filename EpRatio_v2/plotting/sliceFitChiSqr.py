# Plot the reduced chi squareds for every double gaussian fit to E/p time slices

from ROOT import TFile, TH1D, TGraph, TF1, TCanvas, TLine
from plotFunc import *
from array import array

def DefineScat(x_,y_):

    x, y = array('f'), array('f') #, array('d'), array('d')
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
    line3 = TLine(0,1.0,49,1.0)
    line1.SetLineStyle(2)
    line2.SetLineStyle(2)
    line3.SetLineStyle(3)
    # line1.SetLineWidth(3)
    # line2.SetLineWidth(3)

    plot.SetTitle(title)
    plot.GetXaxis().SetTitleSize(.04)
    plot.GetYaxis().SetTitleSize(.04)
    plot.GetXaxis().SetTitleOffset(1.1)
    plot.GetYaxis().SetTitleOffset(1.25)
    plot.GetXaxis().CenterTitle(1)
    plot.GetYaxis().CenterTitle(1)
    # plot.GetYaxis().SetRangeUser(0.086,0.106)\
    plot.GetYaxis().SetRangeUser(0.25,1.75)
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
    line3.Draw("SAME")
    # c2.SetGridx()
    c2.SaveAs(fname+".C")
    c2.SaveAs(fname+".pdf")
    return


dataset = raw_input("Enter run-1 dataset: '60h' '9d' 'HK' 'EG'\n")


if(dataset == "60h" or dataset == "9d" or dataset == "HK" or dataset == "EG"):
    print("Starting\n")
else: 
    print("Invalid dataset, stopping")
    exit(0)

fitName = raw_input("Select fit mode: '1' (SingleGaus) '2' (DoubleGaus) '3' (LanGaus)\n")
fitMode = ""

if(fitName == "1"):
    fitMode = "SingleGaus"
    print("Using fitMode: "+fitMode+"\nStarting\n")
elif(fitName == "2"):
    fitMode = "DoubleGaus";
    print("Using fitMode: "+fitMode+"\nStarting\n")
elif(fitName == "3"):
    fitMode = "LanGaus"
    print("Using fitMode: "+fitMode+"\nStarting\n")
else:
    print("Invalid fitmode, stopping")
    exit(0)
    

file = TFile.Open("../plots/"+dataset+"/plotsEpTimeCalo_"+fitMode+"_"+dataset+".root")
print(file)
# Load chi squareds into an array
cycles = 50
# binning = 4.365




for stn in range(12,19,6):

    chiHist = TH1D("name","title",75,0.25,1.75)

    chi_ = []
    time_ = []

    for i in range(1, cycles):
 
        hist = file.Get("GainCorr/S"+str(stn)+"/sliceFits/"+fitMode+"Calo_"+str(i))
        print(hist)

        if(fitName=="1"): 
            fit = hist.GetFunction("gFunc") 
            chi = fit.GetChisquare() / fit.GetNDF()
            chi_.append(chi)
            time_.append(i)
            chiHist.Fill(chi)
        elif(fitName=="3"):
            fit = hist.GetFunction("lgFunc")
            chi = fit.GetChisquare() / fit.GetNDF()
            chi_.append(chi)
            time_.append(i)
            chiHist.Fill(chi)

    print(len(chi_),len(time_))
    gr = DefineScat(time_,chi_)
    gr.GetXaxis().SetRangeUser(0,(cycles-1))

    DrawScat(gr,dataset+", station "+str(stn)+";E/p time slices;#chi^{2}/NDF","../images/"+dataset+"/S"+str(stn)+"_chiSquareSlices_"+fitMode+"_"+dataset)
    FancyDraw1DStatBox(chiHist,dataset+", station "+str(stn)+";#chi^{2}/NDF;Fits","../images/"+dataset+"/S"+str(stn)+"_chiSquareHist_"+fitMode+"_"+dataset)


