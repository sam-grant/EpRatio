void S18_chiSquareSlices_SingleGaus_60h()
{
//=========Macro generated from canvas: c2/
//=========  (Thu May 14 19:50:18 2020) by ROOT version 6.12/04
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
   1.335704,
   1.561066,
   1.489855,
   1.232242,
   1.335769,
   1.342944,
   1.234695,
   1.274536,
   1.228115,
   1.223488,
   1.474239,
   1.187185,
   1.422739,
   1.115448,
   1.116332,
   1.223335,
   1.075619,
   1.348004,
   1.018826,
   1.198967,
   1.29414,
   1.262283,
   0.9363139,
   1.302109,
   0.9677359,
   1.081323,
   1.268644,
   1.614408,
   0.8990151,
   1.136999,
   1.014317,
   1.182443,
   0.9699081,
   1.159376,
   1.029645,
   0.994394,
   0.9861032,
   1.239729,
   1.015999,
   0.9413642,
   1.091616,
   1.573757,
   1.022987,
   1.208176,
   1.2316,
   1.152986,
   0.8877622,
   1.026621,
   1.277756};
   TGraph *graph = new TGraph(49,Graph0_fx2,Graph0_fy2);
   graph->SetName("Graph0");
   graph->SetTitle("60h, station 18;E/p time slices;#chi^{2}/NDF");
   graph->SetFillStyle(1000);
   graph->SetMarkerStyle(20);
   
   TH1F *Graph_Graph2 = new TH1F("Graph_Graph2","60h, station 18",100,0,53.8);
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
