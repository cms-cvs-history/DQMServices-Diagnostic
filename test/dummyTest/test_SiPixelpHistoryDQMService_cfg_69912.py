import FWCore.ParameterSet.Config as cms

process = cms.Process("PWRITE")

#########################
# message logger
#########################

process.MessageLogger = cms.Service("MessageLogger",
                                    destinations = cms.untracked.vstring('pixel_69912'),
                                    pixel_69912 = cms.untracked.PSet(threshold = cms.untracked.string('DEBUG')),
                                    debugModules = cms.untracked.vstring('*')
                                    )


#########################
# maxEvents ...
#########################

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(1))
process.source = cms.Source("EmptySource",
                            timetype = cms.string("runnumber"),
                            firstRun = cms.untracked.uint32(1),
                            lastRun  = cms.untracked.uint32(1),
                            interval = cms.uint32(1)
                            )

#########################
# DQM services
#########################

process.load("DQMServices.Core.DQM_cfg")


########################
# DB parameters
########################

process.PoolDBOutputService = cms.Service("PoolDBOutputService",
                                          BlobStreamerName = cms.untracked.string('TBufferBlobStreamingService'),
                                          outOfOrder = cms.untracked.bool(True),
                                          DBParameters = cms.PSet(
    messageLevel = cms.untracked.int32(2),
    authenticationPath = cms.untracked.string('/afs/cern.ch/cms/DB/conddb')
    ),
                                          timetype = cms.untracked.string('runnumber'),
                                          connect = cms.string('sqlite_file:dbfile.db'),
                                          toPut = cms.VPSet(cms.PSet(
    record = cms.string("HDQMSummary"),
    tag = cms.string("HDQM_test")
    )),
                                          logconnect = cms.untracked.string("sqlite_file:log.db")
                                          )

########################
# POPCON Application
########################
process.siPixelDQMHistoryPopCon = cms.EDAnalyzer("SiPixelDQMHistoryPopCon",
                                                 record = cms.string("HDQMSummary"),
                                                 loggingOn = cms.untracked.bool(True),
                                                 SinceAppendMode = cms.bool(True),
                                                 Source = cms.PSet(since = cms.untracked.uint32(69587),debug = cms.untracked.bool(False))
                                                 )


########################
# HistoricDQMService
########################

process.SiPixelHistoryDQMService = cms.Service("SiPixelHistoryDQMService",
                                               RunNb = cms.uint32(69587),
                                               accessDQMFile = cms.bool(True),
                                               FILE_NAME = cms.untracked.string("/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/data/Cosmics__Commissioning08_CRAFT_ALL_V11_227_Tosca090216_ReReco_FromTrackerPointing_v2__RAW-RECO/69912/DQM_V0001_R000069912__Cosmics__Commissioning08_CRAFT_ALL_V11_227_Tosca090216_ReReco_FromTrackerPointing_v2__RAW-RECO_1.root"),
                                               ME_DIR = cms.untracked.string("Run 69912/SiPixel"),
                                               histoList = cms.VPSet(
    
    # quantities are 'stat', 'landau', 'gauss'
    # where
    #'stat' includes entries, mean, rms
    #'landau' includes
    #'gauss' includes gaussMean, gaussSigma
    
    
    # CKFTk
    
    cms.PSet( keyName = cms.untracked.string("SUMOFF_ClustX"), quantitiesToExtract = cms.untracked.vstring("user") ),
    cms.PSet( keyName = cms.untracked.string("SUMOFF_ClustY"), quantitiesToExtract = cms.untracked.vstring("user") ),
    cms.PSet( keyName = cms.untracked.string("SUMOFF_adc"), quantitiesToExtract = cms.untracked.vstring("user") )
    )
                                               )


# Schedule

process.p = cms.Path(process.siPixelDQMHistoryPopCon)




