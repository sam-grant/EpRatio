void S18_chiSquareSlices_SingleGaus_HK()
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
   1.438213,
   1.354312,
   1.51971,
   1.141223,
   1.403874,
   1.399571,
   1.172914,
   1.14904,
   1.485755,
   1.248389,
   1.515551,
   1.322132,
   1.19541,
   1.101576,
   1.060284,
   1.416943,
   1.143994,
   1.242746,
   1.400486,
   1.054184,
   1.102218,
   1.447291,
   1.067472,
   1.206117,
   1.090014,
   1.08989,
   1.240293,
   1.126437,
   1.020732,
   0.9774529,
   0.8969911,
   0.9431654,
   1.015219,
   1.163114,
   1.107452,
   1.216543,
   0.8977166,
   1.078459,
   1.173997,
   1.14772,
   1.076299,
   1.065297,
   1.030703,
   1.05059,
   1.149919,
   1.007158,
   0.7754022,
   1.06951,
   1.080082};
   TGraph *graph = new TGraph(49,Graph0_fx2,Graph0_fy2);
   graph->SetName("Graph0");
   graph->SetTitle("HK, station 18;E/p time slices;#chi^{2}/NDF");
   graph->SetFillStyle(1000);
   graph->SetMarkerStyle(20);
   
   TH1F *Graph_Graph2 = new TH1F("Graph_Graph2","HK, station 18",100,0,53.8);
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
