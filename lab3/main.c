#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

int main(int argc, char **argv) {
    FILE *file;
    int print_e = printf("Real user id: %d\nEffective user id: %d\n", getuid(), geteuid());
    if (print_e < 0){
        perror("Can't print");
        exit(1);
    }

    file = fopen("test", "r");
    if (file == NULL){
        perror("Can't open file");
        exit(0);
    } else {
        print_e = printf("File opened\n");
        if (print_e < 0){
            perror("Can't print");
            exit(1);
        }
        fclose(file);
    }

    if (seteuid(getuid()) == -1){
        perror("Can't change effective user id");
        return 0;
    }

    print_e = printf("Real user id: %d\nEffective user id: %d\n", getuid(), geteuid());
    if (print_e < 0){
        perror("Can't print");
        exit(1);
    }

    file = fopen("test", "r");
    if (file == NULL){
        perror("Can't open file");
        exit(0);
    } else {
        print_e = printf("File opened\n");
        if (print_e < 0){
            perror("Can't print");
            exit(1);
        }
        fclose(file);
    }

    return 0;
}
