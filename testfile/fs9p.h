#ifndef FS9P_H
#define FS9P_H

#define NOTAG 0xffffU
#define NOFID 0xffffffffU

enum {
    t_version = 100,
    r_version,
    t_auth = 102,
    r_auth,
    t_attach = 104,
    r_attach,
    t_error = 106,
    r_error,
    t_flush = 108,
    r_flush,
    t_walk = 110,
    r_walk,
    t_open = 112,
    r_open,
    t_create = 114,
    r_create,
    t_read = 116,
    r_read,
    t_write = 118,
    r_write,
    t_clunk = 120,
    r_clunk,
};

// maximum length we're willing to send/receive from host
// write: 4 + 1 + 2 + 4 + 8 + 4 + 1024 = 1048

#define MAXLEN 1048

// functions for the 9p file system
typedef struct fsfile {
    uint32_t offlo;
    uint32_t offhi;
} fs_file;

// send/receive function; sends a buffer to the host
// and reads a reply back
typedef int (*sendrecv_func)(uint8_t *startbuf, uint8_t *endbuf, int maxlen);

// initialize
int fs_init(sendrecv_func fn);

// walk a file from fid "dir" along path, creating fid "newfile"
int fs_walk(fs_file *dir, fs_file *newfile, char *path);

// open a file f using path "path" (relative to root directory)
// for reading or writing
int fs_open(fs_file *f, char *path, int fs_mode);

#define FS_MODE_READ 0
#define FS_MODE_WRITE 1

// close a file
int fs_close(fs_file *f);

// read/write data
int fs_read(fs_file *f, uint8_t *buf, int count);
int fs_write(fs_file *f, uint8_t *buf, int count);

#endif
