#include "cw.h"
#include "video.h"

extern bool isDemo;

wait_for_input(col, row, str, stop_char)
string str;
char stop_char;
{
    char in_char;
    int i;
    BiosPuts(row, col, str);
    in_char = (stop_char == '\0') ? 'a' : '\0';
    while (in_char != stop_char)
    {   if(!IsKStrok())
        {   if (isDemo)
            {   in_char = stop_char;
                for (i = 0; i <= 2000; ++i) {}
                i = 0;
            }
        }
        else
        {   in_char = (char) GetStrok();
            if (stop_char == '\0') {in_char = stop_char;}

        }
    }
    BiosVideo(SET_CURSOR_POSITION, 0, 0, (row << 8) + col);
    for (;str[i] != '\0';++i) {cputs(" ");}
}

jystk_cnfg() 
{   /*joystick config*/
    ;
}

lkfr_jystk()
{   /*look for joystick*/
    ;
}

prfl_jystk()
{   /*profile_joystick*/
    ;
}