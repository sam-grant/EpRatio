


  // Station loop
  for (int stn = 12 ; stn < 19; stn = stn + 6 ) {

    string name = "Station["+to_string(stn)+"]/PositronsQuality/EoverPvsTime";
    string axes = ";Cluster time [#mus];E/p";

    TH2D *h_gain = (TH2D*)input->Get(name);
    TH2D *h_preGain = (TH2D*)input->Get(name+"PreGainCorr");

    // Crystal loop
    for (int xtal = 0 ; xtal < 54 ; xtal++) {

//        // Put strings together for iterting hist/file/title names
//     string tstn = "Stn "+to_string(calo-1)+", Crystal "+to_string(xtal);
//     string h = stn+ffoo+"_"+to_string(xtal);
//     string cmap_fname = stn+"cmap_"+ffoo+"_"+to_string(xtal);
//     string fit_fname = stn+ffoo+"_"+to_string(xtal);
//     string g_fname = stn+"gauss_"+ffoo+"_"+to_string(xtal);
//     string title = tstn+afoo;
          //cout<<h<<endl;



//     if (Ep_vs_t == 0) continue;
//     Ep_vs_t->GetXaxis()->SetLimits(0,4.2*cycles);
//     CMAP(Ep_vs_t, title, cmap_fname, output, save);
//     FitGaussSlices(Ep_vs_t, title, fit_fname, g_fname, output, calo, save);

   } // xtal

 } // stn