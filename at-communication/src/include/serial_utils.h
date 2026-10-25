#ifndef SERIAL_UTILS_H
#define SERIAL_UTILS_H

#define SERIAL_MAX_READ_BYTES 64

int serial_open(char *port);
int serial_close(int fd);
int serial_write(int fd, char *buffer);
int serial_read(int fd, char *buffer, int nbytes);
int serial_flush(int fd);
int serial_configure(int fd);

#endif