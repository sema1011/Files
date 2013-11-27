@if "%DEBUG%" == "" @echo off
@rem ##########################################################################
@rem
@rem  FileDuplicateFinderUI startup script for Windows
@rem
@rem ##########################################################################

@rem Set local scope for the variables with windows NT shell
if "%OS%"=="Windows_NT" setlocal

@rem Add default JVM options here. You can also use JAVA_OPTS and FILE_DUPLICATE_FINDER_UI_OPTS to pass JVM options to this script.
set DEFAULT_JVM_OPTS=-Xmx768m

set DIRNAME=%~dp0
if "%DIRNAME%" == "" set DIRNAME=.
set APP_BASE_NAME=%~n0
set APP_HOME=%DIRNAME%..

@rem Find java.exe
if defined JAVA_HOME goto findJavaFromJavaHome

set JAVA_EXE=java.exe
%JAVA_EXE% -version >NUL 2>&1
if "%ERRORLEVEL%" == "0" goto init

echo.
echo ERROR: JAVA_HOME is not set and no 'java' command could be found in your PATH.
echo.
echo Please set the JAVA_HOME variable in your environment to match the
echo location of your Java installation.

goto fail

:findJavaFromJavaHome
set JAVA_HOME=%JAVA_HOME:"=%
set JAVA_EXE=%JAVA_HOME%/bin/java.exe

if exist "%JAVA_EXE%" goto init

echo.
echo ERROR: JAVA_HOME is set to an invalid directory: %JAVA_HOME%
echo.
echo Please set the JAVA_HOME variable in your environment to match the
echo location of your Java installation.

goto fail

:init
@rem Get command-line arguments, handling Windowz variants

if not "%OS%" == "Windows_NT" goto win9xME_args
if "%@eval[2+2]" == "4" goto 4NT_args

:win9xME_args
@rem Slurp the command line arguments.
set CMD_LINE_ARGS=
set _SKIP=2

:win9xME_args_slurp
if "x%~1" == "x" goto execute

set CMD_LINE_ARGS=%*
goto execute

:4NT_args
@rem Get arguments from the 4NT Shell from JP Software
set CMD_LINE_ARGS=%$

:execute
@rem Setup the command line

set CLASSPATH=%APP_HOME%\lib\FileDuplicateFinderUI-2.0.0.jar;%APP_HOME%\lib\commons-vfs-2.0-SNAPSHOT.jar;%APP_HOME%\lib\commons-vfs-sandbox-2.0-SNAPSHOT.jar;%APP_HOME%\lib\jcifs-1.3.17.jar;%APP_HOME%\lib\jsch-0.1.48.jar;%APP_HOME%\lib\JGoogleAnalyticsTracker-1.2.1-SNAPSHOT-jar-with-dependencies.jar;%APP_HOME%\lib\org.eclipse.swt.nl1_3.2.0.v200606220026.jar;%APP_HOME%\lib\org.eclipse.swt.nl2a_3.2.0.v200606220026.jar;%APP_HOME%\lib\org.eclipse.swt.nl2_3.2.0.v200606220026.jar;%APP_HOME%\lib\org.eclipse.swt.nlBidi_3.2.0.v200606220026.jar;%APP_HOME%\lib\swing2swt.jar;%APP_HOME%\lib\swt-grouplayout.jar;%APP_HOME%\lib\com.ibm.icu_4.4.2.v20110823.jar;%APP_HOME%\lib\org.eclipse.core.commands_3.6.0.I20110111-0800.jar;%APP_HOME%\lib\org.eclipse.core.databinding.beans_1.2.100.I20100824-0800.jar;%APP_HOME%\lib\org.eclipse.core.databinding.observable_1.4.0.I20110222-0800.jar;%APP_HOME%\lib\org.eclipse.core.databinding.property_1.4.0.I20110222-0800.jar;%APP_HOME%\lib\org.eclipse.core.databinding_1.4.0.I20110111-0800.jar;%APP_HOME%\lib\org.eclipse.core.runtime_3.7.0.v20110110.jar;%APP_HOME%\lib\org.eclipse.equinox.common_3.6.0.v20110523.jar;%APP_HOME%\lib\org.eclipse.equinox.registry_3.5.101.R37x_v20110810-1611.jar;%APP_HOME%\lib\org.eclipse.jface.databinding_1.5.0.I20100907-0800.jar;%APP_HOME%\lib\org.eclipse.jface.text_3.7.2.v20111213-1208.jar;%APP_HOME%\lib\org.eclipse.jface_3.7.0.v20110928-1505.jar;%APP_HOME%\lib\org.eclipse.osgi_3.7.2.v20120110-1415.jar;%APP_HOME%\lib\org.eclipse.text_3.5.101.v20110928-1504.jar;%APP_HOME%\lib\org.eclipse.ui.forms_3.5.101.v20111011-1919.jar;%APP_HOME%\lib\org.eclipse.ui.workbench_3.7.1.v20120104-1859.jar;%APP_HOME%\lib\swt.jar;%APP_HOME%\lib\FileDuplicateFinderCore-2.0.0.jar;%APP_HOME%\lib\commons-beanutils-1.8.3.jar;%APP_HOME%\lib\commons-io-2.0.1.jar;%APP_HOME%\lib\groovy-all-1.8.4.jar;%APP_HOME%\lib\commons-lang3-3.0.1.jar;%APP_HOME%\lib\xz-1.0.jar;%APP_HOME%\lib\commons-compress-1.4.jar;%APP_HOME%\lib\commons-logging-1.1.1.jar;%APP_HOME%\lib\commons-codec-1.5.jar;%APP_HOME%\lib\commons-net-3.1.jar;%APP_HOME%\lib\commons-httpclient-3.1.jar;%APP_HOME%\lib\commons-collections-3.2.1.jar;%APP_HOME%\lib\jackson-core-asl-1.8.0.jar;%APP_HOME%\lib\jackson-mapper-asl-1.8.0.jar;%APP_HOME%\lib\httpcore-4.1.jar;%APP_HOME%\lib\httpclient-4.1.jar;%APP_HOME%\lib\aws-java-sdk-1.3.12.jar;%APP_HOME%\lib\jsr166y-1.7.0.jar;%APP_HOME%\lib\extra166y-1.7.0.jar;%APP_HOME%\lib\gpars-0.12.jar

@rem Execute FileDuplicateFinderUI
"%JAVA_EXE%" %DEFAULT_JVM_OPTS% %JAVA_OPTS% %FILE_DUPLICATE_FINDER_UI_OPTS%  -classpath "%CLASSPATH%" com.sleepcamel.fileduplicatefinder.ui.MainView %CMD_LINE_ARGS%

:end
@rem End local scope for the variables with windows NT shell
if "%ERRORLEVEL%"=="0" goto mainEnd

:fail
rem Set variable FILE_DUPLICATE_FINDER_UI_EXIT_CONSOLE if you need the _script_ return code instead of
rem the _cmd.exe /c_ return code!
if  not "" == "%FILE_DUPLICATE_FINDER_UI_EXIT_CONSOLE%" exit 1
exit /b 1

:mainEnd
if "%OS%"=="Windows_NT" endlocal

:omega
