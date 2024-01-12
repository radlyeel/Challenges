#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <wctype.h>


void usage () {
    printf( "Usage: ccwc -clmw [file ...]\n");
}

typedef struct {
    char* data;
    long size;
} FILE_INFO;

FILE_INFO read_file(const  char*file_name) {
    FILE_INFO results;

    FILE* fp = fopen(file_name, "r");
    if (!fp) {
        fprintf(stderr, "Error: Could not open %s\n", file_name);
        exit(1);
    }
    // Ref: https://cplusplus.com/reference/cstdio/fseek/
    int err = fseek(fp, 0L, SEEK_END);
    if (err) {
        fprintf(stderr, "Error: Could not seek to end of file %s\n", file_name);
        exit(2);
    }
    long size = ftell(fp);
    if (size < 0) {
        fprintf(stderr, "Error: Could not get size of file %s\n", file_name);
        exit(2);
    }
    rewind(fp);
    char* buffer = (char*)malloc(size + 1);
    if (!buffer) {
        fprintf(stderr, "Error: Could not get memory for file %s\n", file_name);
        exit(2);
    }
    results.data = buffer;
    results.size = size;
    size_t actual = fread(buffer, 1, size, fp);
    if (actual != size) {
        fprintf(stderr, "Error: Could not read all of file %s\n", file_name);
        exit(2);
    }
    fclose(fp);
    return results;
}
    
int main (int argc, char* argv[]) {
    int  cflag, lflag, mflag, wflag, ch;

    cflag = 0;
    lflag = 0;
    mflag = 0;
    wflag = 0;
    while ((ch = getopt(argc, argv, "clmw")) != -1) {
        switch (ch) {
            case 'c':
                cflag = 1;
                break;
            case 'l':
                lflag = 1;
                break;
            case 'm':
                mflag = 1;
                break;
            case 'w':
                wflag = 1;
                break;
            case '?':
            default:
                usage();
        }
    }
    argc -= optind;
    argv += optind;
    // Output format (excerpt from 'man wc'):
    // The order of output always takes the form of 
    // line, word, byte, and file name.
    size_t bytes_total = 0;
    int lines_total = 0;
    int words_total = 0;
    for (int i = 0; i < argc; i++) {
        FILE_INFO fi = read_file(argv[i]);
        char* data = fi.data;
        size_t bytes = 0;
        int lines = 0;
        int words = 0;
        bool in_word = false;
        while (data != fi.data + fi.size) {
            if (*data == '\n' || data == fi.data + fi.size ) {
                lines++;
            }
            if ( !in_word && !iswspace(*data)) {
                in_word = true;
                words++;
            } else if (in_word && iswspace(*data)) {
                in_word = false;
            }
            bytes++;
            data++;
        }
        bytes_total += bytes;
        lines_total += lines;
        words_total += words;
        free(fi.data);
        if (lflag) {
            printf("%8d", lines);
        }
        if (wflag) {
            printf("%8d", words);
        }
        if (cflag || mflag) {
            printf("%8lu", bytes);
        }
        printf(" %s\n", argv[i]);
    }
    if (argc > 1) {
        if (lflag) {
            printf("%8d", lines_total);
        }
        if (wflag) {
            printf("%8d", words_total);
        }
        if (cflag || mflag) {
            printf("%8lu", bytes_total);
        }
        printf(" Total\n");
    }
}


