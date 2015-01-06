@echo OFF
REM
REM Copyright: See the COPYRIGHT that is included with this distribution.
REM            EPICS exampleCPP is distributed subject to a Software License
REM            Agreement found in file LICENSE that is included with this
REM            distribution.
REM
REM Abs: start_server starts the channel archiver service, which can query a
REM      Channel Archiver index file, with a given service name 
REM
REM Rem: The Channel Archiver Service is an example of an EPICS v4 RPC service.
REM 
REM
REM Usage:  Execute helloServerRunner prior to executing helloClientRunner. 
REM 
REM         > ./helloServerRunner          
REM 
REM ----------------------------------------------------------------------------
REM Auth: 17-Jan-2013, Dave Hickin (david.hickin@diamond.ac.uk)
REM ============================================================================

set TOP=%~dp0
set PATH=%TOP%bin\%EPICS_HOST_ARCH%;%TOP%..\..\pvAccessCPP\bin\%EPICS_HOST_ARCH%;%TOP%..\..\pvDataCPP\bin\%EPICS_HOST_ARCH%;%PATH%
"%TOP%bin\%EPICS_HOST_ARCH%\HelloService.exe"
