#include "../include/serial_utils.h"
#include "argument_parser.h"

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>

int serial_open(char *port){
    if(arguments.mock){
        int mock_file = open(arguments.mock_path, O_RDONLY);
        if(mock_file < 0){
            printf("Error %i from open: %s\n", errno, strerror(errno));
            return -1;
        }
        return mock_file;
    }
    
    int serial_port = open(port, O_RDWR);
    if(serial_port < 0){
        printf("Error %i from open: %s\n", errno, strerror(errno));
        return -1;
    }
    return serial_port;
}

int serial_close(int fd){
    close(fd);
    return 0;
}

int serial_write(int fd, char *buffer){
    if(arguments.mock)
        return 0;
    int res = write(fd, buffer, strlen(buffer) * sizeof(char));
    if(arguments.debug){
        printf("> sent\n");
        if(res > 0){
            char sent[res+1];
            strncpy(sent, buffer, res);
            sent[res] = '\0';
            printf("%s", sent);
        }
        printf(">\n");
    }
    return res;
}

int serial_read(int fd, char *buffer, int nbytes){
    int res = read(fd, buffer, nbytes);
    if(res >= 0) buffer[res] = '\0';
    if(arguments.debug && res > 0){
        printf("< received\n");
        printf("%s\n", buffer);
        printf("<\n");
    }
    return res;
}

int serial_flush(int fd){
    if (tcflush(fd, TCIFLUSH) == -1) {
        perror("tcflush failed");
    }
    return 0;
}

int serial_configure(int fd){
    if(arguments.mock)
        return 0;

    struct termios tty;
    if(tcgetattr(fd, &tty) != 0){
        printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
    }

    tty.c_cflag &= ~PARENB; // clear parity bit
    tty.c_cflag &= ~CSTOPB; // one stop bit
    tty.c_cflag &= ~CSIZE; // clear data bits
    tty.c_cflag |= CS8; // 8 data bits
    tty.c_cflag &= ~CRTSCTS; // disable flow control
    tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)

    tty.c_lflag &= ~ICANON; // disable canonical input mode
    tty.c_lflag &= ~ECHO; // disable echo
    tty.c_lflag &= ~ECHOE; // disable erasure
    tty.c_lflag &= ~ECHONL; // disable new-line echo
    tty.c_lflag &= ~ISIG; // disable interpretation of INTR, QUIT and SUSP
    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
    tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes
    tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
    tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed

    tty.c_cc[VTIME] = 5;    // Wait for up to 2s, returning as soon as any data is received.
    tty.c_cc[VMIN] = 0;

    cfsetispeed(&tty, B115200);
    cfsetospeed(&tty, B115200);

    if(tcsetattr(fd, TCSANOW, &tty) != 0){
        printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
        return errno;
    }
    return 0;
}