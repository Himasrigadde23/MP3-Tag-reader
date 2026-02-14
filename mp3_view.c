  #include "mp3_header.h"

  void view(struct MP3 *mp3)
  {
    //opening smaple.mp3 file in read mode
    mp3->org_mp3_fptr=fopen(mp3->mp3_filename,"r");
    //checking sample file is existing or not
    if(mp3->org_mp3_fptr == NULL)
    {
      printf("mp3 file is not exist");
      return;
    }
    printf("mp3 file is exist\n");
    printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("MP3 Tag Reader and Editor for ID3v2\n");
    printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
    //skiping first 10 bytes
    fseek(mp3->org_mp3_fptr,10,SEEK_CUR);
    int i=6;
    while(i)
    {
      //Tag information is collected and stored in tag
      char tag[5];
      fread(tag,4,1,mp3->org_mp3_fptr);
      //adding last character as null
      tag[4]='\0';
      //size of data which is storing file information
      int frame_size;
      //4 bytes of information reads from sample file
      fread(&frame_size,sizeof(int),1,mp3->org_mp3_fptr);
      //littleendian to bigendian
      toggle_endianess(mp3,&frame_size);
      //skiping 3 bytes of flags which is not required
      fseek(mp3->org_mp3_fptr,3,SEEK_CUR);
      //to get tag name
      int ret= tag_to_name(tag);
      if(ret==0)
      {
          printf("invalid tag found");
          return;
      }
      //read one by one byte from the file and print the frame content
      for(int i=0;i<(frame_size-1);i++)
      {
        char ch;
          fread(&ch,1,1,mp3->org_mp3_fptr);
          printf("%c",ch);
      }
      printf("\n");
      i--;
    }//loop for 6 times
  printf("--------------------------------------------------------------------------------------------------------------------------------------\n");

  }

  