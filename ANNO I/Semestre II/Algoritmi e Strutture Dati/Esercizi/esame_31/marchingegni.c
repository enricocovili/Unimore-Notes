#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// albero binario
extern int SpringArrangementsRec(const char *record, char* current, size_t index, size_t end, int *count) {
    if (index == end) {
        printf("%s\n", current);
        *count += 1;
        return *count;
    }
    if (current[index] == '?') {
        current[index] = '.';
        SpringArrangementsRec(record, current, index+1, end, count);
        current[index] = '#';
        SpringArrangementsRec(record, current, index+1, end, count);
        current[index] = '?';
    } else {
        SpringArrangementsRec(record, current, index+1, end, count);
    }
    return *count;
}

extern int SpringArrangements(const char *record) {
    char* current = calloc(strlen(record)+1, sizeof(char));
    memmove(current, record, strlen(record));
    int count = 0;
    count = SpringArrangementsRec(record, current, 0, strlen(record), &count);
    free(current);
    return count;
}

//int main(void) {
//    int res = SpringArrangements("???.###");
//    return 0;
//}