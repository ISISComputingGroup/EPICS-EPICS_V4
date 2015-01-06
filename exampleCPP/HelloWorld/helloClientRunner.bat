@echo OFF
REM
REM Copyright: See the COPYRIGHT that is included with this distribution.
REM            EPICS exampleCPP is distributed subject to a Software License
REM            Agreement found in file LICENSE that is included with this
REM            distribution.
REM
REM Abs: helloClientRunner executes the helloWorldClient EV4 client.
REM
REM Rem: helloWorldClient is a simple example of an E4C client demonstrating support
REM      for a client/server environment in EPICS V4. 
REM
REM      helloWorldClient passes the argument it was given to the helloServer,
REM      which constructs and returns a simple greeting. The helloClient receives 
REM      the greeting, and prints it.
REM
REM Usage: Execute helloClientRunner any time while helloServerRunner is running.   
REM 
REM         > ./helloClientRunner [optional name, if not supplied, "Dave" is used].  
REM
REM         E.g.: 
REM         bash-3.2$ ./helloClientRunner julie
REM         Hello julie
REM 
REM Ref: 
REM ----------------------------------------------------------------------------
REM Auth: 17-Jan-2013, Dave Hickin (david.hickin@diamond.ac.uk)
REM
REM ============================================================================

set TOP=%~dp0
set PATH=%TOP%bin\%EPICS_HOST_ARCH%;%TOP%..\..\pvAccessCPP\bin\%EPICS_HOST_ARCH%;%TOP%..\..\pvDataCPP\bin\%EPICS_HOST_ARCH%;%PATH%
if "%1" == "" (
    set ARG=Dave
) else (
    set ARG=%1
)
"%TOP%bin\%EPICS_HOST_ARCH%\HelloClient.exe" %ARG%
