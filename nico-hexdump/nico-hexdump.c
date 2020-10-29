#include <stdio.h>

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: nico-hexdump <file>\n");
        return -1;
    }

    // Try to open the file.
    FILE* fp = fopen(argv[1], "rb");
    if (fp == NULL) {
        printf("Impossible to open %s\n", argv[1]);
        return -2;
    }

    // Compute the size of the file.
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    // Read the file.
    char buffer[size];
    fread(buffer, size, 1, fp);

    // Process the file.
    int i = 0;
    int idx = 0;
    char group[16];
    for (int i = 0; i < size; i++) {
        group[idx] = buffer[i];

        if (idx == 15) {
            idx = 0;

            for (int j = 0; j < 16; j++) {
               printf("%02x ", group[j] & 0xFF); 
            }

            printf(" |");

            for (int j = 0; j < 16; j++) {
                char tmp = group[j];
                if (tmp >= 0x20 && tmp <= 0x7D) {
                    printf("%c", tmp & 0xFF);
                } else {
                    printf(".");
                } 
            }

            printf("|\n");
        } else {
            idx++;
        }

    }

    // Print the remaining bytes.
    for (int j = 0; j < idx; j++) {
        printf("%02x ", group[j] & 0xFF); 
    }

    for (int j = 0; j < (16 - idx); j++) {
        printf("   ");
    }
    printf(" |");

    for (int j = 0; j < idx; j++) {
        char tmp = group[j];
        if (tmp >= 0x21 && tmp <= 0x7D) {
            printf("%c", tmp & 0xFF);
        } else {
            printf(".");
        } 
    }

    printf("|\n");

    // Close the file.
    fclose(fp);
    return 0;
}