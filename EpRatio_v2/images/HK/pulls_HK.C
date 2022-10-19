void pulls_HK()
{
//=========Macro generated from canvas: c/c
//=========  (Thu Jul 30 08:09:19 2020) by ROOT version 6.12/04
   TCanvas *c = new TCanvas("c", "c",0,0,800,600);
   c->SetHighLightColor(2);
   c->Range(0,0,1,1);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetFrameBorderMode(0);
   
   TH1D *__2 = new TH1D("__2","",20,-5,5);
   __2->SetBinContent(8,1);
   __2->SetBinContent(9,2);
   __2->SetBinContent(10,5);
   __2->SetBinContent(11,5);
   __2->SetBinContent(13,1);
   __2->SetBinContent(14,2);
   __2->SetEntries(16);
   __2->SetStats(0);
   __2->SetLineWidth(3);
   __2->GetXaxis()->SetTitle("Pull [#sigma]");
   __2->GetXaxis()->CenterTitle(true);
   __2->GetXaxis()->SetLabelFont(42);
   __2->GetXaxis()->SetLabelSize(0.035);
   __2->GetXaxis()->SetTitleOffset(1.1);
   __2->GetXaxis()->SetTitleFont(42);
   __2->GetYaxis()->SetTitle("Fits");
   __2->GetYaxis()->CenterTitle(true);
   __2->GetYaxis()->SetNdivisions(4000510);
   __2->GetYaxis()->SetLabelFont(42);
   __2->GetYaxis()->SetLabelSize(0.035);
   __2->GetYaxis()->SetTitleOffset(1.1);
   __2->GetYaxis()->SetTitleFont(42);
   __2->GetZaxis()->SetLabelFont(42);
   __2->GetZaxis()->SetLabelSize(0.035);
   __2->GetZaxis()->SetTitleSize(0.035);
   __2->GetZaxis()->SetTitleFont(42);
   __2->Draw("HIST");
   
   TPaveText *pt = new TPaveText(0,0,0,0,"brNDC");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetTextFont(44);
   pt->SetTextSize(26);
   TText *pt_LaTex = pt->AddText("#splitline{Mean = 0.1#pm0.2#sigma}{Width = 0.836#sigma}");
   pt->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
