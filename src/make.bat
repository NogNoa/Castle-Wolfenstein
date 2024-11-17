mc1 anti_D~1 > ..\ anti_D~1.err
mc1 console > ..\console.err 
rem mc1 game_f~1
mc1 helper > ..\helper.err 
mc1 memory > ..\memory.err 
mc1 main > ..\main.err 
rem mc1 rank 
rem mc1 CtrlCo~1
mc2 anti_D~1 
mc2 console 
rem mc1 game_f~1
mc2 helper 
mc2 memory 
mc2 main 
rem mc2 rank 
rem mc2 CtrlCo~1

cd ..\asm
d:ml gooba.asm  memorya.asm  stacka.asm  videoa.asm
rename gooba.OBJ ..\src\gooba.OBJ  
rename memorya.OBJ ..\src\memorya.OBJ
rename stacka.OBJ ..\src\stacka.OBJ
rename videoa.OBJ ..\src\videoa.OBJ
cd ..\src
b:link gooba.OBJ ANTI_D~1.OBJ  MAIN.OBJ  MEMORY.OBJ   VIDEOA.OBJ CONSOLE.OBJ HELPER.OBJ MEMORYA.OBJ STACKA.OBJ b:c.obj
