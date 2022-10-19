void S18_chiSquareHist_LanGaus_HK()
{
//=========Macro generated from canvas: c/c
//=========  (Thu May 14 19:48:49 2020) by ROOT version 6.12/04
   TCanvas *c = new TCanvas("c", "c",0,0,800,600);
   c->SetHighLightColor(2);
   c->Range(0.06249999,-0.9187501,1.9375,8.26875);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetFrameBorderMode(0);
   
   TH1D *name__2 = new TH1D("name__2","HK, station 18",75,0.25,1.75);
   name__2->SetBinContent(25,1);
   name__2->SetBinContent(29,1);
   name__2->SetBinContent(31,1);
   name__2->SetBinContent(32,1);
   name__2->SetBinContent(33,3);
   name__2->SetBinContent(34,3);
   name__2->SetBinContent(35,7);
   name__2->SetBinContent(36,3);
   name__2->SetBinContent(37,4);
   name__2->SetBinContent(39,5);
   name__2->SetBinContent(40,4);
   name__2->SetBinContent(41,3);
   name__2->SetBinContent(42,4);
   name__2->SetBinContent(43,3);
   name__2->SetBinContent(44,1);
   name__2->SetBinContent(45,1);
   name__2->SetBinContent(46,1);
   name__2->SetBinContent(47,1);
   name__2->SetBinContent(49,1);
   name__2->SetBinContent(54,1);
   name__2->SetEntries(49);
   
   TPaveStats *ptstats = new TPaveStats(0.11,0.69,0.49,0.89,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetLineWidth(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *ptstats_LaTex = ptstats->AddText("Mean  =   1.01 #pm 0.0149");
   ptstats_LaTex = ptstats->AddText("Std Dev   =  0.104 #pm 0.0105");
   ptstats_LaTex = ptstats->AddText("Underflow =      0");
   ptstats_LaTex = ptstats->AddText("Overflow  =      0");
   ptstats->SetOptStat(112200);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   name__2->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(name__2);
   name__2->SetLineWidth(3);
   name__2->GetXaxis()->SetTitle("#chi^{2}/NDF");
   name__2->GetXaxis()->CenterTitle(true);
   name__2->GetXaxis()->SetLabelFont(42);
   name__2->GetXaxis()->SetLabelSize(0.035);
   name__2->GetXaxis()->SetTitleOffset(1.1);
   name__2->GetXaxis()->SetTitleFont(42);
   name__2->GetYaxis()->SetTitle("Fits");
   name__2->GetYaxis()->CenterTitle(true);
   name__2->GetYaxis()->SetNdivisions(4000510);
   name__2->GetYaxis()->SetLabelFont(42);
   name__2->GetYaxis()->SetLabelSize(0.035);
   name__2->GetYaxis()->SetTitleOffset(1.1);
   name__2->GetYaxis()->SetTitleFont(42);
   name__2->GetZaxis()->SetLabelFont(42);
   name__2->GetZaxis()->SetLabelSize(0.035);
   name__2->GetZaxis()->SetTitleSize(0.035);
   name__2->GetZaxis()->SetTitleFont(42);
   name__2->Draw("");
   
   ptstats = new TPaveStats(0.11,0.69,0.49,0.89,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetLineWidth(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   ptstats_LaTex = ptstats->AddText("Mean  =   1.01 #pm 0.0149");
   ptstats_LaTex = ptstats->AddText("Std Dev   =  0.104 #pm 0.0105");
   ptstats_LaTex = ptstats->AddText("Underflow =      0");
   ptstats_LaTex = ptstats->AddText("Overflow  =      0");
   ptstats->SetOptStat(112200);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
