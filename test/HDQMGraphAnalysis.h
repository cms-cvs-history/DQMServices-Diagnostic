#ifndef DQM_SiStripHistoricInfoClient_HDQMGraphAnalysis_H
#define DQM_SiStripHistoricInfoClient_HDQMGraphAnalysis_H
//---------------------------------------------------------//
//
// Superimpose graphs stored in historicDQM.root...
//
// HDQMGraphAnalysis A("ClusterStoNCorr_OnTrack_landauPeak");
// A.plotHDQMGraphAnalysis("TIB,TOB,TID,TEC");
// 
//---------------------------------------------------------//
//---------------------------------------------------------//
// 
//  2008 - anne-catherine.le.bihan@cern.ch 
//
//---------------------------------------------------------//

class TGraphErrors;


class HDQMGraphAnalysis {

public:   
  
   HDQMGraphAnalysis():_quantity("",false){};
   HDQMGraphAnalysis(TString quantity, bool reverse_order, TString canvas_flag, float min, float max){ _quantity = quantity; _reverse_order = reverse_order; _canvas_flag = canvas_flag; _max = max; _min = min;};
   ~HDQMGraphAnalysis(){};
   void plotHDQMGraphAnalysis(std::string& ListItems);
  
private:
 
   std::string _quantity;
   bool _reverse_order;
   std::string _canvas_flag;
   double findGraphMax(TGraphErrors* g);
   double findGraphMin(TGraphErrors* g);
   float _max;
   float _min;

};
#endif //DQM_SiStripHistoricInfoClient_HDQMGraphAnalysis
