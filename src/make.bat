mc1 anti_D~1 
mc1 console 
mc1 game_files 
mc1 helper 
mc1 memory 
mc1 main 
mc1 rank 
mc1 CtrlConfig
mc2 anti_D~1 
mc2 console 
mc2 game_files 
mc2 helper 
mc2 memory 
mc2 main 
mc2 rank 
mc2 CtrlConfig

cd ..\asm
d:ml gooba.asm  memorya.asm  stacka.asm  videoa.asm
rename gooba.OBJ  memorya.OBJ  stacka.OBJ  videoa.OBJ ..\src
cd ..\src
b:link gooba.OBJ ANTI_D~1.OBJ  MAIN.OBJ  MEMORY.OBJ   VIDEOA.OBJ CONSOLE.OBJ HELPER.OBJ MEMORYA.OBJ STACKA.OBJ b:c.obj
