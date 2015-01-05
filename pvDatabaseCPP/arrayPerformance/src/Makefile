TOP = ..
include $(TOP)/configure/CONFIG

LIBRARY_IOC += pvDatabaseExample
pvDatabaseExample_LIBS += pvDatabase pvAccess pvData Com
pvDatabaseExample_LIBS += $(EPICS_BASE_IOC_LIBS)


INC+= arrayPerformance.h
LIBSRCS += arrayPerformance.cpp
INC+= longArrayMonitor.h
LIBSRCS += longArrayMonitor.cpp
INC+= longArrayGet.h
LIBSRCS += longArrayGet.cpp
INC+= longArrayPut.h
LIBSRCS += longArrayPut.cpp

PROD_HOST += arrayPerformanceMain
arrayPerformanceMain_SRCS += arrayPerformanceMain.cpp
arrayPerformanceMain_LIBS += pvDatabaseExample
arrayPerformanceMain_LIBS += pvDatabase pvAccess pvData Com

PROD_HOST += longArrayMonitorMain
longArrayMonitorMain_SRCS += longArrayMonitorMain.cpp
longArrayMonitorMain_LIBS += pvDatabaseExample
longArrayMonitorMain_LIBS += pvDatabase pvAccess pvData Com

PROD_HOST += longArrayGetMain
longArrayGetMain_SRCS += longArrayGetMain.cpp
longArrayGetMain_LIBS += pvDatabaseExample
longArrayGetMain_LIBS += pvDatabase pvAccess pvData Com

PROD_HOST += longArrayPutMain
longArrayPutMain_SRCS += longArrayPutMain.cpp
longArrayPutMain_LIBS += pvDatabaseExample
longArrayPutMain_LIBS += pvDatabase pvAccess pvData Com

PROD_HOST += vectorPerformanceMain
vectorPerformanceMain_SRCS += vectorPerformanceMain.cpp
vectorPerformanceMain_LIBS += pvDatabaseExample
vectorPerformanceMain_LIBS += pvDatabase pvAccess pvData Com


include $(TOP)/configure/RULES

