@echo OFF
set TOP=%~dp0
set PATH=%TOP%pvAccessCPP\bin\%EPICS_HOST_ARCH%;%TOP%pvDataCPP\bin\%EPICS_HOST_ARCH%;%TOP%normativeTypesCPP\bin\%EPICS_HOST_ARCH%;%TOP%pvDatabaseCPP\bin\%EPICS_HOST_ARCH%;%PATH%
