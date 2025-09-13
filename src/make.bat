del ..\bin\cw.exe
mc1 init > ..\init.err 
mc1 init2 > ..\init2.err 
mc1 config > ..\config.err 
mc1 memory > ..\memory.err 
mc1 endays > ..\endays.err 
mc1 periph~1 > ..\periph.err 
mc1 quort > ..\quort.err
mc2 init
mc2 init2
mc2 config 
mc2 memory 
mc2 endays
mc2 periph~1
mc2 quort


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
b:link b:c MEMORY drawa endays quort config init init2 cwa periph~1 sonara,cw,cw,b:mc /map /line > ..\link.err
rename cw.exe ..\bin\cw.exe
cd ..
type asm.err init.err init2.err config.err quort.err memory.err endays.err periph.err link.err > cw.err
cd src