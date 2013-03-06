@ECHO OFF
:lm
ECHO -------------------------
SET /P exec="READY>>"
ECHO -------------------------
CALL %exec%
ECHO Exit code: %ERRORLEVEL%
GOTO lm
