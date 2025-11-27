//
// Created by enri on 6/5/24.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern void PasswordRec(const char *str, int len, int n,
                       char *curr, int level,
                       int *tot) {
    if (level == n) {
        printf("%s\n", curr);
        *tot += 1;
        return;
    }
    for (int i = 0; i < len; i++) {
        curr[level] = str[i];
        PasswordRec(str, len, n, curr, level+1, tot);
    }
}


extern int Password(const char *str, int n) {
    if (str == NULL)
        return 0;
    int len = (int)strlen(str);
    int tot = 0;
    char *curr = calloc(n+1, sizeof(char));
    PasswordRec(str, len, n, curr, 0, &tot);
    free(curr);
    return tot;
}

//
//int main() {
//    Password("a1", 2);
//}
