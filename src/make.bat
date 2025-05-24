del cw.exe
mc1 game_f~1 > ..\game_f.err 
mc1 config > ..\config.err 
mc1 memory > ..\memory.err 
mc1 main > ..\main.err 
rem mc1 rank 
mc2 game_f~1
mc2 config 
mc2 memory 
mc2 main 
rem mc2 rank 

cd ..\asm
d:ml /c cwa.asm > ..\asm.err
d:ml /c drawa.asm >> ..\asm.err
d:ml /c sonara.asm >> ..\asm.err
rename /f cwa.OBJ ..\src\cwa.OBJ
rename /f drawa.OBJ ..\src\drawa.OBJ
rename /f sonara.OBJ ..\src\sonara.OBJ
cd ..\src
b:link b:c MEMORY drawa MAIN config game_f~1 cwa sonara,cw,cw,b:mc
rename /f cw.exe ..\bin\
