#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    FILE *fp = fopen("fprintf_output.txt", "w");
    if (!fp) {
        perror("fopen");
        exit(1);
    }

    clock_t start = clock();

    for (int i = 0; i < 1000000; i++) {
        fprintf(fp, "a");  // 写到用户态缓冲区
    }

    fclose(fp); // flush + close

    clock_t end = clock();
    printf("fprintf: %.3f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
    return 0;
}
