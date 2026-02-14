	#include "mp3_header.h"

	int validate_cla(int argc, char *argv[], struct MP3 *mp3)
	{
		if( argc == 1 )
		{
		printf("------------------------------------------------------------------------------\n");
		printf("ERROR: ./a.out : INVALID ARGUMENTS\n");
		printf("USAGE : To view please pass like: ./a.out -v mp3filename\n");
		printf("To edit please pass like: ./a.out -e -t/-a/-A/-m/-y/-c changing_text mp3filename\n");
		printf("To get help pass like : ./a.out --help\n");
		printf("------------------------------------------------------------------------------\n");
		return 0;
		}

		if( (strcmp(argv[1], "--help") == 0) )
		{
		printf("------------------------------->HELP<-----------------------------------------\n");
		printf("1. -v -> to view mp3 file contents\n");
		printf("2. -e -> to edit mp3 file contents\n");
		printf("\t\t2.1. -t -> to edit song title\n");
		printf("\t\t2.2. -a -> to edit artist name\n");
		printf("\t\t2.3. -A -> to edit album name\n");
		printf("\t\t2.4. -y -> to edit year\n");
		printf("\t\t2.5. -m -> to edit content\n");
		printf("\t\t2.6. -c -> to edit comment\n");
		printf("------------------------------------------------------------------------------\n");
		return 0; 
		}

		if(!strcmp(argv[1], "-v"))
		{
		if(argc==3)
		{
			char * ret=strstr(argv[2],".mp3");//checking file name 
			if(ret==NULL)
				return 0;
			else
			{
				if(strcmp(ret,".mp3")!=0) 
				return 0;
			}
			mp3->mp3_filename = argv[2];//assign argv[2] to a new pointer
			return VIEW;//returning to view function
		}
		else
		{
			printf("------------------------------------------------------------------------------\n");
			printf("ERROR: ./a.out : INVALID ARGUMENTS\n");
			printf("USAGE : To view please pass like: ./a.out -v mp3filename\n");
			printf("To edit please pass like: ./a.out -e -t/-a/-A/-m/-y/-c changing_text mp3filename\n");
			printf("To get help pass like : ./a.out --help\n");
			printf("------------------------------------------------------------------------------\n");
			return 0;
		}
		}
		
		if(!strcmp(argv[1], "-e"))
		{
			if(argc!=5)
			return 0;
            //comparing argv[2] with tags
			if((strcmp(argv[2],"-t")!=0)&&(strcmp(argv[2], "-a")!=0)&&(strcmp(argv[2],"-A")!=0)&&(strcmp(argv[2],"-y")!=0)&&(strcmp(argv[2],"-m")!=0)&&(strcmp(argv[2],"-c")!=0))
			{
				return 0;
			}
			//validating mp3 file
			char * ptr =strstr(argv[4],".mp3");
			if(ptr==NULL)
			return 0;

			else
			{
				if(strcmp(ptr,".mp3")!=0) 
					return 0;
			}
            
			///storing tags into given_tag array
			if(strcmp(argv[2],"-t")==0)
			{
				strcpy(mp3->given_tag,"TIT2");
			}
			else if(strcmp(argv[2],"-a")==0)
			{
				strcpy(mp3->given_tag,"TPE1");
			}
			else if(strcmp(argv[2],"-A")==0)
			{
			
				strcpy(mp3->given_tag,"TALB");
			}
			else if(strcmp(argv[2],"-y")==0)
			{
				strcpy(mp3->given_tag,"TYER");
			}
			else if(strcmp(argv[2],"-c")==0)
			{
				strcpy(mp3->given_tag,"COMM");
			}
			else if(strcmp(argv[2],"-C")==0)
			{
				strcpy(mp3->given_tag,"TCON");
			}
			mp3->mp3_filename = argv[4];//assigning argv[4] to a new pointer
			return EDIT;//return to edit function
		}
		else
		{
		printf("------------------------------------------------------------------------------\n");
		printf("ERROR: ./a.out : INVALID ARGUMENTS\n");
		printf("USAGE : To view please pass like: ./a.out -v mp3filename\n");
		printf("To edit please pass like: ./a.out -e -t/-a/-A/-m/-y/-c changing_text mp3filename\n");
		printf("To get help pass like : ./a.out --help\n");
		printf("------------------------------------------------------------------------------\n");
		return 0;
		}

	}

    //converting littleendianess to bigendianess
	void toggle_endianess(struct MP3 *mp3, int *size)
	{
		char*cptr;
		cptr=(char*)size;
		for(int i=0;i<2;i++)
		{
				char temp=cptr[i];
				cptr[i]=cptr[4-i-1];
				cptr[4-i-1]=temp;
		}

	}

	//printing data according to that tag
	int tag_to_name(char * tag)
	{
		if(strcmp(tag,"TIT2")==0)
		{
		printf("TITLE    	: ");
		}
		else if(strcmp(tag,"TPE1")==0)
		{
		printf("ARTIST   	: ");
		}
		else if(strcmp(tag,"TALB")==0)
		{
		printf("ALBUM    	: ");
		}
		else if(strcmp(tag,"TYER")==0)
		{
		printf("YEAR     	: ");
		}
		else if(strcmp(tag,"TCON")==0)
		{
		printf("MUSIC    	: ");
		}
		else if(strcmp(tag,"COMM")==0)
		{
		printf("COMPOSER 	: ");
		}
		else
		{
		return 0;
		}
		return 1;
		
	}

    //copying remaining in sample file to temp file
	void copy_remaining_data(struct MP3*mp3)
	{
		char ch;
		while(fread(&ch,1,1,mp3->org_mp3_fptr)==1)
		{
		fwrite(&ch,1,1,mp3->dup_mp3_fptr);
		}
	}
    
	//printing editing data
	void print_edit(struct MP3 *mp3,char * argv[])
	{
		printf("-----------------------Select Edit Option -----------------------------\n");

	if (strcmp(mp3->given_tag, "TIT2") == 0)
		printf("-------------------Select Title Change Option -------------------------\n");
	else if (strcmp(mp3->given_tag, "TPE1") == 0)
		printf("-------------------Select Artist Change Option ------------------------\n");
	else if (strcmp(mp3->given_tag, "TALB") == 0)
		printf("---------------------Select Album Change Option ----------------------\n");
	else if (strcmp(mp3->given_tag, "TYER") == 0)
		printf("-------------------Select Year Change Option -------------------------\n");
	else if (strcmp(mp3->given_tag, "TCON") == 0)
		printf("-------------------Select Music Change Option ------------------------\n");
	else if (strcmp(mp3->given_tag, "COMM") == 0)
		printf("-------------------Select Comment Change Option ----------------------\n");

	tag_to_name(mp3->given_tag);  
	printf("%s\n", argv[3]);

	if (strcmp(mp3->given_tag, "TIT2") == 0)
		printf("----------------------Title Changed Successfully------------------------\n");
	else if (strcmp(mp3->given_tag, "TPE1") == 0)
		printf("-----------------------Artist Changed Successfully----------------------\n");
	else if (strcmp(mp3->given_tag, "TALB") == 0)
		printf("--------------------Album Changed Successfully--------------------------\n");
	else if (strcmp(mp3->given_tag, "TYER") == 0)
		printf("--------------------Year Changed Successfully---------------------------\n");
	else if (strcmp(mp3->given_tag, "TCON") == 0)
		printf("---------------------Music Changed Successfully-------------------------\n");
	else if (strcmp(mp3->given_tag, "COMM") == 0)
		printf("---------------------Comment Changed Successfully-----------------------\n");
	}