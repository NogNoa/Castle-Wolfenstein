#include "cw.h"

#ifdef __WATCOMC__
void put_2_strings(string line4,string line5);
int load_file(string file_name, byte * dest, int length);
void ld_castle_page_w_ptr(string file_name, int size);
signed_error load_page_a(int pagenumb);
bool wait_to_return(void);
void load_demo(void);
byte rank_calculate(void);
void lack_jystk(void);
#endif

struct cs_pg_t
{
    byte prefix[0x40];
    byte pgaind; /*0x40*/
    byte s0[0x60 - 0x41];
    byte save_status; /*0x60*/
    byte s1[0x6c - 0x61];
    bool ris_rnk_twc; /*0x6c*/
    byte rank_index; /*0x6d*/
    byte suffix[PAGE_SZ - 0x6e];
};
extern byte pg_a[];
extern struct cs_pg_t cstl_pg;
extern bool isDemo;

#define RNK_PRIVATE 0x10
#define RNK_COLONEL 0x80
#define RNK_FIELD_MARSHAL 0xf0
