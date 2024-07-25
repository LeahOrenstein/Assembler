#include "testing.h"


#include <ctype.h>

int compareFiles(const char* file1, const char* file2) {
    FILE *f1, *f2;
    char line1[MAX_LINE_LENGTH], line2[MAX_LINE_LENGTH];
    char *trimmed1, *trimmed2;

    f1 = fopen(file1, "r");
    f2 = fopen(file2, "r");

    if (f1 == NULL || f2 == NULL) {
        if (f1) fclose(f1);
        if (f2) fclose(f2);
        return -1;  /* Error opening files */
    }

    while (1) {
        /* Read non-empty lines from both files */
        do {
            if (!fgets(line1, sizeof(line1), f1)) {
                line1[0] = '\0';  /* Mark end of file */
                break;
            }
            trimmed1 = line1;
            while (isspace((unsigned char)*trimmed1)) trimmed1++;
        } while (*trimmed1 == '\0');

        do {
            if (!fgets(line2, sizeof(line2), f2)) {
                line2[0] = '\0';  /* Mark end of file */
                break;
            }
            trimmed2 = line2;
            while (isspace((unsigned char)*trimmed2)) trimmed2++;
        } while (*trimmed2 == '\0');

        /* If both files have ended, they are identical */
        if (*trimmed1 == '\0' && *trimmed2 == '\0') {
            fclose(f1);
            fclose(f2);
            return 1;  /* Files are identical */
        }

        /* If one file ended before the other, or lines are different */
        if (strcmp(trimmed1, trimmed2) != 0) {
            fclose(f1);
            fclose(f2);
            return 0;  /* Files are different */
        }
    }
    return 1;
}


void printDifferences(const char* file1, const char* file2) {
    FILE *f1, *f2;
    char line1[MAX_LINE_LENGTH], line2[MAX_LINE_LENGTH];
    int lineNum = 0, i;

    f1 = fopen(file1, "r");
    f2 = fopen(file2, "r");

    if (f1 == NULL || f2 == NULL) {
        printf("Error opening files for comparison.\n");
        return;
    }

    while (fgets(line1, sizeof(line1), f1) && fgets(line2, sizeof(line2), f2)) {
        lineNum++;
        if (strcmp(line1, line2) != 0) {
            printf("Difference in line %d:\n", lineNum);
            printf("File 1: ");
            for (i = 0; line1[i] && line1[i] != '\n'; i++) {
                if (line1[i] == '\t') printf("\\t");
                else if (line1[i] == ' ') printf("_");
                else printf("%c", line1[i]);
            }
            printf("\nFile 2: ");
            for (i = 0; line2[i] && line2[i] != '\n'; i++) {
                if (line2[i] == '\t') printf("\\t");
                else if (line2[i] == ' ') printf("_");
                else printf("%c", line2[i]);
            }
            printf("\n\n");
        }
    }

    fclose(f1);
    fclose(f2);
}
