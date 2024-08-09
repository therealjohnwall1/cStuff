#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main (int argc, char** argv) {
    char* path;

    for (int i=1;i< argc;++i) {
        path = argv[i];
        FILE* file = fopen(path, "r");

        if(file == NULL) {
            printf("error %s\n", strerror(errno)); 
            printf("no work\n");
            exit(1);
        } 
        char buffer[10000];
        while (!feof(file)) {
            int bytesRead= fread(buffer, sizeof(char), 10000, file);
            fwrite(buffer, sizeof(char), bytesRead, stdout);
        }
        fclose(file);
    } 
}
