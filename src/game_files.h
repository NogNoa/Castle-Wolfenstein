struct cs_pg_t
{
    byte prefix[0x60];
    byte save_status;
    byte suffix[PAGE_SZ-0x61];
};
extern byte pg_a[];
extern struct cs_pg_t castl_pg;