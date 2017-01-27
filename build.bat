set str=src\*.c
gcc -isystem headers -o run %str%

if "%1"=="" goto :EOF
if %1 NEQ run goto :EOF
else (
:run
if exist run.exe goto go
sleep 10
goto run
:go
run.exe
)