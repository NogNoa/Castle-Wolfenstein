#include "cw.h"
#include "init.h"

int drcltb[11] = {
     0,  0,  0, 0,
    -1, -1, -1, 0,
     1,  1,  1
};
int drrwtb[11] = {
    0, 1, -1, 0,
    0, 1, -1, 0,
    0, 1, -1
};

uint in_front(position, direction)
uint position;int direction;
{
    get_crdinats(position);
    col_row2b2.col += drcltb[direction]; 
    col_row2b2.row += drrwtb[direction];
    position = (byte) col_row2b2.row << 3 | (col_row2b2.col & 7);
    return position;
}
