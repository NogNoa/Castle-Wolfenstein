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
    byte rm_id; /*page a index 0x40*/
    byte mov_dir;
    byte aim_dir;
    byte tile_pl_rm;
    byte x_pl_rm;
    byte y_pl_rm;
    byte is_trans;
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
typedef byte page[PAGE_SZ];


typedef struct _room
{
    byte tl_tble[0x40];
    byte rm40[0x30];
    byte rm70[0x10][9];
} room;



typedef struct _castle_buffer
{
    struct cs_pg_t header;
    room rooms[0x3d];
} castle_buffer;


extern room rm_pg;
extern struct cs_pg_t cstl_pg;
extern bool isDemo;
extern byte rank_index;


#define RNK_PRIVATE 0x10
#define RNK_COLONEL 0x80
#define RNK_FIELD_MARSHAL 0xf0
