#ifndef GETEVENT_H
#define GETEVENT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/input.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

char *getEvent(){
    char *commando = (char *)
    
        "grep -E 'Handlers|EV' /proc/bus/input/devices |"
        "grep -E -B1 120013 |"
        "grep -E -o event[0-9]";
    static char event[8];
    FILE *pipe = popen(commando, "r");
    if (!pipe)
        exit(1);
    fgets(event, 8, pipe);
    pclose(pipe);
    event[strlen(event) - 1] = 0x0;
    return event;
}

#endif