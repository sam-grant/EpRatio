void fracUnc()
{
//=========Macro generated from canvas: c/c
//=========  (Wed Jul  8 21:30:09 2020) by ROOT version 6.12/04
   TCanvas *c = new TCanvas("c", "c",0,0,800,600);
   gStyle->SetOptFit(1);
   c->SetHighLightColor(2);
   c->Range(-2.875,-21.26817,25.875,5.179289);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetFrameBorderMode(0);
   c->SetFrameBorderMode(0);
   
   Double_t Graph0_fx1007[21] = {
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
   21};
   Double_t Graph0_fy1007[21] = {
   0.5825933,
   0.4938967,
   0.06739185,
   0.2857034,
   -0.3137245,
   -0.2406933,
   0.08036658,
   0.2844014,
   -0.5014997,
   0.06318047,
   0.2603204,
   -0.523297,
   -0.2180139,
   0.2531677,
   0.1082596,
   -0.9145945,
   -0.1379005,
   -14.77825,
   -0.04726424,
   0.02373264,
   -10.43437};
   Double_t Graph0_fex1007[21] = {
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
   Double_t Graph0_fey1007[21] = {
   0.1887852,
   0.1884345,
   0.2186247,
   0.1600407,
   0.3347141,
   0.2254275,
   0.4385992,
   0.2265752,
   0.2671196,
   0.1685753,
   0.2103289,
   0.5602997,
   0.2508773,
   0.1472127,
   0.20458,
   0.8903632,
   0.3049587,
   2.082015,
   0.3427929,
   0.4060641,
   2.632443};
   TGraphErrors *gre = new TGraphErrors(21,Graph0_fx1007,Graph0_fy1007,Graph0_fex1007,Graph0_fey1007);
   gre->SetName("Graph0");
   gre->SetTitle(";Fit number;#Delta#alpha/#alpha");
   gre->SetFillStyle(1000);
   gre->SetMarkerStyle(20);
   
   TH1F *Graph_Graph1007 = new TH1F("Graph_Graph1007","",100,0,23);
   Graph_Graph1007->SetMinimum(-18.62343);
   Graph_Graph1007->SetMaximum(2.534542);
   Graph_Graph1007->SetDirectory(0);
   Graph_Graph1007->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Graph_Graph1007->SetLineColor(ci);
   Graph_Graph1007->GetXaxis()->SetTitle("Fit number");
   Graph_Graph1007->GetXaxis()->CenterTitle(true);
   Graph_Graph1007->GetXaxis()->SetLabelFont(42);
   Graph_Graph1007->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph1007->GetXaxis()->SetTitleOffset(1.2);
   Graph_Graph1007->GetXaxis()->SetTitleFont(42);
   Graph_Graph1007->GetYaxis()->SetTitle("#Delta#alpha/#alpha");
   Graph_Graph1007->GetYaxis()->CenterTitle(true);
   Graph_Graph1007->GetYaxis()->SetNdivisions(4000510);
   Graph_Graph1007->GetYaxis()->SetLabelFont(42);
   Graph_Graph1007->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph1007->GetYaxis()->SetTitleOffset(1.25);
   Graph_Graph1007->GetYaxis()->SetTitleFont(42);
   Graph_Graph1007->GetZaxis()->SetLabelFont(42);
   Graph_Graph1007->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph1007->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph1007->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph1007);
   
   
   TF1 *lineFit1008 = new TF1("lineFit","pol 0",0,23, TF1::EAddToList::kNo);
   lineFit1008->SetFillColor(19);
   lineFit1008->SetFillStyle(0);
   lineFit1008->SetLineColor(2);
   lineFit1008->SetLineWidth(3);
   lineFit1008->SetChisquare(95.40922);
   lineFit1008->SetNDF(20);
   lineFit1008->GetXaxis()->SetLabelFont(42);
   lineFit1008->GetXaxis()->SetLabelSize(0.035);
   lineFit1008->GetXaxis()->SetTitleSize(0.035);
   lineFit1008->GetXaxis()->SetTitleFont(42);
   lineFit1008->GetYaxis()->SetLabelFont(42);
   lineFit1008->GetYaxis()->SetLabelSize(0.035);
   lineFit1008->GetYaxis()->SetTitleSize(0.035);
   lineFit1008->GetYaxis()->SetTitleOffset(0);
   lineFit1008->GetYaxis()->SetTitleFont(42);
   lineFit1008->SetParameter(0,0.1221472);
   lineFit1008->SetParError(0,0.05289959);
   lineFit1008->SetParLimits(0,0,0);
   lineFit1008->SetParent(gre);
   gre->GetListOfFunctions()->Add(lineFit1008);
   
   TPaveStats *ptstats = new TPaveStats(0.62,0.855,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *ptstats_LaTex = ptstats->AddText("#chi^{2} / ndf = 95.41 / 20");
   ptstats_LaTex = ptstats->AddText("p0       = 0.1221 #pm 0.0529 ");
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
