/*
-------------------------------------------------------------
@Author
Yaswant Reddy Kadiyam

@PlageC Version 1.0.
PLagiarism detection with Bag of Words in c.
The current code reads all files in the directory path given.
Directory should contain only .txt files and they should not 
be empty. All the special characters except for '_' have been
removed. All the characters have been lower cased.

*****To be complied with -lm for math function to work.******
-------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

/*
-------------------------------------------------------------
Structure to contain all data read from Files.
-------------------------------------------------------------
*/

struct files
{
	char *fchars;
	int fcharlen;
	char **fallwords;
	int fallwordslen;
	char **fnonrepwords;
	int fnonrepwordslen;
	int *fcount;
	char *ffingerstring;
	bool isempty;
};

/*
-------------------------------------------------------------
Included operator.h that reads each file and enters data into 
structure and included cosinesimilarity.h that performs the
cosine similarity.
-------------------------------------------------------------
*/

#include "operator.h"
#include "cosinesimilarity.h"
#include "LCS.h"
#include "fingerprinting.h"

void timestamp()
{
    /*
    -------------------------------------------------------
    Prints Time.
    -------------------------------------------------------
    */
    time_t ltime; /* calendar time */
    ltime=time(NULL); /* get current cal time */
    printf("%s\n",asctime( localtime(&ltime) ) );
}

int main(int argc, char const *argv[])
{
	struct dirent *de;  

FILE *flp;
flp = freopen("logfile.log", "a", stdout);
timestamp();
/*
------------------------------------------------------------------
Path of directory is to be given through terminal while 
executing.
------------------------------------------------------------------
*/ 

    DIR *dr = opendir(argv[1]);
    int n = 0;
    int i = 0;
 
    if (dr == NULL)
    {
        printf("Could not open current directory\n" );
        exit(1);
    }
 
    while ((de = readdir(dr)) != NULL)
    {
	    if ( !strcmp(de->d_name, ".") || !strcmp(de->d_name, "..") )
	    {} 
	    else 
	    {
	        n++;
	    }
	}
	rewinddir(dr);

/*
-----------------------------------------------------------------
All file names have been listed in to the FilesList Array. Empty
directories handled.
-----------------------------------------------------------------
*/

if(n==0){
	printf("Error: Directory is empty.\n");
	exit(1);
}

	char *filesList[n];
	char *filepaths[n];

	while((de = readdir(dr)) != NULL) 
	{
	    if ( !strcmp(de->d_name, ".") || !strcmp(de->d_name, "..") )
	    {}
	    else 
	    {   
	        filepaths[i] = (char*) malloc (strlen(de->d_name)+1+strlen(argv[1])+1);
	        filesList[i] = (char*) malloc (strlen(de->d_name)+1);
	        strncpy (filepaths[i],argv[1], strlen(argv[1])+1);
	        strncpy (filesList[i],de->d_name,strlen(de->d_name)+1);
	        strcat(filepaths[i],de->d_name);
	        i++;
	    }
	}
	rewinddir(dr);

    closedir(dr);

/*
--------------------------------------------------------------------------------
Stop words are read into a array to be used to removed them from each file for 
finger-printing.
--------------------------------------------------------------------------------
*/

char **stopwords;
char sword[50];
int swordlen;
int stopwordcount = 0;
FILE *fswp = fopen("stopwords.txt","r");
if(fswp == NULL) 
    {
        perror("Error in opening stop words file\n");
        exit(1);
    }

while( fgets (sword, 50, fswp)!=NULL )
{
	swordlen = strlen(sword);
	if(stopwordcount==0)
	{
		stopwords = (char **)malloc(sizeof(char *));
		stopwords[stopwordcount] = (char *)malloc(sizeof(char)*swordlen);
	}
	else
	{
		stopwords = (char **)realloc(stopwords,(sizeof(char*))*(stopwordcount+1));
		stopwords[stopwordcount] = (char *)malloc(sizeof(char)*swordlen);
	}
	strcpy(stopwords[stopwordcount],sword);
	stopwordcount++;

}
for(int swordlen = 0;swordlen<stopwordcount-1;swordlen++)
{
	if(stopwords[swordlen][strlen(stopwords[swordlen])-2]=='\n');
	{
		stopwords[swordlen][strlen(stopwords[swordlen])-2]='\0';
	}
}
fclose(fswp);

/*
--------------------------------------------------------------------
Structure array with each element containing a file's data.
--------------------------------------------------------------------
*/

    struct files file[n];
/*
--------------------------------------------------------------------
Filling the structure with file data and starting printing as array.
--------------------------------------------------------------------
*/

    printf("-----------------------------BAG OF WORDS------------------------------\n");
    printf("FILES\t\t");

    for(i=0; i<n; i++)
    {
    	operator(&file[i],filepaths[i],stopwords,stopwordcount);
    	printf("%s\t",filesList[i]);
 	}
 	printf("\n");

/*
-------------------------------------------------------------------
Finding the cosine similarity for all combinations of files.
-------------------------------------------------------------------
*/

 	for(i=0; i<n; i++)
 	{
 		printf("%s\t",filesList[i]);
 		for(int j=0; j<n; j++)
 		{
 			if(i==j)
 			{
 				printf("SAMEFILE\t");
 			}
 			else
 			{
 				cosinesimilarity(&file[i],&file[j]);
 			}
 		}
 		printf("\n");
 	}

 	printf("--------------------------------L C S-------------------------------\n");
 	printf("FILES\t\t");

/*
-------------------------------------------------------------------
Finding the L C S for all combinations of files.
-------------------------------------------------------------------
*/

    for(i=0; i<n; i++)
    {
    	printf("%s\t",filesList[i]);
 	}
 	printf("\n");

 	for(i=0; i<n; i++)
 	{
 		printf("%s\t",filesList[i]);
 		for(int j=0; j<n; j++)
 		{
 			if(i==j)
 			{
 				printf("SAMEFILE\t");
 			}
 			else
 			{
 				LCS(&file[i],&file[j]);
 			}
 		}
 		printf("\n");
 	}

 	printf("----------------------------Fingerprinting---------------------------\n");
  	printf("FILES\t\t");

	/*
	-------------------------------------------------------------------
	Finding the Finger printing for all combinations of files.
	-------------------------------------------------------------------
	*/

    for(i=0; i<n; i++)
    {
    	printf("%s\t",filesList[i]);
 	}
 	printf("\n");

 	for(i=0; i<n; i++)
 	{
 		printf("%s\t",filesList[i]);
 		for(int j=0; j<n; j++)
 		{
 			if(i==j)
 			{
 				printf("SAMEFILE\t");
 			}
 			else
 			{
 				fingerprinting(&file[i],&file[j]);
 			}
 		}
 		printf("\n");
 	}
 	printf("\n\n");

	return 0;
}