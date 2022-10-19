void S12_chiSquareSlices_LanGaus_9d()
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
   0.8428837,
   1.020878,
   0.9755023,
   1.072027,
   1.115929,
   1.131064,
   1.076441,
   0.8244262,
   0.9429219,
   0.836935,
   0.9104749,
   0.9754547,
   0.9702098,
   1.1199,
   1.004774,
   1.104929,
   0.8631018,
   0.8752301,
   0.9336668,
   1.106951,
   0.7176471,
   1.1924,
   1.026701,
   1.068939,
   0.9446641,
   1.093795,
   1.075302,
   1.035498,
   1.189572,
   0.8920538,
   0.8435928,
   1.044857,
   1.073509,
   0.9974433,
   0.9539005,
   1.094263,
   1.058535,
   1.052367,
   1.389731,
   1.039206,
   1.166714,
   1.130326,
   1.105246,
   1.001057,
   0.9543999,
   0.9846874,
   1.032163,
   1.004057,
   1.019843};
   TGraph *graph = new TGraph(49,Graph0_fx1,Graph0_fy1);
   graph->SetName("Graph0");
   graph->SetTitle("9d, station 12;E/p time slices;#chi^{2}/NDF");
   graph->SetFillStyle(1000);
   graph->SetMarkerStyle(20);
   
   TH1F *Graph_Graph1 = new TH1F("Graph_Graph1","9d, station 12",100,0,53.8);
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
