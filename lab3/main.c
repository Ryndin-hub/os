#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

int main(int argc, char **argv) {
    FILE *file;
    printf("Real user id: %d\nEffective user id: %d\n", getuid(), geteuid());

    file = fopen("test", "r");
    if (file == NULL){
        perror("Can't open file");
        exit(1);
    } else {
        printf("File opened\n");
        fclose(file);
    }

    if (seteuid(getuid()) == -1){
        perror("Can't change effective user id");
        exit(1);
    }

    printf("Real user id: %d\nEffective user id: %d\n", getuid(), geteuid());

    file = fopen("test", "r");  
    if (file == NULL){
        perror("Can't open file");
        exit(1);
    } else {
        printf("File opened\n");
        fclose(file);
    }

    exit(0);
}
