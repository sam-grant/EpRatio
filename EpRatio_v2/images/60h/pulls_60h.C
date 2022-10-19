void pulls_60h()
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
   
   TH1D *__1 = new TH1D("__1","",20,-5,5);
   __1->SetBinContent(9,2);
   __1->SetBinContent(10,6);
   __1->SetBinContent(11,2);
   __1->SetBinContent(12,1);
   __1->SetBinContent(13,1);
   __1->SetBinContent(14,1);
   __1->SetBinContent(17,1);
   __1->SetBinContent(19,1);
   __1->SetEntries(15);
   __1->SetStats(0);
   __1->SetLineWidth(3);
   __1->GetXaxis()->SetTitle("Pull [#sigma]");
   __1->GetXaxis()->CenterTitle(true);
   __1->GetXaxis()->SetLabelFont(42);
   __1->GetXaxis()->SetLabelSize(0.035);
   __1->GetXaxis()->SetTitleOffset(1.1);
   __1->GetXaxis()->SetTitleFont(42);
   __1->GetYaxis()->SetTitle("Fits");
   __1->GetYaxis()->CenterTitle(true);
   __1->GetYaxis()->SetNdivisions(4000510);
   __1->GetYaxis()->SetLabelFont(42);
   __1->GetYaxis()->SetLabelSize(0.035);
   __1->GetYaxis()->SetTitleOffset(1.1);
   __1->GetYaxis()->SetTitleFont(42);
   __1->GetZaxis()->SetLabelFont(42);
   __1->GetZaxis()->SetLabelSize(0.035);
   __1->GetZaxis()->SetTitleSize(0.035);
   __1->GetZaxis()->SetTitleFont(42);
   __1->Draw("HIST");
   
   TPaveText *pt = new TPaveText(0,0,0,0,"brNDC");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetTextFont(44);
   pt->SetTextSize(26);
   TText *pt_LaTex = pt->AddText("#splitline{Mean = 0.6#pm0.4#sigma}{Width = 1.38#sigma}");
   pt->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
