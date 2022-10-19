void fracUnc()
{
//=========Macro generated from canvas: c/c
//=========  (Wed Jul  8 21:30:08 2020) by ROOT version 6.12/04
   TCanvas *c = new TCanvas("c", "c",0,0,800,600);
   gStyle->SetOptFit(1);
   c->SetHighLightColor(2);
   c->Range(-2.1875,-1.913279,19.6875,1.180837);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetFrameBorderMode(0);
   c->SetFrameBorderMode(0);
   
   Double_t Graph0_fx1004[16] = {
   1,
   2,
   3,
   4,
   5,
   6,
   7,
   8,
   9,
   10,
   11,
   12,
   13,
   14,
   15,
   16};
   Double_t Graph0_fy1004[16] = {
   0.02226704,
   -0.002038855,
   0.4322261,
   -0.06566691,
   -0.1235344,
   0.1866317,
   -0.5014432,
   0.1047471,
   0.06041796,
   0.09594255,
   -0.1395039,
   0.02537499,
   -0.6560243,
   -0.4210853,
   0.3318973,
   -0.2287857};
   Double_t Graph0_fex1004[16] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph0_fey1004[16] = {
   0.2084804,
   0.2459022,
   0.2329248,
   0.4831555,
   0.3241123,
   0.13658,
   0.494994,
   0.306865,
   0.1831433,
   0.2551167,
   0.3437798,
   0.4356491,
   0.7415686,
   0.4790894,
   0.1815043,
   0.5350822};
   TGraphErrors *gre = new TGraphErrors(16,Graph0_fx1004,Graph0_fy1004,Graph0_fex1004,Graph0_fey1004);
   gre->SetName("Graph0");
   gre->SetTitle(";Fit number;#Delta#alpha/#alpha");
   gre->SetFillStyle(1000);
   gre->SetMarkerStyle(20);
   
   TH1F *Graph_Graph1004 = new TH1F("Graph_Graph1004","",100,0,17.5);
   Graph_Graph1004->SetMinimum(-1.603867);
   Graph_Graph1004->SetMaximum(0.8714253);
   Graph_Graph1004->SetDirectory(0);
   Graph_Graph1004->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Graph_Graph1004->SetLineColor(ci);
   Graph_Graph1004->GetXaxis()->SetTitle("Fit number");
   Graph_Graph1004->GetXaxis()->CenterTitle(true);
   Graph_Graph1004->GetXaxis()->SetLabelFont(42);
   Graph_Graph1004->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph1004->GetXaxis()->SetTitleOffset(1.2);
   Graph_Graph1004->GetXaxis()->SetTitleFont(42);
   Graph_Graph1004->GetYaxis()->SetTitle("#Delta#alpha/#alpha");
   Graph_Graph1004->GetYaxis()->CenterTitle(true);
   Graph_Graph1004->GetYaxis()->SetNdivisions(4000510);
   Graph_Graph1004->GetYaxis()->SetLabelFont(42);
   Graph_Graph1004->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph1004->GetYaxis()->SetTitleOffset(1.25);
   Graph_Graph1004->GetYaxis()->SetTitleFont(42);
   Graph_Graph1004->GetZaxis()->SetLabelFont(42);
   Graph_Graph1004->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph1004->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph1004->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph1004);
   
   
   TF1 *lineFit1005 = new TF1("lineFit","pol 0",0,17.5, TF1::EAddToList::kNo);
   lineFit1005->SetFillColor(19);
   lineFit1005->SetFillStyle(0);
   lineFit1005->SetLineColor(2);
   lineFit1005->SetLineWidth(3);
   lineFit1005->SetChisquare(9.610034);
   lineFit1005->SetNDF(15);
   lineFit1005->GetXaxis()->SetLabelFont(42);
   lineFit1005->GetXaxis()->SetLabelSize(0.035);
   lineFit1005->GetXaxis()->SetTitleSize(0.035);
   lineFit1005->GetXaxis()->SetTitleFont(42);
   lineFit1005->GetYaxis()->SetLabelFont(42);
   lineFit1005->GetYaxis()->SetLabelSize(0.035);
   lineFit1005->GetYaxis()->SetTitleSize(0.035);
   lineFit1005->GetYaxis()->SetTitleOffset(0);
   lineFit1005->GetYaxis()->SetTitleFont(42);
   lineFit1005->SetParameter(0,0.1026504);
   lineFit1005->SetParError(0,0.06468192);
   lineFit1005->SetParLimits(0,0,0);
   lineFit1005->SetParent(gre);
   gre->GetListOfFunctions()->Add(lineFit1005);
   
   TPaveStats *ptstats = new TPaveStats(0.62,0.855,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *ptstats_LaTex = ptstats->AddText("#chi^{2} / ndf =  9.61 / 15");
   ptstats_LaTex = ptstats->AddText("p0       = 0.1027 #pm 0.06468 ");
   ptstats->SetOptStat(0);
   ptstats->SetOptFit(110);
   ptstats->Draw();
   gre->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(gre->GetListOfFunctions());
   gre->Draw("ap");
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
