/*
 * myar.h
 *

 */
#define AR_STRUCT_SIZE 60
#define AR_FILELEN 16

#define F_TABLE   0x01
#define F_QUICK   0x02
#define F_APPEND  0x04
#define F_XTRACT  0x08
#define F_DELETE  0x10
#define F_WAIT    0x20

#define TRUE 0
#define FALSE 1

#define STR_SIZE sizeof("rwxrwxrwx")
#define SATANPERMS S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH

#define BLKSIZE 1024

void appendFiles(const char *archive, const char *files[], int num_files);
char *file_perm_string(mode_t perm);
void print_hdr(struct ar_hdr *hdr);
int open_file(const char * filename);
void fmt_filename(const char *file, char *filename);
void build_hdr(const char *file, const struct stat *st, struct ar_hdr *hdr);
void write_hdr(int ar, struct ar_hdr *hdr);
void write_file(int ar, int fd, struct stat *st);
void stat_file(const char *filename, struct stat *st);
void append_file(int archive, const char *filename);
int open_archive(const char *archive);
void close_archive(int fd);
void append_all(const char *archive);
void print_hdr_name(struct ar_hdr *file_header);
void table(const char *archive);
void write_armag(int fd);
void read_armag(int fd);
void create_file(int fd, int name_size, struct ar_hdr *file_hdr);
void copy_file(int fd1, int fd2, size_t blk_size, long size);