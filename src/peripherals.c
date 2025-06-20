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

byte JoyXDur, JoyYDur;

jystk_cnfg() 
{   /*joystick config*/
    bool done;
    byte centXdur, centYdur, leftXdur, upYdur, rightXdur;
    uint ucentXdur, urightXdur, uupYdurm, ucentYdur, uleftXdur, temp;
    while(!done)
    {   SetVideo(PxlClrLo);
        BiosPuts(11, 10, "Move your joystick");
        BiosPuts(13, 10, "to the center position,");
        BiosPuts(15, 10, "and press the space bar.");
        wait_for_input(0, 0, "",' ');
        prfl_jystk();
        centXdur = JoyXDur;
        centYdur = JoyYDur;
        SetVideo(PxlClrLo);
        BiosPuts(2, 1, "Move your joystick");
        BiosPuts(4, 1, "to the upper left,");
        BiosPuts(6, 1, "hold it there and");
        BiosPuts(8, 1, "press the space bar.");
        wait_for_input(0, 0, "",' ');
        prfl_jystk();
        leftXdur = JoyXDur;
        upYdur = JoyYDur;
        SetVideo(PxlClrLo);
        BiosPuts(2, 20, "Move your joystick");
        BiosPuts(4, 20, "to the upper right,");
        BiosPuts(6, 20, "hold it there and");
        BiosPuts(8, 20, "press the space bar.");
        wait_for_input(0, 0, "",' ');
        prfl_jystk();
        rightXdur = JoyXDur;
        SetVideo(PxlClrLo);
        BiosPuts(18, 20, "Move your joystick");
        BiosPuts(20, 20, "to the lower right,");
        BiosPuts(22, 20, "hold it there and");
        BiosPuts(24, 20, "press the space bar.");
        wait_for_input(0, 0, "",' ');
        prfl_jystk();
        /*JoyYDur is downYdur*/
        if (leftXdur < rightXdur && upYdur < JoyYDur)
        {   ucentXdur = (uint) centXdur;
            uleftXdur =  (uint) leftXdur; /*bp.0*/
            uleftXdur =  uleftXdur + (long) (ucentXdur - uleftXdur) / 2;
            urightXdur = (uint) rightXdur;
            uint local_d = ucentXdur + (long) (rightXdur - ucentXdur) / 2;

        }
    }
}

lkfr_jystk()
{   /*look for joystick*/
    ;
}

prfl_jystk()
{   /*profile_joystick*/
    ;
}