#include "cw.h"          
#include "video.h"       
#include "IVT.h"         // Interrupt Vector Table-related Macros
#include "FCNTL.H"       // File control operations
#include "memory.h"

extern byte* file_buffer;

/* 
 * castle_indexize: Insert page numbers in the file buffer.
 */
void castle_indexize(void) {
    int i;
    byte *si;

    for (i = 1; i < 0x40; ++i) {
        file_buffer[i * PAGE_SZ + 0x50] = (byte)i;
    }
}

bool pcjr;

/*
 * Function: put_2_strings
 * Purpose: Displays two strings on the screen at a lines 4 and 5
 * Parameters: line4, line5
 */
void put_2_strings(char *line4, char *line5) {
    if (pcjr) {
        setVideoMode(TxtGreyWd); // Set wide text mode for PCjr
    } else {
        setVideoMode(TxtGreyThn); // Set thin text mode for other systems
    }
    BiosVideo(SET_CURSOR_POSITION, 0, 0, RowColl(4, 1)); // Position cursor
    cputs(line4); // Print first string
    cputs(line5); // Print second string
}

int d2ae, d29c; // Timing-related variables

/*
 * Function: isPcJr
 * Purpose: Detects if the system is a PCjr and sets related configuration.
 */
void isPcJr(void) {
    byte bios_pattern;
    SegMemSet(SingleStep + 1, 0x34);
    SegMemSet(SingleStep + 3, 0xff);
    if (SegmGt(0xf000, (char *)0xffff) == 0xfd) { // Check PCjr BIOS signature
        pcjr = true;
        d2ae = 900;  // Set PCjr-specific timing
        d29c = 200;
    } else {
        pcjr = false;
        d2ae = 3300; // Set non-PCjr timing
        d29c = 600;
    }
    SegMemSet(Breakpoint + 1, 0xcd); 
    SegMemSet(Breakpoint + 3, 0x13);
}

extern byte RGB_monitor;

void keyboard_config(void) {}

/*
 * Function: select_monitor (RGB or Non-RGB).
 */
void select_monitor(void) {
    byte oldRGB;
    char key;
    oldRGB = RGB_monitor; // Save current monitor type
    if (RGB_monitor == 'Y') {
        RGB_monitor = 0;
    }
    setVideoMode(4); // Set video mode for configuration screen
    print_to_position(0, 1, "The two ways in which your monitor may");
    print_to_position(0, 2, "be connected to your computer are either");
    print_to_position(0, 3, "as an RGB or a Non-RGB monitor.");
    print_to_position(0, 5, "Currently, your monitor is assumed to be");
    print_to_position(0, 6, "connected as a");
    if (RGB_monitor == 0) {
        cputs(" Non-");
    } else {
        cputs("n ");
    }
    cputs("RGB monitor.");
    print_to_position(0, 8, "If set incorrectly, the hi-resolution");
    print_to_position(0, 9, "graphic screens may appear distorted");
    print_to_position(0, 10, "and/or improperly colored.");
    print_to_position(0, 12, "Press the ESC key if you are using");
    print_to_position(0, 13, "an RGB monitor hookup.");
    print_to_position(0, 15, "Press the space bar if you are using");
    print_to_position(0, 16, "a Non-RGB monitor hookup.");
    key = '\0';
    while ((key != '\e' && (key != ' '))) { // Wait for user input
        if (IsKStrok() != 0) {
            key = GetStrok();
        }
    }
    RGB_monitor = key == '\e'; // Update monitor type based on input
    if (RGB_monitor != oldRGB) { // Save changes if monitor type changed
        print_to_position(14, 22, "Saving data...");
        ctrls_load_w();
        print_to_position(14, 22, "\t\t ");
    }
    return;
}

/*
 * Function: print_to_position
 * Parameters:
 *   - column
 *   - row
 *   - message
 */
void print_to_position(byte column, byte row, string message) {
    BiosVideo(SET_CURSOR_POSITION, 0, 0, (int)row << 8 | column);
    cputs(message);
}

bool horizontal, vertical;
byte b2ba, b4ac3[0xb], b4ace[0xb], b4ad9[0xb], b4ae4[0xb];

enum cntl_dev {DEV_undefined = -1, DEV_keyboard = 0, DEV_joystick = 1}
cntl_dev controller;

/*
 * Function: ctrls_load_r
 * Purpose: Reads control configuration from the "ctrls" file.
 */
void ctrls_load_r(void) {
    int fd;
    cputs("ctrls_load_r102\n");
    if (check_for_debugger()) { _exit(-1); } // Exit if debugger detected
    cputs("ctrls_load_r104\n");
    fd = open("ctrls", O_RAW); // Open control file
    if (fd < 0) {
        put_2_strings("Cannot open control file", "");
        _exit(-1);
    }
    cputs("ctrls_load_r111\n");
    ctrls_read(fd, &horizontal, 0l, 1); // Read control data
    ctrls_read(fd, &vertical, 1l, 1);
    ctrls_read(fd, &b2ba, 2l, 1);
    ctrls_read(fd, &RGB_monitor, 3l, 1);
    ctrls_read(fd, b4ac3, 4l, 0xb);
    ctrls_read(fd, b4ace, 0xfl, 0xb);
    ctrls_read(fd, b4ad9, 0x1al, 0xb);
    ctrls_read(fd, b4ae4, 0x25l, 0xb);
    close(fd); // Close file
}

/*
 * Function: ctrls_read
 * Purpose: Reads data from a file at a specific offset.
 * Parameters:
 *   - fd: File descriptor
 *   - buf: Buffer to store data
 *   - offset: Offset in the file
 *   - nbytes: Number of bytes to read
 * Returns: Number of bytes read
 */
int ctrls_read(int fd, byte *buf, long offset, int nbytes) {
    int length;
    lseek(fd, offset, 0); // Seek to offset
    length = read(fd, buf, nbytes); // Read data
    if (length != nbytes) {
        put_2_strings("Error reading control file!", "");
        printf("%x", offset);
        _exit(-1);
    }
    return length;
}

/*
 * Function: ctrls_write
 * Purpose: Writes data to a file at a specific offset.
 * Parameters:
 *   - ctrls: File descriptor
 *   - buffer: Data to write
 *   - offset: Offset in the file
 *   - length: Number of bytes to write
 * Returns: Number of bytes written
 */
int ctrls_write(int ctrls, string buffer, long offset, int length) {
    int nbytes;
    lseek(ctrls, offset, 0); // Seek to offset
    nbytes = write(ctrls, buffer, length); // Write data
    if (write(ctrls, buffer, length) != length) {
        cputs("Error writing control file!");
        _exit(-1);
    }
    return nbytes;
}
