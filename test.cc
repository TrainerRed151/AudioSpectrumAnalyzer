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

    fflush(info);
    system("rm info");
    sleep(1);


    while (1) {
        fputs("get_property time_pos\n", mp);
        fflush(mp);
        fgets(str, 55, info);
        fflush(info);

        //if (str[0] != 'A') {
        //    printf("%s\n", str);
        //    break;
        //}

        printf("%f\n", atof(str+13));
    }

    fputs("stop\n", mp);
    fclose(mp);
    
    return 0;
}
