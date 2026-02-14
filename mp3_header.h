    #ifndef MP3_HEADER_H
    #define MP3_HEADER_H

    #include <stdio.h>
    #include <string.h>

    #define VIEW 	1
    #define EDIT 	2


    struct MP3
    {
        char *mp3_filename;
        FILE *org_mp3_fptr;
        FILE *dup_mp3_fptr;
        char given_tag[5];
    };

    int validate_cla(int argc, char *argv[], struct MP3 *mp3);
    void view(struct MP3 *mp3);
    void edit(struct MP3 *mp3,char *argv[],int argc);
    void toggle_endianess(struct MP3 *mp3, int *size);
    void print_tag_data(FILE * org_mp3_fptr);
    int tag_to_name(char*);
    void copy_remaining_data(struct MP3 *mp3);
    void print_edit(struct MP3 *mp3,char * argv[]);

    #endif
