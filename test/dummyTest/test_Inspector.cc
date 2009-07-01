{
#include <stdio.h>
#include <time.h>


/* 
   Extraction of the summary informations using 
   DQMServices/Diagnostic/test/HDQMInspector.
   The sqlite database should have been filled using the new SiStripHistoryDQMService.   
   
   */

gSystem->Load("libFWCoreFWLite");  
gSystem->Load("libtestSiStripHistoricDQM"); 
gSystem->Load("libCondFormatsSiStripObjects"); 

AutoLibraryLoader::enable();
   
gROOT->Reset();


HDQMInspector A;
A.setDB("sqlite_file:dbfile.db","HDQM_test","cms_cond_strip","w3807dev","");

A.setDebug(1);
A.setDoStat(1);

//A.setBlackList("68286");


//createTrend(std::string ListItems, std::string CanvasName="", int logy=0,std::string Conditions="", unsigned int firstRun=1, unsigned int lastRun=0xFFFFFFFE);
A.createTrend("268435456@Chi2_CKFTk@entries", "number_of_tracks.gif",1,"268435456@NumberOfTracks_CKFTk@entries>10000&&268435456@NumberOfRecHitsPerTrack_CKFTk@entries>0",2,70416);

// 
A.createTrend("
369098752@Summary_TotalNumberOfClusters_OnTrack@mean,369098752@Summary_ClusterChargeCorr_OnTrack@landauPeak,
436207616@Summary_TotalNumberOfClusters_OnTrack@mean,436207616@Summary_ClusterChargeCorr_OnTrack@landauPeak,
402653184@Summary_TotalNumberOfClusters_OnTrack@mean,402653184@Summary_ClusterChargeCorr_OnTrack@landauPeak,
469762048@Summary_TotalNumberOfClusters_OnTrack@mean,469762048@Summary_ClusterChargeCorr_OnTrack@landauPeak",
"OnTrackClusters.gif",0,"268435456@NumberOfTracks_CKFTk@entries>10000&&268435456@NumberOfRecHitsPerTrack_CKFTk@entries>0",1,70416);


}