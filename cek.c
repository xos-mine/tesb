#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void detect_libc() {
    FILE *fp;
    char buffer[256];

    // Jalankan "ldd --version" dan ambil output baris pertama
    fp = popen("ldd --version 2>&1", "r");
    if (fp == NULL) {
        printf("Tidak bisa mendeteksi libc (popen gagal)\n");
        return;
    }

    if (fgets(buffer, sizeof(buffer), fp) != NULL) {
        if (strstr(buffer, "glibc") || strstr(buffer, "GLIBC")) {
            printf("Detected: GNU C Library %s", buffer);
        } else if (strstr(buffer, "musl")) {
            printf("Detected: musl libc %s", buffer);
        } else {
            printf("Unknown libc: %s", buffer);
        }
    } else {
        printf("Tidak ada output dari ldd --version\n");
    }

    pclose(fp);
}

int main() {
    detect_libc();
    return 0;
}
