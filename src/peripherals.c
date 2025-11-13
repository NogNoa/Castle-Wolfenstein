#include "cw.h"
#include "video.h"

#ifdef __WATCOMC__
#include "cwa.h"
#include "conio.h"
#include "config.h"

void prflJystk(void);
#endif

extern bool isDemo;
byte joyCunfag;
bool JoyBut1, JoyBut2;

void wait_for_input(col, row, str, stop_char)
int col, row;
string str;
char stop_char;
{
    char in_char;
    int i;
    PositCPuts(row, col, str);
    in_char = (stop_char == '\0') ? 'a' : '\0';
    while (in_char != stop_char)
    {   if(!IsKstroke())
        {   if (isDemo)
            {   in_char = stop_char;
                for (i = 0; i <= 2000; ++i) {}
                i = 0;
            }
        }
        else
        {   in_char = (char) Getstroke();
            if (stop_char == '\0') {in_char = stop_char;}

        }
    }
    BiosVideo(SET_CURSOR_POSITION, 0, 0, RowColl(row, col));
    for (;str[i] != '\0';++i) {cputs(" ");}
}

byte JoyXDur, JoyYDur;
extern bool sagital;
extern byte LC_L_RC[11], RC_DC[11], UC_DC_U[11], DC_UC[11];

uint jystk_cnfg(void)
{   /*joystick config*/
    bool done = false;
    byte centXdur, centYdur, leftXdur, upYdur, rightXdur, downYdur;
    byte brightXdur, bdownYdur, bleftXdur, bupYdur;
    uint ucentXdur, urightXdur, uupYdur, ucentYdur, uleftXdur, yupdiff;
    char stroke;
    string shoot;
    string aim;
    while(!done)
    {   setVideoMode(PxlClrLo);
        PositCPuts(11, 10, "Move your joystick");
        PositCPuts(13, 10, "to the center position,");
        PositCPuts(15, 10, "and press the space bar.");
        wait_for_input(0, 0, "",' ');
        prflJystk();
        centXdur = JoyXDur;
        centYdur = JoyYDur;
        setVideoMode(PxlClrLo);
        PositCPuts(2, 1, "Move your joystick");
        PositCPuts(4, 1, "to the upper left,");
        PositCPuts(6, 1, "hold it there and");
        PositCPuts(8, 1, "press the space bar.");
        wait_for_input(0, 0, "",' ');
        prflJystk();
        leftXdur = JoyXDur;
        upYdur = JoyYDur;
        setVideoMode(PxlClrLo);
        PositCPuts(2, 20, "Move your joystick");
        PositCPuts(4, 20, "to the upper right,");
        PositCPuts(6, 20, "hold it there and");
        PositCPuts(8, 20, "press the space bar.");
        wait_for_input(0, 0, "",' ');
        prflJystk();
        rightXdur = JoyXDur;
        setVideoMode(PxlClrLo);
        PositCPuts(18, 20, "Move your joystick");
        PositCPuts(20, 20, "to the lower right,");
        PositCPuts(22, 20, "hold it there and");
        PositCPuts(24, 20, "press the space bar.");
        wait_for_input(0, 0, "",' ');
        prflJystk();
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
                    RC_DC[0] = RC_DC[1] = RC_DC[2] = brightXdur - 1;
                    RC_DC[3] = -1;
                    RC_DC[4] = RC_DC[5] = RC_DC[6] = bdownYdur;
                    RC_DC[7] = -2;
                    RC_DC[8] = RC_DC[9] = RC_DC[10] = -6;
                    UC_DC_U[0] = UC_DC_U[4] = UC_DC_U[8] = bupYdur + 1;
                    UC_DC_U[1] = UC_DC_U[5] = UC_DC_U[9] = bdownYdur;
                    UC_DC_U[2] = UC_DC_U[6] = UC_DC_U[10] = upYdur;
                    UC_DC_U[3] = UC_DC_U[7] = -1;
                    DC_UC[0] = DC_UC[4] = DC_UC[8] = bdownYdur - 1;
                    DC_UC[1] = DC_UC[5] = DC_UC[9] = -6;
                    DC_UC[2] = DC_UC[6] = DC_UC[10] = bupYdur;
                    DC_UC[3] = DC_UC[7] = -2;
                    done = true;
                }
        }
    }
    if (!done)
    {   setVideoMode(PxlClrLo);
        PositCPuts(19, 4, "Turn your joystick 90 degrees (one");
        PositCPuts(21, 4, "quarter turn), press the space bar");
        PositCPuts(23, 4, "and try again");
        wait_for_input(0, 0, "",' ');
    }
    setVideoMode(PxlClrLo);
    if (!sagital)
    {   shoot = "front";
        aim = "back";
    }
    else
    {   shoot = "back";
        aim = "front";
    }
    PositCPrintf(5, 1, "You now shoot with the %s button", shoot);
    PositCPrintf(7, 1, "and aim with the %s button.", aim);
    PositCPuts(10, 9, "Press the ESC key");
    PositCPrintf(12, 1, "to shoot with the %s button, and", aim);
    PositCPrintf(14, 1, "aim with the %s button.", shoot);
    PositCPuts(17, 1, "Press the space bar to keep");
    PositCPuts(19, 1, "the buttons as they currently are.");
    stroke = '\0';
    while ((stroke != ESC && (stroke != ' '))) {
        if (IsKstroke() != 0) {
        stroke = (char)Getstroke();
        }
    }
    if (stroke == ESC) {
        sagital = !sagital;
    }
    joyCunfag = 0;
    PositCPuts(23, 14, "Saving data...");
    uleftXdur = w_ctrls_load();
    return uleftXdur;
}

int lkfr_jystk(void)
{   /*look for joystick*/
    prflJystk();
    return JoyXDur == -1;
}
