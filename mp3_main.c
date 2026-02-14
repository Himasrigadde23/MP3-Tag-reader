    /*

    NAME          :Himasri Gadde
    Date          :06-01-2026
    Description   :This project is a command-line MP3 tag reader and editor written in C, specifically designed to handle ID3v2 metadata in MP3 files.
                   It allows users to view the existing tag information or modify specific tags without corrupting the audio data. 
                   The tool supports basic operations through command-line arguments, making it a lightweight utility for managing MP3 metadata.
                   The program supports two primary modes: viewing and editing.
                   In view mode (invoked with -v), it reads an MP3 file, skips the initial ID3v2 header, and extracts the content of six predefined tags—
                   Title (TIT2), Artist (TPE1), Album (TALB), Year (TYER), Genre (TCON), and Comment (COMM)—displaying them in a formatted manner. 
                   It correctly handles the big-endian byte order of frame sizes by converting them to the host system's endianness for proper processing.
                   In edit mode (invoked with -e), users can modify one of these six tags by providing the new text. 
                   The program creates a temporary file, copies the ID3v2 header and all unmodified tags unchanged, replaces the selected tag's content with the user-provided string, and then copies the remaining audio data.
                   After completion, it overwrites the original file with the modified version and displays a confirmation message showing the updated value.
                   The tool includes thorough command-line argument validation, proper error handling for invalid inputs or missing files, and a helpful --help option that explains usage and supported tags. 
                   While simple and educational in nature, it demonstrates key concepts like binary file manipulation, endianness conversion, and safe in-place editing through temporary files. 
                   However, it assumes a fixed structure with exactly these six tags in a specific order and lacks support for more complex ID3v2 features.
    
    */
    
    
    
    #include "mp3_header.h"

    int main(int argc, char *argv[])
    {
        /* structure variable declaration */
        struct MP3 mp3;
        //assigning validate value to ret variable
        int ret = validate_cla(argc,argv,&mp3);
        if(ret == VIEW)
        {
            view(&mp3);//for go to view and print information
        }
        else if(ret == EDIT)
        {
            edit(&mp3,argv,argc);//for go to edit and edit the requirements
        }
        else
        {
        puts("invalid CLA passed");
        }

        return 0;

    }
