void fracUnc_EG()
{
//=========Macro generated from canvas: c/c
//=========  (Thu Jul  9 08:53:05 2020) by ROOT version 6.12/04
   TCanvas *c = new TCanvas("c", "c",0,0,800,600);
   gStyle->SetOptFit(1);
   c->SetHighLightColor(2);
   c->Range(-3.2875,-1.587888,29.5875,1.104558);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetFrameBorderMode(0);
   c->SetFrameBorderMode(0);
   
   Double_t Graph0_fx1010[24] = {
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
   16,
   17,
   18,
   19,
   20,
   21,
   22,
   23,
   24};
   Double_t Graph0_fy1010[24] = {
   0.008724514,
   -0.1030379,
   -0.1321128,
   0.1699143,
   0.1635017,
   -0.5489909,
   0.4787655,
   0.5234705,
   -0.4514602,
   -0.05680201,
   -0.1885667,
   -0.1780935,
   0.05107641,
   0.3253298,
   0.1576834,
   0.05441914,
   0.3341953,
   -0.1345175,
   -0.2926497,
   -0.446594,
   -0.4885583,
   -0.2268092,
   -0.4729183,
   0.04439034};
   Double_t Graph0_fex1010[24] = {
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
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph0_fey1010[24] = {
   0.2780304,
   0.2549122,
   0.3000654,
   0.3557735,
   0.1616222,
   0.2429593,
   0.138989,
   0.1323464,
   0.3004521,
   0.1804572,
   0.3294598,
   0.2008688,
   0.2006676,
   0.1464029,
   0.1743187,
   0.2758255,
   0.2257861,
   0.2931981,
   0.5084214,
   0.6162199,
   0.6505891,
   0.4616772,
   0.5151649,
   0.4407893};
   TGraphErrors *gre = new TGraphErrors(24,Graph0_fx1010,Graph0_fy1010,Graph0_fex1010,Graph0_fey1010);
   gre->SetName("Graph0");
   gre->SetTitle(";Fit number;#Delta#alpha/#alpha");
   gre->SetFillStyle(1000);
   gre->SetMarkerStyle(20);
   
   TH1F *Graph_Graph1010 = new TH1F("Graph_Graph1010","",100,0,26.3);
   Graph_Graph1010->SetMinimum(-1.318644);
   Graph_Graph1010->SetMaximum(0.8353133);
   Graph_Graph1010->SetDirectory(0);
   Graph_Graph1010->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Graph_Graph1010->SetLineColor(ci);
   Graph_Graph1010->GetXaxis()->SetTitle("Fit number");
   Graph_Graph1010->GetXaxis()->CenterTitle(true);
   Graph_Graph1010->GetXaxis()->SetLabelFont(42);
   Graph_Graph1010->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph1010->GetXaxis()->SetTitleOffset(1.2);
   Graph_Graph1010->GetXaxis()->SetTitleFont(42);
   Graph_Graph1010->GetYaxis()->SetTitle("#Delta#alpha/#alpha");
   Graph_Graph1010->GetYaxis()->CenterTitle(true);
   Graph_Graph1010->GetYaxis()->SetNdivisions(4000510);
   Graph_Graph1010->GetYaxis()->SetLabelFont(42);
   Graph_Graph1010->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph1010->GetYaxis()->SetTitleOffset(1.25);
   Graph_Graph1010->GetYaxis()->SetTitleFont(42);
   Graph_Graph1010->GetZaxis()->SetLabelFont(42);
   Graph_Graph1010->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph1010->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph1010->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph1010);
   
   
   TF1 *lineFit1011 = new TF1("lineFit","pol 0",0,26.3, TF1::EAddToList::kNo);
   lineFit1011->SetFillColor(19);
   lineFit1011->SetFillStyle(0);
   lineFit1011->SetLineColor(2);
   lineFit1011->SetLineWidth(3);
   lineFit1011->SetChisquare(41.03371);
   lineFit1011->SetNDF(23);
   lineFit1011->GetXaxis()->SetLabelFont(42);
   lineFit1011->GetXaxis()->SetLabelSize(0.035);
   lineFit1011->GetXaxis()->SetTitleSize(0.035);
   lineFit1011->GetXaxis()->SetTitleFont(42);
   lineFit1011->GetYaxis()->SetLabelFont(42);
   lineFit1011->GetYaxis()->SetLabelSize(0.035);
   lineFit1011->GetYaxis()->SetTitleSize(0.035);
   lineFit1011->GetYaxis()->SetTitleOffset(0);
   lineFit1011->GetYaxis()->SetTitleFont(42);
   lineFit1011->SetParameter(0,0.127375);
   lineFit1011->SetParError(0,0.04670362);
   lineFit1011->SetParLimits(0,0,0);
   lineFit1011->SetParent(gre);
   gre->GetListOfFunctions()->Add(lineFit1011);
   
   TPaveStats *ptstats = new TPaveStats(0.62,0.855,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *ptstats_LaTex = ptstats->AddText("#chi^{2} / ndf = 41.03 / 23");
   ptstats_LaTex = ptstats->AddText("p0       = 0.1274 #pm 0.0467 ");
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
