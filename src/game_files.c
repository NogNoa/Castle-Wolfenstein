#include "cw.h"
#include "files.h"
#include "video.h"
#include "game_f~1.h"

byte prewrite_buffer[PAGE_SZ];
char file_buffer[0x3ff4];
byte *ptr_file_buffer = file_buffer;
byte rank_index;

int checked_open(fn, flags)
string fn;
int flags;
{   int fildsc;
    fildsc = open(fn, flags);
    if (fildsc < 0) 
    {   put_2_strings("Cannot open ", fn);
        _exit(-1);
    }
    return fildsc;
}

start_menu()
{
    char c;
    rank_print();
    BiosVideo(0x200, 0, 0, RowColl(7, 1));
    cputs("Press:");
    BiosVideo(0x200, 0, 0, RowColl(9, 6));
    cputs("Ctrl-N To create a new");
    BiosVideo(0x200, 0, 0, RowColl(10, 13));
    cputs("castle map only.");
    BiosVideo(0x200, 0, 0, RowColl(11, 13));
    cputs("(Saving your rank)");
    BiosVideo(0x200, 0, 0, RowColl(13, 6));
    cputs("Ctrl-R To create a new");
    BiosVideo(0x200, 0, 0, RowColl(14, 13));
    cputs("castle map and");
    BiosVideo(0x200, 0, 0, RowColl(15, 13));
    cputs("reset your rank to");
    BiosVideo(0x200, 0, 0, RowColl(16, 13));
    cputs("Private.");
    BiosVideo(0x200, 0, 0, RowColl(18, 6));
    cputs("ENTER to do nothing.");
    while (true)
    {
        while (!IsKStrok());
        c = GetStrok();
        if (c == CTRL('R'))
        {   rank_index = RNK_PRIVATE;
            cstl_pg.save_status = 0xff;
        }
        else if (c == CTRL('N'))
        {   cstl_pg.save_status = 0xff;

        }
        else if (c != '\r')
        {
            continue;
        }
        break;
    }
}

reverse_control()
{
    char c;
    setVideo(PxlClrLo);
    BiosVideo(0x200, 0, 0, RowColl(9, 2));
    cputs("What controls do you wish to adjust ?");
    BiosVideo(0x200, 0, 0, RowColl(11, 2));
    cputs("Press: K to adjust keyboard controls");
    BiosVideo(0x200, 0, 0, RowColl(13, 9));
    cputs("J to adjust joystick controls");
    while (true)
    {   while (!IsKStrok());
        c = GetStrok();
        if ((c | 0x20) == 'k')
        {   kb_cnfg();}
        else if ((c | 0x20) == 'j')
        {   /*if (lkfr_jystk() == 0)
                {jystk_cnfg();}
            else
                {lack_jystk();}
            */
        }
        else
            {continue;}
        break;
    }
}

resume_castle(/*void*/)
{
    setVideoMode(PxlClrLo);
    BiosVideo(SET_CURSOR_POSITION, 0, 0, RowColl(13, 6));
    cputs("Resuming where you left off...");
}

char pg_a[PAGE_SZ];
struct cs_pg_t cstl_pg;

ld_castle_page_w_ptr(filename, length)
string filename;
{
    int i;
    byte *cstl;
    cstl = (byte *) &cstl_pg;
    load_file(filename, file_buffer, length);
    for (i=0; i < PAGE_SZ; ++i)
    {   cstl[i] = ptr_file_buffer[i];
    }
}

write_to_file(file_name)
char* file_name;
{
    int fildsc, i;
    ptr_file_buffer = file_buffer;
    for (i=0; i < PAGE_SZ; ++i) 
        {ptr_file_buffer[i] = prewrite_buffer[i];}
    fildsc = checked_open(file_name, 0x8001);
    if (write(fildsc, file_buffer, 0x3ff4) < 0)
    {    put_2_strings("Error writing file ", file_name);
        _exit(-1);
    }
    close(fildsc);
}

string rank_table[8] = {
    "Private",
    "Corporal",
    "Sergeant",
    "Lieutenant",
    "Captain",
    "Colonel",
    "General",
    "Field Marshal"
};
rank_print()
{
    setVideoMode(PxlClrLo);
    BiosVideo(SET_CURSOR_POSITION, 0, 0, RowColl(2, 1));
    cputs("Your Rank is ");
    cputs(rank_table[rank_index >> 5]);
    printf("\n rank index: 0x%x\n shifted: %x\n rank: %s",
           rank_index, rank_index >> 5, rank_table[rank_index >> 5]);
    return;
}

signed_error load_page_a(pagenumb)
int pagenumb;
{
    int i;
    if ((0 < pagenumb) && (pagenumb < 0x3d))
    {   pagenumb <<= 8;
        for (i=0; i < PAGE_SZ; ++i)
            {pg_a[i] = file_buffer[pagenumb++];}
        return 0;
    }
    else {return -1;}
}

byte rank_calculate()
{
    bool cont;
    printf(" save status:%x\n rank_index: %x\n rise rank twice: %x\n"
    ,cstl_pg.save_status, cstl_pg.rank_index, cstl_pg.ris_rnk_twc);
    if (cstl_pg.save_status < 0x80)
    {   if (1 < cstl_pg.save_status)
            {--cstl_pg.rank_index;}
    }
    else
    {   do
        {   if (RNK_FIELD_MARSHAL <= cstl_pg.rank_index) {break;}
            cstl_pg.rank_index += 0x10;
            cont = cstl_pg.ris_rnk_twc;
            cstl_pg.ris_rnk_twc = false;
        } while (cont);
        if (RNK_FIELD_MARSHAL < cstl_pg.rank_index) 
            {cstl_pg.rank_index = RNK_FIELD_MARSHAL;}
    }
    if (cstl_pg.rank_index < RNK_PRIVATE)
        {cstl_pg.rank_index = RNK_PRIVATE;}
    printf("rank index: %x\n", cstl_pg.rank_index);
    return cstl_pg.rank_index;
}

/*void*/
castle_indexize(/*void*/)
{
    int i;

    for (i=1; i < 0x40; ++i)
      {file_buffer[i * PAGE_SZ + 0x50] = (byte) i;}
}

bool pcjr;

put_2_strings(line4, line5)
string line4, *line5;
{   
    if (pcjr) {setVideoMode(TxtGreyWd);}
    else {setVideoMode(TxtGreyThn);}
    BiosVideo(SET_CURSOR_POSITION, 0, 0, RowColl(4,1));
    cputs(line4);
    cputs(line5);
}

word dmodt_offset, ind29a;
bool isDemo = false;
byte dmodt_buffer[DEMODT_FSIZE];
extern bool horizontal;

load_demo()
{
    byte *gfx_buffer;
    file_to_screen(2);
    ld_castle_page_w_ptr("demofile", CASTLE_FSIZE);
    load_file("demodata", dmodt_buffer, DEMODT_FSIZE);
    isDemo = true;
    horizontal = false;
    gfx_buffer = dmodt_buffer + 1000;
    dmodt_offset = 0;
    ind29a = 0;
    GfxFileP = gfx_buffer;
    load_page_a(1);
}

word error_encountered;

bool wait_to_return()
{
    long limit, li;
    if (error_encountered) {return 1;}
    if (!pcjr) {limit = 119000l;}
    else {limit = 56000l;}
    for (li=0;li <= limit;++li)
    {   if (IsKStrok())
        {   if (GetStrok() == '\r')
                {return false;}
        }
    }
    return true;
}

load_file(file_name, dest, length)
string file_name;
byte *dest;
int length;
{
    int fildsc, status;
    isDos210();
    if (Goober(0x23, dest) > 0) {_exit(-1);}
    fildsc = status = checked_open(file_name, 0x8000);
    if (-1 < read(fildsc, dest, length))
    {   status = close(fildsc);
        return status;    
    }  
    put_2_strings("Error reading ", file_name);
    if (fildsc > -1) {close(fildsc);}
    _exit(-1);
}


lack_jystk()
{   /*lack_of joystick*/
    ;
}

int d2ae, d29c;

isPcJr()
{
  byte bios_pattern;
  /*
  SegMemSet(SingleStep+1, 0x34);
  SegMemSet(SingleStep+3, 0xff);
  */
  if (SegmGt(0xf000, (byte *)0xffff) == 0xfd) /* from the PC Jr BIOS*/
  { pcjr = true;
    d2ae = 900;
    d29c = 200;
  }
  else
  { pcjr = false;
    d2ae = 3300;
    d29c = 600;
  }
  /*
  SegMemSet(Breakpoint+1, 0xcd);
  SegMemSet(Breakpoint+3, 0x13);
  */
}