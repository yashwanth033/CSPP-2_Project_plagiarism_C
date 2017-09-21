/*
----------------------------------------------------------------------
@Author
Kadiyam Yaswant Reddy
----------------------------------------------------------------------
*/

int removechars(int c)
{
    /*
    ------------------------------------------------------------------
    This function takes a char at a time to convert case to lower and
    to remove special characters and gives a single string with spaces 
    between words.
    ------------------------------------------------------------------
    */

    if(c==32||c==95||(c>=97&&c<=122)||(c>=48&&c<=57))
    {}
    else if(c==10)
    {
        c = 32;
    }
    else if(c>=65&&c<=90)
    {
    	c = c+32;
    }
    else
    {
    	c = 0;
    }
	  return c;
}

int removecharslcs(int c)
{

    /*
    ---------------------------------------------------------------------
    This function takes a char at a time and removes all special chars
    and spaces to make one single continuous string which can be used for
    LCS and Finger Printing.
    ---------------------------------------------------------------------
    */

    if(c==95||(c>=97&&c<=122)||(c>=48&&c<=57))
    {}
    else if(c>=65&&c<=90)
    {
        c = c+32;
    }
    else
    {
        c = 0;
    }
      return c;
}


void operator(struct files *fii, char* fname,char** fstopwords,int fstopwordcount)
{
    
    /*
    --------------------------------------------------------------------
    This function takes filename, a structure pointer, stopwords array, 
    count and return the listed info to structure.
    1. File as a single continuos string(fchar->fchars)and its length.
    fcharl->fcharlen.
    2. File as a array of all (words allWords->fallwords) and array size
    counter->fallwordslen.
    3.File as a array of non repeating words (nonrepwords->fnonrepwords)
    also their frequencies in a array (counts->fcount) and these array 
    sizes (counter2->fnonrepwordslen).
    4.File as a string of no stop words(fingerstring->ffingerstring).
    --------------------------------------------------------------------
    */

    FILE *fp;
    int c;
    int c1;
    int n = 0;
    char dm[2] = {'\0','\0'};
    char dm1[2] = {'\0','\0'};
    char *fwords;
    char *fchar;
    int flen;
    int fcharl;

    /*
    ----------------------------------------------------------------------
    The loop below gives file as a single continuos string (fchar*).
    Also a string with spacing between words (fwords). fcharl and flen are 
    their lengths respectively.
    ----------------------------------------------------------------------
    */

    fp = fopen(fname,"r");

    if(fp == NULL) 
    {
        perror("Error in opening file:");
        exit(1);
    }

    do
    {
        c = fgetc(fp);
        c1 = c;
        if( feof(fp) )
        {
            break ;
        }

        c = removechars(c);
        c1 = removecharslcs(c1);

        dm[0] = c;
        dm1[0] = c1;

        if(n==0)
        {
            fwords = (char*)malloc((n+2)*sizeof(char));
            fchar = (char*)malloc((n+2)*sizeof(char));
            fwords[0]= '\0';
            fchar[0]= '\0';
        }
        else{
            fwords = (char*)realloc(fwords,((n+2)*sizeof(char)));
            fchar = (char*)realloc(fchar,((n+2)*sizeof(char)));
        }
        strcat(fwords,dm);
        strcat(fchar,dm1);
        n++;
    }while(1);

    if(n==0){
        fii->isempty = true;
    }

    else{
            flen = strlen(fwords);
            fcharl = strlen(fchar);

            fclose(fp);

            /*
            ----------------------------------------------------------------------------
            While loop below gives array of all words in file(allWords) and array length 
            counter.
            ----------------------------------------------------------------------------
            */

            char str[flen];
            strcpy(str,fwords);
            char *token = strtok(str, " ");
            char **allWords;
            char **nonrepwords;
            int *counts;
            int counter = 0;    

            while (token != NULL)
            {
                int strln = strlen(token);

                if (counter == 0)
                {
                    allWords = (char **)malloc(sizeof(char *));
                    allWords[counter] = (char *)malloc(sizeof(char)*strln);
                }
                else
                {
                    allWords = (char **)realloc(allWords,((counter+1)*sizeof(char *)));
                    allWords[counter] = (char *)malloc(sizeof(char)*strln);
                }

                strcpy(allWords[counter],token);
                counter++;

                token = strtok(NULL, " ");
            }

            /*
            ---------------------------------------------------------------------
            This loop gives array of non repetitive words(nonrepwords) and array
            with their frequencies(counts) and the their length(counter2).
            ---------------------------------------------------------------------
            */

            int counter2 = 0;
            for(int i=0; i<counter ;i++)
            {
                int flag =0;

                for(int j=0;j<counter2;j++)
                {
                    int rtn = strcmp(allWords[i],nonrepwords[j]);
                    if(rtn==0)
                    {
                        flag = 1;
                    }
                }
                if(flag==0)
                {
                    int strln = strlen(allWords[i]);
                    if (counter2 == 0)
                    {
                        nonrepwords = (char **)malloc(sizeof(char *));
                        nonrepwords[counter2] = (char *)malloc(sizeof(char)*strln);
                    }
                    else
                    {
                        nonrepwords = (char **)realloc(nonrepwords,((counter2+1)*sizeof(char *)));
                        nonrepwords[counter2] = (char *)malloc(sizeof(char)*strln);
                    }
                    strcpy(nonrepwords[counter2],allWords[i]);
                    int count = 0;
                    for(int k=0;k<counter;k++)
                    {
                        int rtn2 = strcmp(nonrepwords[counter2],allWords[k]);
                        if(rtn2==0)
                        {
                            count++;
                        }
                    }

                    if (counter2 == 0)
                    {
                        counts = (int *)malloc(sizeof(int));
                    }
                    else
                    {
                        counts = (int *)realloc(counts,((counter2+1)*sizeof(int)));
                    }
                    counts[counter2]=count;
                    counter2++;
                }

            }

            /*
            ------------------------------------------------------------------------
            Removing stop words and and adding words to a array named nostopwords.
            ------------------------------------------------------------------------
            */

            char **nostopwords;
            int nostopwordcount=0;
            for(int i=0;i<counter;i++)
            {
                int flag = 0;
                for(int j=0;j<fstopwordcount;j++)
                {
                    int rtn = strcmp(allWords[i],fstopwords[j]);
                    if(rtn==0)
                    {
                        flag = 1;
                        break;
                    }
                }
                if(flag==0)
                {
                    int strln = strlen(allWords[i]);
                    if(nostopwordcount==0)
                    {
                        nostopwords = (char **)malloc(sizeof(char *));
                        nostopwords[nostopwordcount] = (char *)malloc(sizeof(char)*strln);
                    }
                    else
                    {
                        nostopwords = (char **)realloc(nostopwords,(sizeof(char*))*(nostopwordcount+1));
                        nostopwords[nostopwordcount] = (char *)malloc(sizeof(char)*strln);
                    }
                    strcpy(nostopwords[nostopwordcount],allWords[i]);
                    nostopwordcount++;
                }
            }
            /*
            ---------------------------------------------------------------------------------
            Forming single string of nostopwords for finger printing.
            ---------------------------------------------------------------------------------
            */

            char* fingerstring;
            int strln = 0;
            int j = 0;
            for(int i=0;i<nostopwordcount;i++)
            {
                strln = strlen(nostopwords[i]);
                if(j==0)
                {
                    j += strln;
                    fingerstring = (char *)malloc(sizeof(char)*(j+1));
                    fingerstring[0] = '\0';
                }
                else
                {
                    j += strln;
                    fingerstring = (char *)realloc(fingerstring,sizeof(char)*(j+1));
                }
                strcat(fingerstring,nostopwords[i]);
            }

            /*
            ------------------------------------------------------
            Passing them to into the arguement stucture variables
            and freeing unreturned pointers.
            ------------------------------------------------------
            */
            
            free(nostopwords);
            free(fwords);
            free(token);

            fii->fchars = fchar;
            fii->fcharlen = fcharl;
            fii->fallwords = allWords;
            fii->fallwordslen = counter;
            fii->fnonrepwords = nonrepwords;
            fii->fnonrepwordslen = counter2;
            fii->fcount = counts;
            fii->ffingerstring = fingerstring;
            fii->isempty = false;
    }

}