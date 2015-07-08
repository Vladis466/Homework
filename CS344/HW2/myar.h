/*
 * Vlad Predovic
 * CS 344
 * Summer 2015
 * Header file for myar.c that intends to illustrate the of file I/O on Unix by teaching 
 * us to maintain a UNIX archive library. The program should run similar to the std UNIX command ar.
 */
 

void appendFiles(const char *archive, const char *files[], int num_files);
void buildHeader(struct ar_hdr *hdr, const struct stat *st, char *fName);
void fHeader(const char *file, const struct stat *st, struct ar_hdr *hdr);

void ToC(char *archive, int verbosity);