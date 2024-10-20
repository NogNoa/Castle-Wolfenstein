#include "cw.h"
#include "dos.h"

int Set_Video_mode (byte mode_p);
void BIOS_Video(int A, int B, int C, int D); 

int row_coll(byte row, byte coll)
{   
    return (row - 1) << 8 | (coll - 1);
}

int sum_5fd6;
int arr_5fd6[36];

int main()
{
    Set_Video_mode(4);
    BIOS_Video(SET_CURSOR_POSITION, 0, 0, row_coll(2,2));
    cputs("072684");
    sum_5fd6 = sum(arr_5fd6, 36);
}