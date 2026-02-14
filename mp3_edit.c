  #include "mp3_header.h"

  void edit(struct MP3 *mp3,char *argv[],int argc)
  {
    //create and opening temp file in write mode
    mp3->dup_mp3_fptr=fopen("temp.mp3","w");
    //opening sample file in read mode
    mp3->org_mp3_fptr=fopen("sample.mp3","r");
    //validating the temp file is existing or not
    if(mp3->dup_mp3_fptr == NULL)
    {
      printf("File does not exist");
      return;
    }
    //reading first 10 header bytes from sample file
    char header[10];
    fread(&header,10,1,mp3->org_mp3_fptr);
    //copying first 10 header bytes into temp file
    fwrite(mp3->org_mp3_fptr,10,1,mp3->dup_mp3_fptr);
    int i=6;
    while(i)
    {    
        //Tag information is collected and stored in tag
        char tag[5];
        fread(tag,4,1,mp3->org_mp3_fptr);
        //adding last character as null
        tag[4]='\0';
        //copying tag 4 bytes into temp file
        fwrite(tag,4,1,mp3->dup_mp3_fptr);
        if(strcmp(mp3->given_tag,tag)==0)//tag found
        {
          //size of data which is storing file information
          int frame_size;
          //4 bytes of information reads from sample file
          fread(&frame_size,sizeof(int),1,mp3->org_mp3_fptr);
          //littleendian to bigendian
          toggle_endianess(mp3,&frame_size);
          //storing the size of new message into temp_size 
          int temp_size=strlen(argv[3])+1;
          //littleendian to bigendian
          toggle_endianess(mp3,&temp_size);
          //copying temp_size into temp file
          fwrite(&temp_size,sizeof(int),1,mp3->dup_mp3_fptr);
          char flags[3];
          //reading 3 flags from sample file
          fread(flags,3,1,mp3->org_mp3_fptr);
          //copying those 3 flags into temp file
          fwrite(flags,3,1,mp3->dup_mp3_fptr);
          //littleendian to bigendian
          toggle_endianess(mp3,&temp_size);
          //storing the new message in temp file
          fwrite(argv[3],temp_size-1,1,mp3->dup_mp3_fptr);
          //skiping frame_size bytes in sample file
          fseek(mp3->org_mp3_fptr,frame_size-1,SEEK_CUR);
          break;
        }
        else  //tag not found
        {
          int frame_size;
          //reading frame size from sample file
          fread(&frame_size,sizeof(int),1,mp3->org_mp3_fptr);
          //copying frame size into temp file
          fwrite(&frame_size,sizeof(int),1,mp3->dup_mp3_fptr);
          //littleendian to bigendian
          toggle_endianess(mp3,&frame_size);
          char flags[3];
          //reading 3 flag bytes from sample file
          fread(flags,3,1,mp3->org_mp3_fptr);
          //copying 3 flag bytes into temp file
          fwrite(flags,3,1,mp3->dup_mp3_fptr);
          char ch;
          for(int i=0;i<(frame_size-1);i++)
          {
            //reading one by one byte from sample file
            fread(&ch,1,1,mp3->org_mp3_fptr);
            //copying one by one byte into templ file
            fwrite(&ch,1,1,mp3->dup_mp3_fptr);
          }
          
        }
        i--;
    }//runs loop for 6 times
    
    copy_remaining_data(mp3);//copy remaining data from sample file to temp file

    remove(mp3->mp3_filename);//remove sample file
    rename("temp.mp3",mp3->mp3_filename);//renaming temp file as sample file

    print_edit(mp3,argv);//printing editing data

    fclose(mp3->dup_mp3_fptr);//close temp file
    fclose(mp3->org_mp3_fptr);//closing sample file

  }

