void pulls_EG()
{
//=========Macro generated from canvas: c/c
//=========  (Wed Jul  8 22:14:51 2020) by ROOT version 6.12/04
   TCanvas *c = new TCanvas("c", "c",0,0,800,600);
   c->SetHighLightColor(2);
   c->Range(0,0,1,1);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetFrameBorderMode(0);
   
   TH1D *__4 = new TH1D("__4","",20,-5,5);
   __4->SetBinContent(6,1);
   __4->SetBinContent(7,1);
   __4->SetBinContent(9,6);
   __4->SetBinContent(10,5);
   __4->SetBinContent(11,5);
   __4->SetBinContent(12,1);
   __4->SetBinContent(13,2);
   __4->SetBinContent(15,1);
   __4->SetBinContent(17,1);
   __4->SetBinContent(18,1);
   __4->SetEntries(24);
   __4->SetStats(0);
   __4->SetLineWidth(3);
   __4->GetXaxis()->SetTitle("Pull [#sigma]");
   __4->GetXaxis()->CenterTitle(true);
   __4->GetXaxis()->SetLabelFont(42);
   __4->GetXaxis()->SetLabelSize(0.035);
   __4->GetXaxis()->SetTitleOffset(1.1);
   __4->GetXaxis()->SetTitleFont(42);
   __4->GetYaxis()->SetTitle("Fits");
   __4->GetYaxis()->CenterTitle(true);
   __4->GetYaxis()->SetNdivisions(4000510);
   __4->GetYaxis()->SetLabelFont(42);
   __4->GetYaxis()->SetLabelSize(0.035);
   __4->GetYaxis()->SetTitleOffset(1.1);
   __4->GetYaxis()->SetTitleFont(42);
   __4->GetZaxis()->SetLabelFont(42);
   __4->GetZaxis()->SetLabelSize(0.035);
   __4->GetZaxis()->SetTitleSize(0.035);
   __4->GetZaxis()->SetTitleFont(42);
   __4->Draw("HIST");
   
   TPaveText *pt = new TPaveText(0,0,0,0,"brNDC");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetTextFont(44);
   pt->SetTextSize(26);
   TText *pt_LaTex = pt->AddText("#splitline{Mean = 0.1#pm0.3 #sigma}{StdDev = 1.4 #sigma}");
   pt->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
