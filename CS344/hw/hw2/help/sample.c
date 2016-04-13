/*
 * myar.c

 */
#define _XOPEN_SOURCE 500
#define _BSD_SOURCE

#include <dirent.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <utime.h>

#include <ar.h>
#include "sample.h"

int verbose = FALSE;

/* Utility Functions
 *
 * Note: archive here means the path to the archive file.
 *
 *
 * find_file(fd, file) - if file in archive: return
 *   byte (start) and (end+1); if file not in archive: return -1.
 */

/* file_perm_string used from the file_stat.c example on the class website. */
char *file_perm_string(mode_t perm)
{
    /* Return ls(1)-style string for file permissions mask */
    static char str[STR_SIZE];
    snprintf(str, STR_SIZE, "%c%c%c%c%c%c%c%c%c",
             (perm & S_IRUSR) ? 'r' : '-',
             (perm & S_IWUSR) ? 'w' : '-',
             (perm & S_IXUSR) ? 'x' : '-',
             (perm & S_IRGRP) ? 'r' : '-',
             (perm & S_IWGRP) ? 'w' : '-',
             (perm & S_IXGRP) ? 'x' : '-',
             (perm & S_IROTH) ? 'r' : '-',
             (perm & S_IWOTH) ? 'w' : '-',
             (perm & S_IXOTH) ? 'x' : '-');
    return str;
}

/*
 //char  Return ls(1)-style string for file permissions mask 
filePermStr(mode_t perm, int flags)
{
static char str[STR_SIZE];
snprintf(str, STR_SIZE, "%c%c%c%c%c%c%c%c%c",
(perm & S_IRUSR) ? 'r' : '-', (perm & S_IWUSR) ? 'w' : '-', (perm & S_IXUSR) ?
(((perm & S_ISUID) && (flags & FP_SPECIAL)) ? 's' : 'x') :
(((perm & S_ISUID) && (flags & FP_SPECIAL)) ? 'S' : '-'),
(perm & S_IRGRP) ? 'r' : '-', (perm & S_IWGRP) ? 'w' : '-', (perm & S_IXGRP) ?
(((perm & S_ISGID) && (flags & FP_SPECIAL)) ? 's' : 'x') :
(((perm & S_ISGID) && (flags & FP_SPECIAL)) ? 'S' : '-'),
(perm & S_IROTH) ? 'r' : '-', (perm & S_IWOTH) ? 'w' : '-',(perm & S_IXOTH) ?
(((perm & S_ISVTX) && (flags & FP_SPECIAL)) ? 't' : 'x') :
(((perm & S_ISVTX) && (flags & FP_SPECIAL)) ? 'T' : '-'));
return str;
}
 */

/*
 * Print Header
 *
 * Prints an ar_hdr to stdout.
 */
void print_hdr(struct ar_hdr *hdr)
{
    mode_t perms;
    mode_t *ps = &perms;
    time_t date;
    char name[17];
    long uid;
    long gid;
    long size;

    char date_str[20];

    sscanf(hdr->ar_mode, "%lo", (long *) ps);
    sscanf(hdr->ar_uid, "%ld", &uid);
    sscanf(hdr->ar_gid, "%ld", &gid);
    sscanf(hdr->ar_date, "%ld", &date);
    sscanf(hdr->ar_name, "%16s", name);
    sscanf(hdr->ar_size, "%ld", &size);

    // Remove slash from filename
    char* slash = name;
    while(*slash != '/') slash++;
    *slash = 0;

    strftime(date_str, 20, "%b %d %H:%M %Y", localtime(&date));

    printf("%8s %ld/%ld %6ld %10s %-15s\n",
            file_perm_string(perms),
            uid,
            gid,
            size,
            date_str,
            name);
}












/*
 * Read ARMAG
 *
 * Read in the ARMAG from an archive.
 *
 * Used to ensure a file is actually an archive.
 */
void read_armag(int fd)
{
    char armag[SARMAG];
    if (read(fd, armag, SARMAG) == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    if (memcmp(armag, ARMAG, SARMAG) == -1) {
        fprintf(stderr, "Aborting: Not a valid archive file.\n");
        exit(EXIT_FAILURE);
    }
}





/*
 * given a ar filename, return a fd for the ar.
 *   Check to ensure fd is valid, and use perror to output failure. Also
 *   contains an optional argument to create the archive if it doesn't
 *   exist.
 *   - This may return a struct containing the file and stat of file...
 *     operation will most likely need the size...
 */
int open_archive(const char *archive)
{
    int fd;

    if ((fd = open(archive, O_RDONLY)) == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    read_armag(fd);

    return fd;
}

/*
 * close_archive(fd) - closes the archive at the given fd, checks result
 *   to make sure no errors given. If errors, perror and fail
 */
void close_archive(int fd)
{
    if(close(fd) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }
}

/* Append all regular files 
 * 
 * get list of regular files in current directory (except archive
 *   itself)
 *  - uses stat and checks file type
 * pass list to 'quick append' function
 *
 */
void append_all(const char *archive)
{
    char **files;
    DIR *dir;
    struct dirent *ed;
    int nfiles = 0;

    char *dirname = ".";

    if ((dir = opendir(dirname)) == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    files = (char **) malloc( sizeof(char *) * 50);

    while ((ed = readdir(dir)) != NULL) {
        if(ed->d_type == DT_REG && strcmp(ed->d_name, archive) != 0) {
            files[nfiles++] = ed->d_name;
        }
    }

    closedir(dir);
    
    appendFiles(archive, (const char **)files, nfiles);
    free(files);
}






/*
 * Print Header Name
 *
 * Prints the ar_name of a ar_hdr.
 */
int hdr_name_size(struct ar_hdr *file_header)
{
    int i = 0;
    while(file_header->ar_name[i] != '/') {
        ++i;
    }
    return i;
}

/*
 * Table
 *
 * Open archive file
 * byte = size of ar header +1
 * while not at end of file
 *   read in till size of ar_struct as ar_struct (60 chars)
 *   if verbose print all file info
 *   else print ar_struct.name
 *   seek to ar_struct.size (+1 ?)
 *   set bytes to current position
 * close archive
 *
 */
void table(const char *archive)
{
    int name_size;
    int fd;
    int size;
    ssize_t buf;
    struct ar_hdr file_header;

    fd = open_archive(archive);

    while((buf = read(fd, &file_header, AR_STRUCT_SIZE)) == AR_STRUCT_SIZE) {
        size = 0;

        if (buf == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        if (memcmp(file_header.ar_fmag, ARFMAG, 2) != 0) {
            fprintf(stderr, "Bad read.\n");
            exit(EXIT_FAILURE);
        }

        if(verbose == TRUE) {
            print_hdr(&file_header);
        } else {
            name_size = hdr_name_size(&file_header);
            printf("%.*s\n", name_size, file_header.ar_name);
        }

        if ((size = strtol(file_header.ar_size, (char **)NULL, 10)) == LONG_MIN
                || size == LONG_MAX)
        {
            perror("strtol");
            exit(EXIT_FAILURE);
        }

        /* Compensate for '\n' when the file length is even */
        if ((size % 2) == 1) {
            size++;
        }

        if (lseek(fd, size, SEEK_CUR) == -1) {
            perror("lseek");
            exit(EXIT_FAILURE);
        }
    }

    close_archive(fd);
}


/*
 * Copy File
 *
 * Copy at most bytes from one file to another in blockSize chunks.
 *
 */
void copy_file(int fd1, int fd2, size_t blockSize, long size)
{
    int i = 0;
    char* buf[blockSize];
    ssize_t b_read;

    while ((i < size) && (b_read = read(fd1, buf, blockSize)) != 0) {
        if (b_read == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        if ((write(fd2, buf, b_read)) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }
        i += b_read;
    }
}

/* Delete
 *
 * Open archive
 * while not at end of file
 *   read in files until reaching one where ar_struct.name is same as
 *   filename; break
 * (pointer should be at beginning of file now. file can be copied by
 *  copying bytes up to size of file [from ar_struct.size])
 * if not found, fail
 * create a new archive file
 * copy bytes of first file to new file
 * unlink original archive
 * close archive
 *
 * prints 'd - Filename' in verbose mode 
 */
/*
void delete(const char *archive, const char* files[], int num_files) {
    ;
}
*/

/* Extract
 * 
 * open archive
 *   while not at end of file
 *     read in headers, skip file content,  until reaching one where
 *     ar_struct.name is same as one of filenames
 *       add filename to list of filenames already found
 *       (pointer should be at beginning of file now. file can be copied by
 *        copying bytes up to size of file [from ar_struct.size])
 *       open and create a new file with name of file asked for, along with
 *         file stats from archive file
 *       copy bytes from archive to file
 *       close file; 
 *   if length of filenames handled not same as filenames requested continue,
 *   else close archive and fail, since we did find any files
 * close archive
 *
 * prints 'x - Filename' in verbose mode
 */
/*
void extract(const char *archive, const char* files[], int num_files)
{
    int fd;
    ssize_t buf;
    struct ar_hdr file_header;
    const char *file;
    int size;
    fd = open_archive(archive);
    while((buf = read(fd, &file_header, AR_STRUCT_SIZE)) == AR_STRUCT_SIZE) {
        if (buf == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        if (memcmp(file_header.ar_fmag, ARFMAG, 2) != 0) {
            //printf("%60s", (char *)&file_header);
            fprintf(stderr, "Bad read.\n");
            exit(EXIT_FAILURE);
        }
        for(int i = 0; i < num_files; i++) {
            file = files[i];
            int hdr_size = hdr_name_size(&file_header);
            //printf("%s\n", file);
            //printf("%.*s %s %ld\n", hdr_size, file_header.ar_name, file, (long) hdr_size);
            if(memcmp(file_header.ar_name, file, (size_t) hdr_size) == 0) {
                //printf("FOUND\n");
                create_file(fd, (int) hdr_size, &file_header);
            } else {
                if ((size = strtol(file_header.ar_size, (char **)NULL, 10)) == LONG_MIN
                        || size == LONG_MAX)
                {
                    perror("strtol");
                    exit(EXIT_FAILURE);
                }
                //printf("NOTFOUND: %ld\n", (long) size);
                if ((size % 2) == 1) {
                    size++;
                }
                if (lseek(fd, size, SEEK_CUR) == -1) {
                    perror("lseek");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
    close_archive(fd);
}
*/

/*
 * Create File
 *
 * Create a new file with the properties from file_header
 *
 */
/*
void create_file(int fd, int name_size, struct ar_hdr *file_hdr)
{
    //int new_file;
    char filename[name_size];
    long size;
    struct utimbuf utime_bufs = { 
        .actime = (time_t) file_hdr->ar_date,
        .modtime = (time_t) file_hdr->ar_date
    };
    snprintf(file_hdr->ar_name, name_size, "%s", filename);
    //printf("%s", filename);
    if((new_file = open(file_hdr->ar_name, O_WRONLY | O_APPEND | O_CREAT,
                       file_hdr->ar_mode)) == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    sscanf(file_hdr->ar_size, "%ld", &size);
    copy_file(fd, new_file, BLKSIZE, size);
    utime(file_hdr->ar_name, &utime_bufs);
}
*/




/*
 * Write File
 *
 * Write a file to another while keeping even offsets.
 */
void wrFileAr(int ar, int fd, struct stat *st)
{
    ssize_t b_read;
    long blockSize = (long) st->st_blksize;
    long file_size = (long) st->st_size;
    char* buf[blockSize];

    /* read chars from filename into a buffer */
    while((b_read = read(fd, buf, blockSize)) != 0) {
        write(ar, buf, b_read);    
    }

    /* Add a newline if odd length file. */
    if((file_size % 2) == 1) { (write(ar, "\n", 1));  }
}

void buildHeader(struct ar_hdr *hdr, const struct stat *st, char *fName)
{
	sprintf(hdr->ar_name, "%-16s", fName);
    sprintf(hdr->ar_date, "%-12ld", (long) st->st_mtime);
    sprintf(hdr->ar_uid, "%-6ld", (long) st->st_uid);
    sprintf(hdr->ar_gid, "%-6ld", (long) st->st_gid);
    sprintf(hdr->ar_mode, "%-8lo", (unsigned long) st->st_mode);
    sprintf(hdr->ar_size, "%-10lld", (long long) st->st_size);
    memcpy(hdr->ar_fmag, ARFMAG, 2);
}





/*
 * Build Header
 *
 * Constructs the ar header for a file.
 *
 * Takes the file metadata from stat and puts it into an ar_hdr
 *   struct. Returns the preferred blksize for writing the file.
 */
void fHeader(const char *file, const struct stat *st, struct ar_hdr *hdr)
{
    char filename[16];
    int i = 0;
    while(i < strlen(file)) {			//Use strcpy instead..
        filename[i] = file[i];
        i++;
    }
    filename[i++] = '/';
    while(i < 16) {
        filename[i++] = ' ';
    }
	
	buildHeader(hdr, st, filename);
	

}


/* Quick Append
 *
 * open archive
 * for each file name
 *   open file
 *   write ar header for file to archive
 *   write file to archive
 *   close file
 * close archive
 *
 */
void appendFiles(const char *archive, const char *files[], int num_files)
{
    int fd;				//for archive
	int fd1;			//for files
    struct stat st;					//To keep all the info for the header
    struct ar_hdr file_hdr;	
	
	//Create the archive and append files. If archive exists, just append.
    fd = open(archive, O_APPEND | O_WRONLY| O_CREAT, SATANPERMS); 
	
	
	write(fd, "!<arch>\n", 8);	//Writes header of archive file for UNIX into the new archive.(Check how to make so not always?)	
	
	
	
    for (int i = 0; i < num_files; i++) {
		fd1 = open(files[i], O_RDONLY);			//link selected file using fd1
	    stat(files[i], &st);					//Get info into stat struct from fd1
	    fHeader(files[i], &st, &file_hdr);	//build header for file in archive
		write(fd, &file_hdr, 60);				//write header into archive
		wrFileAr(fd, fd1, &st);				//write file into archive
    }		

    close(fd);
}



/*
 * myar is an simple implementation of the UNIX archive (ar) program.
 *  It is design to create archives, extract files, delete files, and add
 *  files to an archive.
 */
int main(int argc, char *argv[])
{	
	int verbosity = 0;
    int option = 0;
	int setOpt = 0;
    short flags = 0;
    const char *theArchive;
    const char *files[argc];

    while ((option = getopt(argc, argv, "Adqtvw:x")) != -1) {
        switch (option) {
        case 'q':
            // append named files to archive
            setOpt = 1;
            break;
        case 'x':
            //extract named files from archive
            setOpt = 2;
            break;
		case 't':
            //print a concise table of contents of archive
            setOpt = 3;
            break;
        case 'v':
            //if specified with t, print a verbose table of contents of archive
            verbose = TRUE;
            break;
        case 'd':
            // delete named files from archive
            flags |= F_DELETE;
            break;
        case 'A':
            //Append all regular files in current directory
            setOpt = 6;
            break;
        case 'w':
            //Extra credit: for a given time-out, add all modified files to archive.
            flags |= F_WAIT;
            break;

        default:
			printf("error, invalid input");
			exit(EXIT_FAILURE);
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "Expected argument after options\n");
        exit(EXIT_FAILURE);
    }

/*     if (flags == 0) {
        fprintf(stderr, "At least one non-verbose option required.\n");
        exit(EXIT_FAILURE);
    } */

    theArchive = argv[optind++];
    if (setOpt == 3) {
        table(theArchive);
    } else if (setOpt == 6) {
        append_all(theArchive);
    } else {
        int i = 0;
        while (optind < argc) {
            files[i++] = argv[optind++];
        }

        if (optind < 4) {
            fprintf(stderr, "At least one file required for appending, "
                            "extracting or deleting.\n");
            exit(EXIT_FAILURE);
        }

        if (setOpt == 1) {
            appendFiles(theArchive, files, i);
        } else {
            fprintf(stderr, "Option not supported yet.\n");
            exit(EXIT_FAILURE);
        }
    }
    exit(EXIT_SUCCESS);
}