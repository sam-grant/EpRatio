void S12_chiSquareSlices_SingleGaus_HK()
{
//=========Macro generated from canvas: c2/
//=========  (Thu May 14 19:49:49 2020) by ROOT version 6.12/04
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
   1.356884,
   1.827325,
   1.922984,
   1.88846,
   2.061393,
   1.746035,
   1.628101,
   1.788343,
   1.370026,
   1.320189,
   1.52995,
   1.150764,
   1.59519,
   1.762909,
   1.561823,
   1.129093,
   1.38,
   1.310211,
   1.257436,
   1.362942,
   1.096992,
   1.498785,
   1.387253,
   1.299729,
   1.218492,
   1.260791,
   1.105903,
   1.208735,
   0.9666529,
   1.04992,
   1.102872,
   0.9801391,
   1.09705,
   1.167006,
   0.8982622,
   0.9187807,
   1.16779,
   1.180639,
   0.8601147,
   1.075687,
   1.241598,
   1.086112,
   1.189204,
   1.036317,
   0.8978367,
   1.063674,
   0.7667532,
   1.259131,
   1.067373};
   TGraph *graph = new TGraph(49,Graph0_fx1,Graph0_fy1);
   graph->SetName("Graph0");
   graph->SetTitle("HK, station 12;E/p time slices;#chi^{2}/NDF");
   graph->SetFillStyle(1000);
   graph->SetMarkerStyle(20);
   
   TH1F *Graph_Graph1 = new TH1F("Graph_Graph1","HK, station 12",100,0,53.8);
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
