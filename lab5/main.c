#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define NO_FILE_ERROR 1
#define CANT_OPEN_FILE_ERROR 2
#define READ_ERROR 3
#define READ_FAIL -1

int main(int argc, char *argv[]) {
    if (argc < 2){
        printf("No file given\n");
        exit(NO_FILE_ERROR);
    }
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1){
        perror("Cant open file");
        exit(CANT_OPEN_FILE_ERROR);
    }
    char c;
    int num_of_lines = 0, read_result;
    read_result = read(fd, &c, 1);
    while(read_result != 0){
        if (read_result == READ_FAIL){
            perror("Error while reading");
            exit(READ_ERROR);
        }
        if (c == '\n'){
            num_of_lines++;
        }
        read_result = read(fd, &c, 1);
    }
    lseek(fd, 0, SEEK_SET);
    int line_length = 0, line_num = 0;
    int file_lines_length[num_of_lines], file_offsets[num_of_lines];
    file_offsets[1] = 0;
    read_result = read(fd, &c, 1);
    while(read_result != 0){
        if (read_result == READ_FAIL){
            perror("Error while reading");
            exit(READ_ERROR);
        }
        if (c == '\n'){
            line_length++;
            line_num++;
            file_lines_length[line_num] = line_length;
            file_offsets[line_num+1] = lseek(fd, 0, SEEK_CUR);
            line_length = 0;
        } else {
            line_length++;
        }
        read_result = read(fd, &c, 1);
    }
    int requested_line;
    while(scanf("%d", &requested_line)){
        if (requested_line == 0) return 0;
        if (requested_line < 0 || requested_line > num_of_lines){
            printf("Line should be between 0 and %d\n", num_of_lines);
            continue;
        }
        lseek(fd, file_offsets[requested_line], SEEK_SET);
        int i;
        for (i = 0; i < file_lines_length[requested_line]; i++){
            read(fd, &c, 1);
            printf("%c", c);
        }
    }
}
