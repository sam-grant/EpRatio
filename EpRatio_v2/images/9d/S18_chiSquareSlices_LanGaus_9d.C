void S18_chiSquareSlices_LanGaus_9d()
{
//=========Macro generated from canvas: c2/
//=========  (Thu May 14 19:49:56 2020) by ROOT version 6.12/04
   TCanvas *c2 = new TCanvas("c2", "",0,0,800,600);
   c2->SetHighLightColor(2);
   c2->Range(0,0,1,1);
   c2->SetFillColor(0);
   c2->SetBorderMode(0);
   c2->SetBorderSize(2);
   c2->SetFrameBorderMode(0);
   
   Double_t Graph0_fx2[49] = {
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
   Double_t Graph0_fy2[49] = {
   1.283982,
   1.025896,
   0.8718786,
   1.003927,
   1.025104,
   0.8922003,
   1.086405,
   0.9940449,
   0.9372179,
   1.05295,
   1.106957,
   1.090249,
   1.479867,
   0.9353823,
   0.971477,
   0.8888635,
   0.8090155,
   1.102311,
   0.8392511,
   1.017067,
   1.051617,
   1.232704,
   0.8235984,
   1.341395,
   1.23414,
   0.9318299,
   0.8547855,
   1.058673,
   1.213465,
   1.129294,
   1.17427,
   0.9907333,
   1.232272,
   0.9206114,
   0.8480965,
   1.089648,
   0.8975374,
   0.985939,
   1.092172,
   1.292188,
   2.625257,
   1.017174,
   1.02051,
   1.19387,
   1.261002,
   0.9805939,
   0.9005565,
   1.102249,
   1.024037};
   TGraph *graph = new TGraph(49,Graph0_fx2,Graph0_fy2);
   graph->SetName("Graph0");
   graph->SetTitle("9d, station 18;E/p time slices;#chi^{2}/NDF");
   graph->SetFillStyle(1000);
   graph->SetMarkerStyle(20);
   
   TH1F *Graph_Graph2 = new TH1F("Graph_Graph2","9d, station 18",100,0,53.8);
   Graph_Graph2->SetMinimum(0.25);
   Graph_Graph2->SetMaximum(1.75);
   Graph_Graph2->SetDirectory(0);
   Graph_Graph2->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Graph_Graph2->SetLineColor(ci);
   Graph_Graph2->GetXaxis()->SetTitle("E/p time slices");
   Graph_Graph2->GetXaxis()->SetRange(1,92);
   Graph_Graph2->GetXaxis()->CenterTitle(true);
   Graph_Graph2->GetXaxis()->SetLabelFont(42);
   Graph_Graph2->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph2->GetXaxis()->SetTitleOffset(1.1);
   Graph_Graph2->GetXaxis()->SetTitleFont(42);
   Graph_Graph2->GetYaxis()->SetTitle("#chi^{2}/NDF");
   Graph_Graph2->GetYaxis()->CenterTitle(true);
   Graph_Graph2->GetYaxis()->SetNdivisions(4000510);
   Graph_Graph2->GetYaxis()->SetLabelFont(42);
   Graph_Graph2->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph2->GetYaxis()->SetTitleOffset(1.25);
   Graph_Graph2->GetYaxis()->SetTitleFont(42);
   Graph_Graph2->GetZaxis()->SetLabelFont(42);
   Graph_Graph2->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph2->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph2->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph2);
   
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
