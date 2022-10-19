void pulls()
{
//=========Macro generated from canvas: c/c
//=========  (Wed Jul  8 22:13:53 2020) by ROOT version 6.12/04
   TCanvas *c = new TCanvas("c", "c",0,0,800,600);
   c->SetHighLightColor(2);
   c->Range(0,0,1,1);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetFrameBorderMode(0);
   
   TH1D *__3 = new TH1D("__3","",20,-5,5);
   __3->SetBinContent(0,1);
   __3->SetBinContent(2,1);
   __3->SetBinContent(7,1);
   __3->SetBinContent(8,2);
   __3->SetBinContent(9,3);
   __3->SetBinContent(10,2);
   __3->SetBinContent(11,4);
   __3->SetBinContent(12,1);
   __3->SetBinContent(13,2);
   __3->SetBinContent(14,2);
   __3->SetBinContent(16,2);
   __3->SetEntries(21);
   __3->SetStats(0);
   __3->SetLineWidth(3);
   __3->GetXaxis()->SetTitle("Pull [#sigma]");
   __3->GetXaxis()->CenterTitle(true);
   __3->GetXaxis()->SetLabelFont(42);
   __3->GetXaxis()->SetLabelSize(0.035);
   __3->GetXaxis()->SetTitleOffset(1.1);
   __3->GetXaxis()->SetTitleFont(42);
   __3->GetYaxis()->SetTitle("Fits");
   __3->GetYaxis()->CenterTitle(true);
   __3->GetYaxis()->SetNdivisions(4000510);
   __3->GetYaxis()->SetLabelFont(42);
   __3->GetYaxis()->SetLabelSize(0.035);
   __3->GetYaxis()->SetTitleOffset(1.1);
   __3->GetYaxis()->SetTitleFont(42);
   __3->GetZaxis()->SetLabelFont(42);
   __3->GetZaxis()->SetLabelSize(0.035);
   __3->GetZaxis()->SetTitleSize(0.035);
   __3->GetZaxis()->SetTitleFont(42);
   __3->Draw("HIST");
   
   TPaveText *pt = new TPaveText(0,0,0,0,"brNDC");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetTextFont(44);
   pt->SetTextSize(26);
   TText *pt_LaTex = pt->AddText("#splitline{Mean = 0.06#pm0.4 #sigma}{StdDev = 1.59 #sigma}");
   pt->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
