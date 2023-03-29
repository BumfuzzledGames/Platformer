/***********************************************************
* A platformer game
* (C) 2023 Bumfuzzled Games <bumfuzzled.games@gmail.com>
* 
* This program is free software: you can redistribute it
* and/or modify it under the terms of the GNU General
* Public License as published by the Free Software
* Foundation, either version 3 of the License, or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be
* useful, but WITHOUT ANY WARRANTY; without even the
* implied warranty of MERCHANTABILITY or FITNESS FOR A
* PARTICULAR PURPOSE.  See the GNU General Public License
* for more details.
*
* You should have received a copy of the GNU General Public
* License along with this program.  If not, see
* <https://www.gnu.org/licenses/>.
**********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BYTES_PER_LINE 8

#define LOWER "abcdefghijklmnopqrstuvwxyz"
#define UPPER "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define NUMBER "0123456789"

FILE *open_or_die(const char *filename, const char *mode) {
    FILE *file = fopen(filename, mode);
    if (file == 0) {
        fprintf(stderr, "Could not open %s\n", filename);
        exit(EXIT_FAILURE);
    }
    return file;
}

char *string_to_identifier(const char *string) {
    char *identifier = calloc(1, strlen(string) + 1);
    for (int i = 0; i < strlen(string); i++)
        if (strchr(LOWER UPPER NUMBER, string[i]))
            identifier[i] = string[i];
        else
            identifier[i] = '_';
    return identifier;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s infile outfile", argv[0]);
        exit(EXIT_FAILURE);
    }
    FILE *in = open_or_die(argv[1], "rb");
    FILE *out = open_or_die(argv[2], "w+");
    char *in_id = string_to_identifier(argv[1]);
    
    fprintf(out, "#include <stddef.h>\n\n");
    fprintf(out, "const unsigned char %s[] = {\n", in_id);
    int bytes_on_line = 0;
    for (int c; (c = fgetc(in)) != EOF;) {
        if (bytes_on_line == 0)
            fprintf(out, "    ");
        fprintf(out, "0x%02x, ", c);
        bytes_on_line++;
        if (bytes_on_line == BYTES_PER_LINE) {
            fprintf(out, "\n");
            bytes_on_line = 0;
        }
    }
    if (bytes_on_line != 0)
        fprintf(out, "\n");
    fprintf(out, "};\n");
    fprintf(out, "const size_t %s_size = sizeof(%s);\n", in_id, in_id);
    fclose(out);
    fclose(in);
    return EXIT_SUCCESS;
}