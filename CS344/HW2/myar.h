/*
 * Vlad Predovic
 * CS 344
 * Summer 2015
 * Header file for myar.c that intends to illustrate the of file I/O on Unix by teaching 
 * us to maintain a UNIX archive library. The program should run similar to the std UNIX command ar.
 */


//void ToC(const char *Chive, int verbosity);

#define SATANPERMS S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH
#define AR_HDR struct ar_hdr
#define AR_HSZ sizeof(AR_HDR)

char *trigger;


char *PermissionFiles(mode_t perm);
void appendFiles(const char *archive, const char *files[], int num_files);
void formatHeader(struct ar_hdr *hdr, const struct stat *st, char *fName);
void fHeader(const char *file, const struct stat *st, struct ar_hdr *hdr);
void wrFileAr(int archive, int fd, struct stat *st);
void appALL(const char *archive);
void deleteFiles(const char *Ar, const char **delFiles ,int i);
void evenLength( int fd, struct ar_hdr *file_header);
void print_archive(const char *archive, int verbs);
void print_hdr(struct ar_hdr *hdr);
int findHeader(int archFD, struct ar_hdr * headerCopy);

