#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, const char *argv[]) {
    FILE *mp, *info;
    int i;

    system("rm info");
    system("touch info");

    mp = popen("mplayer -slave -quiet violin.wav > info", "w");

    info = fopen("info", "r");

    
    char str[55];

    for (i = 0; i < 20; i++) {
        fgets(str, 55, info);
    }


    sleep(1);

    system("rm info");

    while (1) {
        fputs("get_property time_pos\n", mp);
        fflush(mp);
        fgets(str, 55, info);
        fflush(info);
        printf("%s", str);
    }

    fputs("stop\n", mp);
    fclose(mp);
    
    return 0;
}
