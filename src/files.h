#define CHR_FSIZE 0x400
#define MSG_FSIZE 0x4b0
#define DEMODT_FSIZE 5000
#define GFX_BSIZE 4000
#define VOCAB_FSIZE 0x2bd0
#define CASTLE_FSIZE 0x3ff4
#define PIX_FSIZE 0x4000
#define FBUF_SIZE 0x4100

extern char file_buffer[FBUF_SIZE];
extern byte* ptr_file_buffer;
extern byte* GfxFileP;
extern struct {
    byte f0[500];
    byte f1[500];
    byte gfx_buffer[GFX_BSIZE];
}   dmodt_buffer;
