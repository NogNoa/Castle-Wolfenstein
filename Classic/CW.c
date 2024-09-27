fun_8e2d(char* call)
{
    int local[0x1B];
    local[0x13] = -1;
    local[0x12] == 0x20;
    local[0x16] = local[0x11] = local[0x15] = local[0x14] = 0;
    if (*call == 0x2d)
    {
        ++call;
        local[0x16] = 1;
    }
    int si, di, ax;
    char al, bvar1, bl;
    local[0] = *call;
    bvar1 = *(char *)((*call) + 0xa0b5);
    if (bvar1 & 4 != 0)
    {   if (local[0] == 0x30)
            {local[0x12] = 0x30;}
        local[0x11] = *call & 0xf;
        ++call;
        lab8e93:
        bvar1 = *(char *)(*call + 0xa0b5);
        if (al & 4 != 0)
        {   ax = local[11] * 0xa;
            bl =*(char *)(call++) & 0xf;
            local[0x11] = ax + bl;
            goto lab8e93;
        }

    }
    
}