#include "cw.h"
struct cs_pg_t
{
    byte prefix[0x60];
    byte save_status;
    byte s1[0x6c - 0x61];
    bool ris_rnk_twc;
    byte rank_index;
    byte suffix[PAGE_SZ - 0x6e];
};
extern byte pg_a[];
extern struct cs_pg_t castl_pg;
extern bool isDemo;