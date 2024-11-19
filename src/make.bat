mc1 console > ..\console.err 
rem mc1 game_f~1
mc1 helper > ..\helper.err 
mc1 config > ..\config.err 
mc1 memory > ..\memory.err 
mc1 main > ..\main.err 
rem mc1 rank 
mc1 CtrlCo~1 > ..\CtrlCo~1.err
mc2 console 
rem mc1 game_f~1
mc2 helper 
mc2 config 
mc2 memory 
mc2 main 
rem mc2 rank 
mc2 CtrlCo~1

del gooba.OBJ  
del memorya.OBJ
del stacka.OBJ
del videa.OBJ
del Stroka.obj
cd ..\asm
d:ml gooba.asm  memorya.asm  stacka.asm  videa.asm Stroka.asm
rename gooba.OBJ ..\src\gooba.OBJ  
rename memorya.OBJ ..\src\memorya.OBJ
rename stacka.OBJ ..\src\stacka.OBJ
rename videa.OBJ ..\src\videa.OBJ
rename Stroka.OBJ ..\src\Stroka.OBJ
cd ..\src
b:link b:c CTRLCO~1 gooba MAIN config Stroka videa CONSOLE MEMORYA HELPER MEMORY STACKA,cw,cw,b:mc
