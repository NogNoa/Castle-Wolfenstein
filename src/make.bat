del ..\bin\cw.exe
mc1 game_f~1 > ..\game_f.err 
mc1 config > ..\config.err 
mc1 memory > ..\memory.err 
mc1 main > ..\main.err 
mc1 periph~1 > ..\periph.err 
mc2 game_f~1
mc2 config 
mc2 memory 
mc2 main
mc2 periph~1


del cwa.OBJ
del drawa.OBJ
del sonara.OBJ
cd ..\asm
d:ml /c cwa.asm > ..\asm.err
d:ml /c drawa.asm >> ..\asm.err
d:ml /c sonara.asm >> ..\asm.err
rename cwa.OBJ ..\src\cwa.OBJ
rename drawa.OBJ ..\src\drawa.OBJ
rename sonara.OBJ ..\src\sonara.OBJ
cd ..\src
b:link b:c MEMORY drawa MAIN config game_f~1 cwa periph~1 sonara,cw,cw,b:mc /map /line > ..\link.err
rename cw.exe ..\bin\cw.exe
cd ..
type asm.err game_f.err config.err memory.err main.err periph.err link.err > cw.err
cd src