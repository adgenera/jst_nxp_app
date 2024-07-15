@REM @echo off
@REM ADD THIS LINE TO YOUR PROJECT:
@REM ${ProjDirPath}/../../SCRIPTS/postbuild.cmd ${BuildArtifactFilePrefix} ${ConfigName} ${BuildLocation} ${BuildArtifactFileName}
@REM Usage: %0 ${BuildArtifactFilePrefix} ${ConfigName} ${BuildLocation} ${BuildArtifactFileName}

@setlocal ENABLEDELAYEDEXPANSION

@SET DEST_DIR_INPUT=%1
@SET TARGETNAME=%2
@SET BUILD_BASE_DIR_INPUT=%3
@SET BUILD_FILE_NAME=%4

@REM #################################################################################

@call set BUILD_FILE_NAME_BASE=%BUILD_FILE_NAME:.elf=%
@call set DEST_DIR=%DEST_DIR_INPUT:/=\%
@call set BUILD_BASE_DIR=%BUILD_BASE_DIR_INPUT:/=\%

@IF %BUILD_FILE_NAME_BASE:~-1%==\ SET BUILD_FILE_NAME_BASE=%BUILD_FILE_NAME_BASE:~0,-1%
@IF %DEST_DIR:~-1%==\ SET DEST_DIR=%DEST_DIR:~0,-1%
@IF %BUILD_BASE_DIR:~-1%==\ SET BUILD_BASE_DIR=%BUILD_BASE_DIR:~0,-1%

@REM del /F %BUILD_BASE_DIR%\..\..\..\LIB\LIB_MCAL_DEBUG.lib
@REM del /F %BUILD_BASE_DIR%\..\..\..\LIB\LIB_MCAL_DEBUG.lst
@if exist %BUILD_BASE_DIR%\..\log\LIB_MCAL.build.log (
	copy /v %BUILD_BASE_DIR%\..\log\LIB_MCAL.build.log %DEST_DIR%\
) else (
	echo %BUILD_BASE_DIR%\..\log\LIB_MCAL.build.log NONEXISTENT
)

@exit 0