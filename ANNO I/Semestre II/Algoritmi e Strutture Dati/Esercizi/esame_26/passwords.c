//
// Created by enri on 5/29/24.
//

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

extern bool isValid(const char* str, int n) {
    for (size_t i = 0; i < n-1; ++i) {
        if (str[i] == str[i+1])
            return true;
    }
    return false;
}

extern void PasswordsRec(int n, int i, char* current, int *count) {
    if (i == n){
        if (isValid(current, n)) {
            (*count)++;
            printf("%d) %s\n", *count, current);
        }
        return;
    }
    for (char j = '0'; j < (char)('0'+10); j++) {
        if (current[i-1] > j)
            continue;
        current[i] = j;
        PasswordsRec(n, i+1, current, count);
    }
}

extern void Passwords(int n) {
    if (n < 2)
        return;
    int count = 0;
    char* str = malloc(sizeof(char)*n+1);
    for (char i = '0'; i < (char)('0'+10); i++) {
        for (size_t j=0; j<n; j++) {
            str[j] = '0';
        }
        str[0] = i;
        str[n] = '\0';
        PasswordsRec(n, 1, str, &count);
    }
    free(str);
}

//int main(void) {
//    Passwords(2);
//    return 0;
//}