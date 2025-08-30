#include "cw.h"

#ifdef __WATCOMC__
void put_2_strings(string line4,string line5);
int load_file(string file_name, byte * dest, int length);
void ld_castle_page_w_ptr(string file_name, int size);
signed_error load_room_pg(int pagenumb);
bool wait_to_return(void);
void load_demo(void);
byte rank_calculate(void);
void lack_jystk(void);
#endif

struct cs_pg_t
{
    byte prefix[0x40];
    byte pgaind; /*page a index 0x40*/
    byte s_41;
    byte s_42;
    byte s_43;
    byte s0[0x47 - 0x44];
    byte bulletCount;
    byte granadeCount;
    byte uniform;
    byte vest;
    byte s_4b;
    byte s_4c;
    byte s_4d;
    byte s1[0x51 - 0x4e];
    byte unlktm; /*unlock time 0x51*/
    byte s_52;
    byte par_ray_ind;
    byte s2[0x59 - 0x54];
    byte s_59;
    byte s3[0x6c - 0x60];
    bool plans; /*0x6c*/
    byte rank_index; /*0x6d*/
    byte s_6e;
    byte save_status; /*0x6f*/
    byte table_4_4[4][4]; /*0x70*/
    byte suffix[PAGE_SZ - 0x87];
};
struct tile
{
    byte val[8];
};
typedef struct _room
{
    struct tile val[8];
} room;


extern byte rm_pg[];
extern byte* rm_pg_70;
extern struct cs_pg_t cstl_pg;
extern bool isDemo;
extern byte rank_index;


#define RNK_PRIVATE 0x10
#define RNK_COLONEL 0x80
#define RNK_FIELD_MARSHAL 0xf0
