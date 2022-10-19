void S12_chiSquareSlices_LanGaus_60h()
{
//=========Macro generated from canvas: c2/
//=========  (Thu May 14 19:50:11 2020) by ROOT version 6.12/04
   TCanvas *c2 = new TCanvas("c2", "",0,0,800,600);
   c2->SetHighLightColor(2);
   c2->Range(0,0,1,1);
   c2->SetFillColor(0);
   c2->SetBorderMode(0);
   c2->SetBorderSize(2);
   c2->SetFrameBorderMode(0);
   
   Double_t Graph0_fx1[49] = {
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
   24,
   25,
   26,
   27,
   28,
   29,
   30,
   31,
   32,
   33,
   34,
   35,
   36,
   37,
   38,
   39,
   40,
   41,
   42,
   43,
   44,
   45,
   46,
   47,
   48,
   49};
   Double_t Graph0_fy1[49] = {
   0.9993375,
   1.136308,
   1.239972,
   1.008788,
   0.9974267,
   1.128102,
   1.101477,
   0.8719737,
   0.9704103,
   0.9622454,
   1.108676,
   1.011699,
   1.11735,
   1.173125,
   1.147296,
   0.9898286,
   1.031669,
   1.015917,
   0.9734714,
   1.002556,
   0.7953348,
   0.909826,
   0.9450411,
   0.9224756,
   0.8092571,
   1.02494,
   1.084687,
   1.127176,
   0.8744725,
   0.9499165,
   1.024042,
   0.8939661,
   1.004096,
   1.028715,
   1.023084,
   1.535244,
   1.081565,
   1.046252,
   0.8430089,
   1.03441,
   1.243966,
   0.9762223,
   1.064995,
   0.9962176,
   0.8404804,
   0.9569082,
   1.014478,
   1.063659,
   0.9312413};
   TGraph *graph = new TGraph(49,Graph0_fx1,Graph0_fy1);
   graph->SetName("Graph0");
   graph->SetTitle("60h, station 12;E/p time slices;#chi^{2}/NDF");
   graph->SetFillStyle(1000);
   graph->SetMarkerStyle(20);
   
   TH1F *Graph_Graph1 = new TH1F("Graph_Graph1","60h, station 12",100,0,53.8);
   Graph_Graph1->SetMinimum(0.25);
   Graph_Graph1->SetMaximum(1.75);
   Graph_Graph1->SetDirectory(0);
   Graph_Graph1->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Graph_Graph1->SetLineColor(ci);
   Graph_Graph1->GetXaxis()->SetTitle("E/p time slices");
   Graph_Graph1->GetXaxis()->SetRange(1,92);
   Graph_Graph1->GetXaxis()->CenterTitle(true);
   Graph_Graph1->GetXaxis()->SetLabelFont(42);
   Graph_Graph1->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph1->GetXaxis()->SetTitleOffset(1.1);
   Graph_Graph1->GetXaxis()->SetTitleFont(42);
   Graph_Graph1->GetYaxis()->SetTitle("#chi^{2}/NDF");
   Graph_Graph1->GetYaxis()->CenterTitle(true);
   Graph_Graph1->GetYaxis()->SetNdivisions(4000510);
   Graph_Graph1->GetYaxis()->SetLabelFont(42);
   Graph_Graph1->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph1->GetYaxis()->SetTitleOffset(1.25);
   Graph_Graph1->GetYaxis()->SetTitleFont(42);
   Graph_Graph1->GetZaxis()->SetLabelFont(42);
   Graph_Graph1->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph1->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph1->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph1);
   
   graph->Draw("ap");
   TLine *line = new TLine(0,1.5,49,1.5);
   line->SetLineStyle(2);
   line->Draw();
   line = new TLine(0,0.5,49,0.5);
   line->SetLineStyle(2);
   line->Draw();
   line = new TLine(0,1,49,1);
   line->SetLineStyle(3);
   line->Draw();
   c2->Modified();
   c2->cd();
   c2->SetSelected(c2);
}
