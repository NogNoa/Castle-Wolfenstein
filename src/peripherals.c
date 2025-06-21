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
    BiosVideo(SET_CURSOR_POSITION, 0, 0, RowColl(row, col));
    for (;str[i] != '\0';++i) {cputs(" ");}
}

byte JoyXDur, JoyYDur;
extern bool sagital;
extern byte LC_L_RC[11], RC_LC[11], UC_YCU[11], YC_UC[11];

jystk_cnfg() 
{   /*joystick config*/
    bool done = false;
    byte centXdur, centYdur, leftXdur, upYdur, rightXdur, downYdur;
    byte brightXdur, bdownYdur, bleftXdur, bupYdur;
    uint ucentXdur, urightXdur, uupYdur, ucentYdur, uleftXdur, yupdiff;
    char stroke;
    char *shoot, *aim;
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
        downYdur = JoyYDur;
        if (leftXdur < rightXdur && upYdur < downYdur)
        {   ucentXdur = (uint) centXdur;
            uleftXdur =  (uint) leftXdur; /*bp.0*/
            bleftXdur = uleftXdur + (uint) ((long) (ucentXdur - uleftXdur) / 2);
            urightXdur = (uint) rightXdur;
            brightXdur = ucentXdur + (uint) ((long) (urightXdur - ucentXdur) / 2);
            uupYdur = (uint) upYdur;
            ucentYdur = (uint) centYdur;
            yupdiff = ucentYdur - uupYdur;
            bupYdur = uupYdur + (uint) ((long) yupdiff / 2);
            bdownYdur = ucentYdur + (uint) ((long) ((uint) downYdur - ucentYdur) / 2);
            if (uleftXdur < bleftXdur && 
                brightXdur < urightXdur && 
                bupYdur < upYdur &&
                bdownYdur < downYdur)
                {   LC_L_RC[0] = LC_L_RC[1] = LC_L_RC[2] = bleftXdur + 1;
                    LC_L_RC[3] = LC_L_RC[7] = -1;
                    LC_L_RC[4] = LC_L_RC[5] = LC_L_RC[6] = leftXdur;
                    LC_L_RC[8] = LC_L_RC[9] = LC_L_RC[10] = brightXdur;
                    RC_LC[0] = RC_LC[1] = RC_LC[2] = brightXdur - 1;
                    RC_LC[3] = -1;
                    RC_LC[4] = RC_LC[5] = RC_LC[6] = bdownYdur;
                    RC_LC[7] = -2;
                    RC_LC[8] = RC_LC[9] = RC_LC[10] = -6;
                    UC_YCU[0] = UC_YCU[4] = UC_YCU[8] = bupYdur + 1;
                    UC_YCU[1] = UC_YCU[5] = UC_YCU[9] = bdownYdur;
                    UC_YCU[2] = UC_YCU[6] = UC_YCU[10] = upYdur;
                    UC_YCU[3] = UC_YCU[7] = -1;
                    YC_UC[0] = YC_UC[4] = YC_UC[8] = bdownYdur - 1;
                    YC_UC[1] = YC_UC[5] = YC_UC[9] = -6;
                    YC_UC[2] = YC_UC[6] = YC_UC[10] = bupYdur;
                    YC_UC[3] = YC_UC[7] = -2;
                    done = true;
                }
        }
    }
    if (!done)
    {   SetVideo(PxlClrLo);
        BiosPuts(19, 4, "Turn your joystick 90 degrees (one");
        BiosPuts(21, 4, "quarter turn), press the space bar");
        BiosPuts(23, 4, "and try again");
        wait_for_input(0, 0, "",' ');
    }
    SetVideo(PxlClrLo);
    if (!sagital)
    {   shoot = "front";
        aim = "back";
    }
    else
    {   shoot = "back";
        aim = "front";
    }
    BiosVideo(SET_CURSOR_POSITION, 0, 0, RowColl(5, 1));
    cprintf("You now shoot with the %s button", shoot);
    BiosVideo(SET_CURSOR_POSITION, 0, 0, RowColl(7, 1));
    cprintf("and aim with the %s button.", aim);
    BiosPuts(10, 9, "Press the ESC key");
    BiosVideo(SET_CURSOR_POSITION, 0, 0, RowColl(12, 1));
    cprintf("to shoot with the %s button, and", aim);
    BiosVideo(SET_CURSOR_POSITION, 0, 0, RowColl(14, 1));
    cprintf("aim with the %s button.", shoot);
    BiosPuts(17, 1, "Press the space bar to keep");
    BiosPuts(19, 1, "the buttons as they currently are.");
    stroke = '\0';
    while ((stroke != ESC && (stroke != ' '))) {
        if (Is_Keystroke() != 0) {
        stroke = (char)get_stroke();
        }
    }
    if (stroke == ESC) {
        sagital = !sagital;
    }
    BYTE_1a27_02ba = 0;
    BiosPuts(23, 14, "Saving data...");
    uleftXdur = ctrls_load_w();
    return uleftXdur;
}

lkfr_jystk()
{   /*look for joystick*/
    ;
}

prfl_jystk()
{   /*profile_joystick*/
    ;
}