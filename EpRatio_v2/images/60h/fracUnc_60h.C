void fracUnc_60h()
{
//=========Macro generated from canvas: c/c
//=========  (Thu Jul  9 08:53:05 2020) by ROOT version 6.12/04
   TCanvas *c = new TCanvas("c", "c",0,0,800,600);
   gStyle->SetOptFit(1);
   c->SetHighLightColor(2);
   c->Range(-2.05,-1.452666,18.45,1.185474);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetFrameBorderMode(0);
   c->SetFrameBorderMode(0);
   
   Double_t Graph0_fx1001[15] = {
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
   15};
   Double_t Graph0_fy1001[15] = {
   -0.3341088,
   0.1350009,
   0.2789022,
   -0.4123366,
   -0.1123425,
   0.1713884,
   -0.02476365,
   -0.09724887,
   0.6131369,
   -0.06274368,
   0.3626272,
   -0.06847755,
   0.3879281,
   -0.03939073,
   0.03469971};
   Double_t Graph0_fex1001[15] = {
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
   Double_t Graph0_fey1001[15] = {
   0.5307698,
   0.2749912,
   0.2594404,
   0.6006392,
   0.3238817,
   0.2715179,
   0.4510953,
   0.25684,
   0.1326474,
   0.419237,
   0.09947542,
   0.4317607,
   0.2055142,
   0.4854237,
   0.4305658};
   TGraphErrors *gre = new TGraphErrors(15,Graph0_fx1001,Graph0_fy1001,Graph0_fex1001,Graph0_fey1001);
   gre->SetName("Graph0");
   gre->SetTitle(";Fit number;#Delta#alpha/#alpha");
   gre->SetFillStyle(1000);
   gre->SetMarkerStyle(20);
   
   TH1F *Graph_Graph1001 = new TH1F("Graph_Graph1001","",100,0,16.4);
   Graph_Graph1001->SetMinimum(-1.188852);
   Graph_Graph1001->SetMaximum(0.9216603);
   Graph_Graph1001->SetDirectory(0);
   Graph_Graph1001->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Graph_Graph1001->SetLineColor(ci);
   Graph_Graph1001->GetXaxis()->SetTitle("Fit number");
   Graph_Graph1001->GetXaxis()->CenterTitle(true);
   Graph_Graph1001->GetXaxis()->SetLabelFont(42);
   Graph_Graph1001->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph1001->GetXaxis()->SetTitleOffset(1.2);
   Graph_Graph1001->GetXaxis()->SetTitleFont(42);
   Graph_Graph1001->GetYaxis()->SetTitle("#Delta#alpha/#alpha");
   Graph_Graph1001->GetYaxis()->CenterTitle(true);
   Graph_Graph1001->GetYaxis()->SetNdivisions(4000510);
   Graph_Graph1001->GetYaxis()->SetLabelFont(42);
   Graph_Graph1001->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph1001->GetYaxis()->SetTitleOffset(1.25);
   Graph_Graph1001->GetYaxis()->SetTitleFont(42);
   Graph_Graph1001->GetZaxis()->SetLabelFont(42);
   Graph_Graph1001->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph1001->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph1001->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph1001);
   
   
   TF1 *lineFit1002 = new TF1("lineFit","pol 0",0,16.4, TF1::EAddToList::kNo);
   lineFit1002->SetFillColor(19);
   lineFit1002->SetFillStyle(0);
   lineFit1002->SetLineColor(2);
   lineFit1002->SetLineWidth(3);
   lineFit1002->SetChisquare(16.45203);
   lineFit1002->SetNDF(14);
   lineFit1002->GetXaxis()->SetLabelFont(42);
   lineFit1002->GetXaxis()->SetLabelSize(0.035);
   lineFit1002->GetXaxis()->SetTitleSize(0.035);
   lineFit1002->GetXaxis()->SetTitleFont(42);
   lineFit1002->GetYaxis()->SetLabelFont(42);
   lineFit1002->GetYaxis()->SetLabelSize(0.035);
   lineFit1002->GetYaxis()->SetTitleSize(0.035);
   lineFit1002->GetYaxis()->SetTitleOffset(0);
   lineFit1002->GetYaxis()->SetTitleFont(42);
   lineFit1002->SetParameter(0,0.297432);
   lineFit1002->SetParError(0,0.05977934);
   lineFit1002->SetParLimits(0,0,0);
   lineFit1002->SetParent(gre);
   gre->GetListOfFunctions()->Add(lineFit1002);
   
   TPaveStats *ptstats = new TPaveStats(0.62,0.855,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *ptstats_LaTex = ptstats->AddText("#chi^{2} / ndf = 16.45 / 14");
   ptstats_LaTex = ptstats->AddText("p0       = 0.2974 #pm 0.05978 ");
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
