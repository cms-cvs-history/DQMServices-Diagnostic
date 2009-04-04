#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include "TFile.h" 
#include "TGraphErrors.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TStyle.h"
#include "HDQMGraphAnalysis.h"


void HDQMGraphAnalysis::plotHDQMGraphAnalysis(std::string& ListItems)
{

  //
  TFile *f  = TFile::Open( "./historicDQM.root","read");
  if( f->IsZombie() || f == 0 ) return;
   
  //
  TStyle* theStyle= new TStyle();
  theStyle->SetOptStat(0);
  theStyle->SetOptFit(111);
  theStyle->SetStatFont(12);
  theStyle->SetStatBorderSize(1);
  theStyle->SetCanvasColor(0);
  theStyle->SetCanvasBorderMode(0);
  theStyle->SetPadBorderMode(0);
  theStyle->SetPadColor(0);
  theStyle->SetFillColor(0);
  theStyle->SetLineWidth(1);
  theStyle->SetLineStyle(2);
  theStyle->SetPalette(1);
  theStyle->cd();

   
  //
  TLegend *legendE = new TLegend(0.75,0.81,0.95,0.98);
  std::vector<TGraphErrors*> vGraph;
  std::vector<std::string> vString;
  
 
  
  //
  // Unpack ItemList ...
  //
  std::string::size_type oldloc = 0; 
  std::string::size_type loc = ListItems.find( ",", oldloc );
   
   while( loc != std::string::npos ) {
     vString.push_back((ListItems.substr(oldloc,loc-oldloc)));
     oldloc=loc+1;
     loc=ListItems.find( ",", oldloc );
     }
   
  vString.push_back((ListItems.substr(oldloc,loc-oldloc)));
 
 
 
  //
  //  Find the graphs in historicDQM.root
  //
  for (size_t i=0; i<vString.size(); i++)
  {  
     TGraphErrors *g = 0;
     if (!_reverse_order) g = (TGraphErrors*)f->Get((vString.at(i)+"_"+_quantity).c_str());
     else                 g = (TGraphErrors*)f->Get((_quantity+"_"+vString.at(i)).c_str());
     if (g!=0) {
        vGraph.push_back(g);
        vGraph.back()->SetMarkerColor(2+i);
	if (_reverse_order)
	{
	  std::string vString2 = vString.at(i);
	  std::string  _quantity2 = _quantity;
	  
	  if (vString.at(i).find("_mean")!=std::string::npos)
	  {	 
	    vString2.replace(vString2.find("_mean"),vString2.size()-vString2.find("_mean"),"");
	    _quantity2.append("_mean");}
	  else if (vString.at(i).find("_rms")!=std::string::npos)
	  {
	    vString2.replace(vString2.find("_rms"),vString2.size()-vString2.find("_rms"),"");	  
	    _quantity2.append("_rms");} 
	  
	  legendE->AddEntry(vGraph.back(),vString2.c_str(),"P");
	  vGraph.back()->SetTitle(_quantity2.c_str());}
	  
	else 
	{
          legendE->AddEntry(vGraph.back(),(vString.at(i)).c_str(),"P");
	  vGraph.back()->SetTitle(_quantity.c_str());}
	}
     else {
        if (!_reverse_order) std::cout << "No graph found called " << vString.at(i)<<"_"<<_quantity << std::endl;
        else std::cout << "No graph found called " << _quantity <<"_"<< vString.at(i)<< std::endl;}
     }
    
      
  //
  // Find maximum, minimum of all the graph
  //
  std::vector<float> graphMin;
  std::vector<float> graphMax;
  std::vector<float>::iterator max; 
  std::vector<float>::iterator min; 
 
  for (unsigned int i=0; i<vGraph.size(); i++)
  { 
    graphMin.push_back(findGraphMax(vGraph.at(i)));
    graphMax.push_back(findGraphMin(vGraph.at(i))); 
 
    max = std::max_element(graphMin.begin(), graphMin.end());
    min = std::min_element(graphMax.begin(), graphMax.end());}
    
 

  //
  // Superimpose the graphs
  //
  if (vGraph.size()>0) 
  {
   TCanvas *C = new TCanvas("","");
   std::string CanvasName = _quantity+_canvas_flag+"_superimposed.gif";
   
    
   float max_graph = 0.;
   max_graph = (*max)+((*max)-(*min))/5.;
   float min_graph = 0.;
   min_graph = (*min)-((*max)-(*min))/5.;
   
   if (_max == 99.) vGraph.at(0)->SetMaximum(max_graph);
   else             vGraph.at(0)->SetMaximum(_max);
   
   if (_min == 99.) vGraph.at(0)->SetMinimum(min_graph);
   else 	    vGraph.at(0)->SetMinimum(_min);
   
   vGraph.at(0)->Draw("alp");
   
   
   for (size_t i=1; i<vGraph.size(); i++) vGraph.at(i)->Draw("lp");
   legendE->Draw();
   C->SaveAs(CanvasName.c_str()); 
   C->SaveAs(CanvasName.replace(CanvasName.find("."),CanvasName.size()-CanvasName.find("."),".C").c_str()); 
 
   }
  
    
}


double HDQMGraphAnalysis::findGraphMax(TGraphErrors* g)
{
  // GetMaximum() doesn't work ....
  int n = g->GetN();
  double* y = g->GetY();
  int locmax = TMath::LocMax(n,y);
  return  y[locmax];
}


double HDQMGraphAnalysis::findGraphMin(TGraphErrors* g)
{
  // GetMinimum() doesn't work ....
  int n = g->GetN();
  double* y = g->GetY();
  int locmin = TMath::LocMin(n,y);
  return  y[locmin];
}
