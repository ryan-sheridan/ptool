#import <libproc.h>
#import <stdio.h>
#import <string.h>
#include <unistd.h>

void listprocs();
void proc_error();
pid_t findpid(char *name);
int killproc(char *name);