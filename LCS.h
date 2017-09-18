/*
---------------------------------------------------------
@Author
Kadiaym Yaswant Reddy

Longest common sequence of words is calculated, Lcs is
calculated and printed between the files.
--------------------------------------------------------- 
*/

void LCS(struct files *file1, struct files *file2, char* fname1, char* fname2)
{
	/*
	--------------------------------------------------------------------------
	Takes names and structures of two files to print LCS of those files.
	--------------------------------------------------------------------------
	*/

	int z = 0;
	int i = 0;
	int c = 0;
	for(i=0;i<file1->fallwordslen;i++)
	{
		int k = i;
		int j = 0;
		c = 0;
		while(k<file1->fallwordslen && j<file2->fallwordslen)
		{
			while (k<file1->fallwordslen&&j<file2->fallwordslen&&(strcmp(file1->fallwords[k],file2->fallwords[j])==0))
			{	
				c += strlen(file1->fallwords[k]);
				k += 1;
				j += 1;
			}
			if(k<file1->fallwordslen && j<file2->fallwordslen)
			{
				if(strcmp(file1->fallwords[k],file2->fallwords[j])!=0)
				{
					k = i;
					if(c>z)
						{
							z = c;
						}
					c = 0;
					if(strcmp(file1->fallwords[k],file2->fallwords[j])!=0)
						{
							j += 1;
						}
				}
			}
		}	
		if(c>z)
		{
			z = c;
		}
	}
	if(c>z)
	{
		z = c;
	}
	double len_dct1 = 0;
	double len_dct2 = 0;
	for(i=0;i<file1->fallwordslen;i++)
	{
		len_dct1 = len_dct1 + strlen(file1->fallwords[i]);
	}
	for(i=0;i<file2->fallwordslen;i++)
	{
		len_dct1 = len_dct1 + strlen(file2->fallwords[i]);
	}
	double lcs = ((2*z)/(len_dct1+len_dct2))*100;
	printf("%.2f\t\t",lcs);
}