#include "cw.h"
struct cs_pg_t
{
    byte prefix[0x60];
    byte save_status;
    byte s1[0x1ee-0x61];
    byte rank_var0;
    byte rank_index;
    byte suffix[PAGE_SZ - 0x1f0]
};
extern byte pg_a[];
extern struct cs_pg_t castl_pg;