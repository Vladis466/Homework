#ifndef _MISC_
#define _MISC_
#define WIN_W 32
#define WIN_H 64
#define BLK_W 16
#define BLK_H 24
#define BLK_S_W 8
#define BLK_S_H 8
#define CEL_W 8
#define CEL_H 8
#define BIN_S 9
#define NEG_POS_R 7


char* getfolder(const char* filename, char* folder);
char* getestension(const char* filename);
void TraceTime();
#endif