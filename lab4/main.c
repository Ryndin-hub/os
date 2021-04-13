#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define MAX_SIZE 10

struct line{
    char* str;
    struct line* next;
};

int readLines(struct line* first_line){
    struct line* line = first_line;
    int size = 0;
    int prev_ended = 1;
    char* str = malloc(sizeof(char) * MAX_SIZE);
    if (str == NULL){
        perror("Malloc error");
        return 1;
    }
    if (fgets(str, MAX_SIZE, stdin) == NULL) {
        perror("Error while reading");
        free(str);
        return 1;
    }
    while(str[0] != '.') {
        int len = strlen(str);
        if (prev_ended != 1){ //объединение строк
            line->str = realloc(line->str,size);
            if (line->str == NULL) {
                perror("Not enough memory for string");
                free(str);
                return 1;
            }
            int i;
            for (i = 0; i < len + 1; i++) {
                line->str[i + size] = str[i];
            }
            if (str[len-1] != '\n') {
                prev_ended = 0;
                size += len;
            } else {
                line->next = malloc(sizeof(struct line));
                if (line->next == NULL) {
                    perror("Not enough memory for new line");
                    free(str);
                    return 1;
                }
                line = line->next;
                prev_ended = 1;
                size = 0;
            }
        } else {
            line->str = malloc(sizeof(char) * (len + 1));
            if (line->str == NULL) {
                perror("Not enough memory for string");
                free(str);
                return 1;
            }
            int i;
            for (i = 0; i < len + 1; i++) {
                line->str[i] = str[i];
            }
            if (str[len-1] != '\n') {
                prev_ended = 0;
                size = len;
            } else {
                line->next = malloc(sizeof(struct line));
                if (line->next == NULL) {
                    perror("Not enough memory for new line");
                    free(str);
                    return 1;
                }
                line = line->next;
                prev_ended = 1;
            }
        }
        if (fgets(str, MAX_SIZE, stdin) == NULL) {
            perror("Error while reading");
            free(str);
            return 1;
        }
    }
    line->next = NULL;
    free(str);
    return 0;
}

int printLines(struct line* first_line){
    struct line* line = first_line;
    while(line->next != NULL){
        if (printf("%s", line->str) < 0){
            perror("Can't print");
            return 1;
        }
        line = line->next;
    }
}

int freeLines(struct line* first_line){
    struct line* line = first_line;
    while(line->next != NULL){
        struct line* next = line->next;
        free(line->str);
        free(line);
        line = next;
    }
    free(line->str);
    free(line);
    return 0;
}

int main() {
    struct line* line = malloc(sizeof(struct line));
    if (line == NULL){
        perror("Not enough memory for new line");
        return 1;
    }
    if (readLines(line) != 0){
        freeLines(line);
        return 1;
    }
    if (printLines(line) != 0){
        freeLines(line);
        return 1;
    }
    freeLines(line);
    return 0;
}
