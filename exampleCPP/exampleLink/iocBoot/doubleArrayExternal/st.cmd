< envPaths

cd ${TOP}

## Register all support components
dbLoadDatabase("dbd/exampleLink.dbd")
exampleLink_registerRecordDeviceDriver(pdbbase)

## Load record instance
dbLoadRecords("db/dbArray.db","name=doubleArrayExternal,type=DOUBLE");

cd ${TOP}/iocBoot/${IOC}
iocInit()
startPVAServer
