#include "cw.h"

#ifdef __WATCOMC__
void put_2_strings(string line4,string line5);
int load_file(string file_name, byte * dest, int length);
void ld_castle_page_w_ptr(string file_name, int size);
signed_error load_room_pg(int pagenumb);
int checked_open(string fn, int flags);
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
    byte pl_aim;
    byte bonk_timer;
    byte room_timer;
    byte s1[0x51 - 0x4e];
    byte act_timer; /*unlock time 0x51*/
    bool is_looting;
    byte par_ray_ind;
    byte s2[0x59 - 0x54];
    byte keys; /*0x59*/
    byte s3[0x6c - 0x5a];
    bool plans; /*0x6c*/
    byte rank_index; /*0x6d*/
    byte s_6e;
    byte save_status; /*0x6f*/
    byte table_4_4[4][4]; /*0x70*/
    byte s_80; /*0x80*/
    byte s4[0x87 - 0x81];
    byte s_87;
    byte s5[0xc0 - 0x88];
    byte rm_table[0x40]; /*0xc0*/
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
extern word error_encountered;


/*save status*/
#define SS_Ongoing 0
#define SS_Caught 0x40
#define SS_Suicide 0x60
#define SS_Error 0x80
#define SS_Escaped 0xFF

/* rank */
#define RNK_PRIVATE 0x10
#define RNK_CORPORAL 0x20
#define RNK_CAPTAIN 0x80
#define RNK_COLONEL 0xA0
#define RNK_GENERAL 0xC0
#define RNK_FIELD_MARSHAL 0xF0
