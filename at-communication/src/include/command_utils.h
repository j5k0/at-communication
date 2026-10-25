#ifndef COMMAND_UTILS_H
#define COMMAND_UTILS_H

enum CommandStatus{
    COMMAND_STATUS_OK,
    COMMAND_STATUS_TIMEOUT,
    COMMAND_STATUS_ERROR,
    __COMMAND_STATUS_MAX
};

int get_lines(int fd, char *command, double timeout, char ***response, int *count);
int get_spec_lines(char *prefix, char **lines, int line_count, char ***spec_lines, int *spec_count);
int query_command(char *command, int timeout, int attempts, char ***response, int *lines);

#endif