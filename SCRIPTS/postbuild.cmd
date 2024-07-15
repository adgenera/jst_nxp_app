@REM @echo off
@REM ADD THIS LINE TO YOUR PROJECT:
@REM ${ProjDirPath}/../../SCRIPTS/postbuild.cmd ${BuildArtifactFilePrefix} ${ConfigName} ${BuildLocation} ${BuildArtifactFileName}
@REM Usage: %0 ${BuildArtifactFilePrefix} ${ConfigName} ${BuildLocation} ${BuildArtifactFileName} ${SVNREV}

@setlocal ENABLEDELAYEDEXPANSION

@if "%5"=="" goto usage

@SET DEST_DIR_INPUT=%1
@SET BUILD_TARGETNAME=%2
@SET BUILD_BASE_DIR_INPUT=%3
@SET BUILD_FILE_NAME=%4
@SET SVNVERSION=%5

@echo *** SVN version: %SVNVERSION%

@REM #################################################################################

@if %BUILD_TARGETNAME%==_DevClock (
@SET TARGETNAME=CLOCK
@SET RELEASETYPE=DEBUG
) else if %BUILD_TARGETNAME%==_DevCompass (
@SET TARGETNAME=COMPASS
@SET RELEASETYPE=DEBUG
) else if %BUILD_TARGETNAME%==_DevOAT (
@SET TARGETNAME=OAT
@SET RELEASETYPE=DEBUG
) else if %BUILD_TARGETNAME%==_DevStopWatch (
@SET TARGETNAME=STOPWATCH
@SET RELEASETYPE=DEBUG
) else if %BUILD_TARGETNAME%==_RELEASE_CLOCK (
@SET TARGETNAME=CLOCK
@SET RELEASETYPE=RELEASE
) else if %BUILD_TARGETNAME%==_RELEASE_COMPASS (
@SET TARGETNAME=COMPASS
@SET RELEASETYPE=RELEASE
) else if %BUILD_TARGETNAME%==_RELEASE_OAT (
@SET TARGETNAME=OAT
@SET RELEASETYPE=RELEASE
) else if %BUILD_TARGETNAME%==_RELEASE_STOPWATCH (
@SET TARGETNAME=STOPWATCH
@SET RELEASETYPE=RELEASE
) else (
@SET TARGETNAME=UNKNOWN
@SET RELEASETYPE=UNKNOWN
)

@echo *** Release type: %RELEASETYPE%


@call set BUILD_FILE_NAME_BASE=%BUILD_FILE_NAME:.elf=%
@call set DEST_DIR=%DEST_DIR_INPUT:/=\%
@call set BUILD_BASE_DIR=%BUILD_BASE_DIR_INPUT:/=\%

@IF %BUILD_FILE_NAME_BASE:~-1%==\ SET BUILD_FILE_NAME_BASE=%BUILD_FILE_NAME_BASE:~0,-1%
@IF %DEST_DIR:~-1%==\ SET DEST_DIR=%DEST_DIR:~0,-1%
@IF %BUILD_BASE_DIR:~-1%==\ SET BUILD_BASE_DIR=%BUILD_BASE_DIR:~0,-1%

@REM #################################################################################
copy %BUILD_BASE_DIR%\build-DEVICES-%BUILD_TARGETNAME%\%BUILD_FILE_NAME_BASE%.map %DEST_DIR%
copy %BUILD_BASE_DIR%\build-DEVICES-%BUILD_TARGETNAME%\%BUILD_FILE_NAME_BASE%.args %DEST_DIR%
copy %BUILD_BASE_DIR%\build-DEVICES-%BUILD_TARGETNAME%\%BUILD_FILE_NAME_BASE%.elf_stats.txt %DEST_DIR%
@if exist %BUILD_BASE_DIR%\..\log\DEVICES.build.log (
	copy /v %BUILD_BASE_DIR%\..\log\DEVICES.build.log %DEST_DIR%\%BUILD_FILE_NAME_BASE%.build.log
) else (
	echo %DEST_DIR%\..\..\LIB\LIB_MCAL.build.log NONEXISTENT
)
@if exist %DEST_DIR%\..\..\LIB\LIB_CDD.build.log (
	copy /v %DEST_DIR%\..\..\LIB\LIB_CDD.build.log %DEST_DIR%\%BUILD_FILE_NAME_BASE%.LIB_CDD.build.log
) else (
	echo %DEST_DIR%\..\..\LIB\LIB_MCAL.build.log NONEXISTENT
)
@if exist %DEST_DIR%\..\..\LIB\LIB_MCAL.build.log (
	copy /v %DEST_DIR%\..\..\LIB\LIB_MCAL.build.log %DEST_DIR%\%BUILD_FILE_NAME_BASE%.LIB_MCAL.build.log
) else (
	echo %DEST_DIR%\..\..\LIB\LIB_MCAL.build.log NONEXISTENT
)

@printf "%SVNVERSION%" >  %DEST_DIR%\%BUILD_FILE_NAME_BASE%.SVNBUILDVERSION.txt

@IF "%RELEASETYPE%"=="RELEASE" (
	@echo *** Generate SAP file ...
	C:\PEMicro\cyclone_pro\csaps12zz.exe "%DEST_DIR%\..\..\SAP\JST-BY634_5_CyclonePro_SAP.cfg" imagefile "%DEST_DIR%\%BUILD_FILE_NAME_BASE%.sap" imagecontent "JST-BY634/5 %TARGETNAME%.SVN%SVNVERSION%.%RELEASETYPE%" "/PARAM1=%DEST_DIR%\%BUILD_FILE_NAME_BASE%.elf" "/PARAM2=JST-BY634/5 %TARGETNAME%.SVN%SVNVERSION%.%RELEASETYPE%"
)

del /F %DEST_DIR%\%BUILD_FILE_NAME_BASE%_ENV_DATA
@goto eof

@REM #################################################################################
:usage
@echo PARAMETER missing. Bye.
@echo ' ' 
@echo Usage: %0 ${BuildArtifactFilePrefix} ${ConfigName} ${BuildLocation} ${BuildArtifactFileName} ${SVNREV}
@echo Given: %0 %1 %2 %3 %4 %5
@exit 1

@REM #################################################################################
:eof

@exit 0
