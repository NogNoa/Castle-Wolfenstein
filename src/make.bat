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

del cwa.OBJ
cd ..\asm
d:ml cwa.asm
rename cwa.OBJ ..\src\cwa.OBJ  
cd ..\src
b:link b:c MEMORY MAIN config game_f~1 cwa,cw,cw,b:mc
