#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NO_FILE_ERROR 1
#define CANT_OPEN_FILE_ERROR 2
#define READ_ERROR 3
#define FGETS_ERROR 4
#define READ_FAIL -1
#define REQUESTED_LINE_BUFF_SIZE 100
#define MAXIMUM_REQUEST_SIZE 10

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
    int requested_line, requested_line_size;
    char requested_line_str[REQUESTED_LINE_BUFF_SIZE];
    while(1){
        char* fgetsResult = fgets(requested_line_str, REQUESTED_LINE_BUFF_SIZE, stdin);
        if (fgetsResult == NULL){
            printf("Fgets error\n");
            exit(FGETS_ERROR);
        }
        requested_line_size = strlen(requested_line_str);
        if (requested_line_size > MAXIMUM_REQUEST_SIZE){
            printf("Input is too big\n");
            continue;
        }
        int i, second_continue = 0;
        if ((requested_line_str[0] < '0' || requested_line_str[0] > '9') && requested_line_str[0] != '-'){
            printf("Program needs a number\n");
            second_continue = 1;
        }
        if (second_continue) continue;
        for (i = 1; i < requested_line_size - 1; i++){
            if (requested_line_str[i] < '0' || requested_line_str[i] > '9'){
                printf("Program needs a number\n");
                second_continue = 1;
                break;
            }
        }
        if (second_continue) continue;
        requested_line = atoi(requested_line_str);
        if (requested_line == 0) return 0;
        if (requested_line < 0 || requested_line > num_of_lines){
            printf("Line should be between 0 and %d\n", num_of_lines);
            continue;
        }
        lseek(fd, file_offsets[requested_line], SEEK_SET);
        for (i = 0; i < file_lines_length[requested_line]; i++){
            read(fd, &c, 1);
            printf("%c", c);
        }
    }
}
