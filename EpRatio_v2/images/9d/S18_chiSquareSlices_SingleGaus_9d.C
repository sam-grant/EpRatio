void S18_chiSquareSlices_SingleGaus_9d()
{
//=========Macro generated from canvas: c2/
//=========  (Thu May 14 19:50:04 2020) by ROOT version 6.12/04
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
   2.212083,
   1.729609,
   1.452048,
   1.785697,
   1.919996,
   1.529354,
   1.649238,
   1.532117,
   1.65192,
   1.486789,
   1.603847,
   1.478042,
   1.997053,
   1.477497,
   1.59237,
   1.532428,
   1.187457,
   1.258391,
   1.114595,
   1.398881,
   1.360383,
   1.343493,
   0.9406373,
   1.479997,
   1.309577,
   1.131536,
   1.04888,
   1.184058,
   1.368555,
   1.182954,
   1.367427,
   1.098496,
   1.292261,
   0.9814627,
   0.8828465,
   1.101883,
   1.008589,
   1.057394,
   1.142346,
   1.404127,
   1.16974,
   1.011584,
   1.101616,
   1.252337,
   1.270739,
   0.9767639,
   0.9652013,
   1.170927,
   1.084217};
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
