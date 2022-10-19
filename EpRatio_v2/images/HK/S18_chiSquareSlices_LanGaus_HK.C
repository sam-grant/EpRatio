void S18_chiSquareSlices_LanGaus_HK()
{
//=========Macro generated from canvas: c2/
//=========  (Thu May 14 19:48:49 2020) by ROOT version 6.12/04
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
   0.9495026,
   0.9699418,
   1.09937,
   0.9363698,
   1.06193,
   0.9763517,
   0.8664153,
   0.9700359,
   0.9442212,
   0.9226872,
   1.076061,
   0.967926,
   1.023803,
   0.918336,
   0.815165,
   1.214105,
   1.019324,
   1.153534,
   1.132385,
   0.9443506,
   0.9031081,
   1.321711,
   0.938132,
   1.185152,
   0.9340141,
   0.9840908,
   1.053935,
   1.104277,
   0.9748476,
   0.9125894,
   0.8781027,
   0.8905786,
   1.013499,
   1.090096,
   1.037781,
   1.079396,
   0.8983539,
   0.958694,
   1.080137,
   1.129346,
   1.040227,
   1.014393,
   1.041772,
   1.02138,
   1.059005,
   0.9389235,
   0.7326361,
   1.047054,
   1.074338};
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
