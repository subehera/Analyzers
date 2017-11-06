void compare()
{
   TFile* f[100];
   f[0] = new TFile("cnm_vnm_std_SC23.root");
   f[1] = new TFile("cnm_vnm_2sub_SC23.root");
   f[2] = new TFile("cnm_vnm_3sub_SC23.root");
   f[3] = new TFile("cnm_vnm_4sub_SC23.root");

   TFile* ff[100];
   ff[0] = new TFile("cnm_vnm_std_SC24.root");
   ff[1] = new TFile("cnm_vnm_2sub_SC24.root");
   ff[2] = new TFile("cnm_vnm_3sub_SC24.root");
   ff[3] = new TFile("cnm_vnm_4sub_SC24.root");

   TH1D* h22[100];
   TH1D* h24[100];
   TH1D* h26[100];
   TH1D* h28[100];

   h24[0] = (TH1D*)f[0]->Get("hC234_51_rebinned");
   h28[0] = (TH1D*)ff[0]->Get("hC244_51_rebinned");

   h24[1] = (TH1D*)f[1]->Get("hC234_51_rebinned");
   h28[1] = (TH1D*)ff[1]->Get("hC244_51_rebinned");

   h24[2] = (TH1D*)f[2]->Get("hC234_51_rebinned");
   h28[2] = (TH1D*)ff[2]->Get("hC244_51_rebinned");

   h24[3] = (TH1D*)f[3]->Get("hC234_51_rebinned");
   h28[3] = (TH1D*)ff[3]->Get("hC244_51_rebinned");

   h24[0]->SetMarkerStyle(20);
   h28[0]->SetMarkerStyle(20);
   h24[1]->SetMarkerStyle(20);
   h28[1]->SetMarkerStyle(20);
   h24[2]->SetMarkerStyle(20);
   h28[2]->SetMarkerStyle(20);
   h24[3]->SetMarkerStyle(20);
   h28[3]->SetMarkerStyle(20);

   h24[0]->SetMarkerColor(1);
   h28[0]->SetMarkerColor(1);
   h24[1]->SetMarkerColor(2);
   h28[1]->SetMarkerColor(2);
   h24[2]->SetMarkerColor(4);
   h28[2]->SetMarkerColor(4);
   h24[3]->SetMarkerColor(3);
   h28[3]->SetMarkerColor(3);

   TCanvas* c = new TCanvas("c","c",900,450);   
   c->Divide(2,1);
   c->cd(1);
   h24[0]->Draw("P");
   h24[1]->Draw("PSAME");
   h24[2]->Draw("PSAME");
   h24[3]->Draw("PSAME");
   c->cd(2);
   h28[0]->Draw("P");
   h28[1]->Draw("PSAME");
   h28[2]->Draw("PSAME");
   h28[3]->Draw("PSAME");

}
