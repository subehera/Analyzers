void compare_Vn(int n=2)
{
   TFile* f[100];
   f[0] = new TFile(Form("cnm_vnm_2sub_V%d.root",n));
   f[1] = new TFile(Form("cnm_vnm_3sub_V%d.root",n));
   f[2] = new TFile(Form("cnm_vnm_4sub_V%d.root",n));

   TH1D* h22[100];
   TH1D* h24[100];
   TH1D* h26[100];
   TH1D* h28[100];

   h24[0] = (TH1D*)f[0]->Get(Form("hC%d%d4_rebinned",n,n));
   h26[0] = (TH1D*)f[0]->Get(Form("hC%d%d6_rebinned",n,n));
   h28[0] = (TH1D*)f[0]->Get(Form("hC%d%d8_rebinned",n,n));

   h24[1] = (TH1D*)f[1]->Get(Form("hC%d%d4_rebinned",n,n));
   h26[1] = (TH1D*)f[1]->Get(Form("hC%d%d6_rebinned",n,n));
   h28[1] = (TH1D*)f[1]->Get(Form("hC%d%d8_rebinned",n,n));

   h24[2] = (TH1D*)f[2]->Get(Form("hC%d%d4_4sub_rebinned",n,n));
   h26[2] = (TH1D*)f[2]->Get(Form("hC%d%d6_rebinned",n,n));
   h28[2] = (TH1D*)f[2]->Get(Form("hC%d%d8_rebinned",n,n));

   h24[0]->SetMarkerStyle(20);
   h26[0]->SetMarkerStyle(20);
   h28[0]->SetMarkerStyle(20);
   h24[1]->SetMarkerStyle(20);
   h26[1]->SetMarkerStyle(20);
   h28[1]->SetMarkerStyle(20);
   h24[2]->SetMarkerStyle(20);
   h26[2]->SetMarkerStyle(20);
   h28[2]->SetMarkerStyle(20);

   h24[0]->SetMarkerColor(1);
   h26[0]->SetMarkerColor(1);
   h28[0]->SetMarkerColor(1);
   h24[1]->SetMarkerColor(2);
   h26[1]->SetMarkerColor(2);
   h28[1]->SetMarkerColor(2);
   h24[2]->SetMarkerColor(4);
   h26[2]->SetMarkerColor(4);
   h28[2]->SetMarkerColor(4);

   TCanvas* c = new TCanvas("c","c",900,900);   
   c->Divide(2,2);
   c->cd(1);
   h24[0]->Draw("P");
   h24[1]->Draw("PSAME");
   h24[2]->Draw("PSAME");
   c->cd(2);
   h28[0]->Draw("P");
   h28[1]->Draw("PSAME");
   h28[2]->Draw("PSAME");
   c->cd(3);
   h26[0]->Draw("P");
   h26[1]->Draw("PSAME");
   h26[2]->Draw("PSAME");
}
