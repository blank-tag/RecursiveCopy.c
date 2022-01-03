#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <libgen.h>

 
void copy_file(char *dest_dir, char *src_dir, char * filename )
{
	
	char temp_src[512] = {0};                                             
        char temp_dest[512] = {0};
 
        sprintf( temp_dest, "%s/%s", dest_dir, filename );
        sprintf( temp_src, "%s/%s", src_dir, filename );
 
 /* opening a file to read and write from src and dest*/

	FILE *src_fp = fopen( temp_src ,"r" );
	if(!src_fp)
	{
		perror("open file error!");
		return ;
	}
 
	FILE *dest_fp = fopen( temp_dest, "w");
	if(!dest_fp)
	{
		perror("open file error!");
		return ;
	}
 

/*adding the files in temp buffer to read and move files from directory*/



 
}


 

/*checking sub directories inside a directory if its present copying takes place */

void _copy_dir( char *src_path, char *dest_path )
{
 
	if( strcmp( src_path, "." ) == 0 || strcmp( src_path, ".." )  == 0 )
	{
		return;
	}
 
	DIR *src_dp, *dest_dp;
        struct dirent *file_info;
 
        src_dp = opendir( src_path );
        if( src_dp == NULL )
        {
                return ;
        }

/* if directories is present it create a folder of the source directory in the destination directory*/

	
	char temp_src[512] = {0};
	char temp_dest[512] = {0};
 
	sprintf( temp_dest, "%s/%s", dest_path, basename( src_path ));
	dest_dp = opendir( temp_dest );
 
        if( dest_dp == NULL )
        {
                mkdir( temp_dest, 0777);
        }
        else
        {
                closedir( dest_dp );
        }
	
 
	while( file_info = readdir( src_dp ) )
	{
		switch( file_info->d_type )
		{
			case DT_DIR: 
				    if( strcmp( file_info->d_name, ".") != 0 && strcmp(file_info->d_name, "..")  != 0 )
    			            {
				     	sprintf( temp_src, "%s/%s", src_path, file_info->d_name );
				     	_copy_dir( temp_src, temp_dest );
				    }
				   break; 
 			case DT_REG:;				//reads file types where DT_REG = normal files extensions , accepts unknown files too 
			
			case DT_UNKNOWN:copy_file( temp_dest, src_path, file_info->d_name);
				     break;
			default:
				break;
		}
 
	}
	
	closedir( src_dp );
}
 


void copy_dir( char *name, char *src_path, char *dest_path )
{
	DIR *dest_dp;
	dest_dp = opendir( dest_path );
	if( dest_dp == NULL )
	{
		if( mkdir( dest_path, 0777 ) == -1 )
		{
			perror( "mkdir error!\n" );
			return ;
		}
	}
	else
	{
		closedir( dest_dp );
	}
	_copy_dir( src_path, dest_path );
}


int comparestrings(char*x, char*y){

int flag = 0;

	while(*x!='\0'|| *y !='\0'){
	 if(*x == *y) {
		x++;
	 	y++;
	 }

	else if ((*x == '\0' && *y != '\0')
                 || (*x != '\0' && *y == '\0')
                 || *x != *y) {
            flag = 1;
	    break;
	}
     }
	if(flag == 0){
	return 1;
	}
return 0;
}



int main(int argc, char *argv[])
{
	if(argc <= 3){
		printf("error\n");
		return 0; 
	}
        else{ 
		if(comparestrings(argv[1],"-r")){
		copy_dir(argv[1], argv[2],argv[3]);
		}
	else{
	      printf("\n please input -r");
}
	}
	
	
	
 
	return 0;


}
