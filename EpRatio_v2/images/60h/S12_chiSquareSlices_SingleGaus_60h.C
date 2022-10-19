void S12_chiSquareSlices_SingleGaus_60h()
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
   1.570567,
   1.754529,
   1.565992,
   1.56196,
   1.640695,
   1.589931,
   1.651366,
   1.394782,
   1.375038,
   1.497115,
   1.44656,
   1.388564,
   1.407856,
   1.474446,
   1.508615,
   1.195838,
   1.36864,
   1.267141,
   1.201934,
   1.184652,
   0.9439151,
   1.24151,
   1.078219,
   1.065329,
   0.8514267,
   1.159112,
   1.12999,
   1.163705,
   0.9356976,
   1.120311,
   1.084731,
   1.062369,
   1.078216,
   1.106287,
   1.042066,
   1.579824,
   1.112059,
   1.079728,
   0.8971541,
   1.029206,
   1.295856,
   0.9951991,
   1.065251,
   0.992694,
   0.881164,
   0.9714122,
   1.028404,
   1.049339,
   0.9436147};
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
