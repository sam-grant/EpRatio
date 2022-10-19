void S12_chiSquareSlices_SingleGaus_9d()
{
//=========Macro generated from canvas: c2/
//=========  (Thu May 14 19:50:03 2020) by ROOT version 6.12/04
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
   1.813808,
   2.414247,
   2.455369,
   2.101313,
   2.688216,
   2.076064,
   2.461293,
   1.840041,
   1.5613,
   1.386321,
   1.645405,
   1.85329,
   1.541661,
   1.866638,
   1.598614,
   1.772526,
   1.276489,
   1.369341,
   1.285769,
   1.355934,
   1.372126,
   1.380044,
   1.242941,
   1.298259,
   1.187494,
   1.460803,
   1.355101,
   1.18415,
   1.40945,
   1.213192,
   0.9424534,
   1.276149,
   1.222031,
   1.326038,
   0.989758,
   1.127739,
   1.325638,
   1.138553,
   1.428783,
   1.088243,
   1.230006,
   1.17221,
   1.209165,
   0.9997376,
   1.002324,
   1.121904,
   1.070239,
   1.090477,
   1.062147};
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
