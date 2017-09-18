/*
-----------------------------------------------------------
@Author
Kadiyam Yaswant Reddy
-----------------------------------------------------------
*/

int hasher(char* string1,int pin)
{
	int h = 0;
	for(int i = 0;i<5;i++)
	{
		h += ((int)string1[pin+i])*pow(5,(5-i));
	}
	return h;
}

void fingerprinting(struct files *file1,struct files *file2, char* fname1,char* fname2)
{
	/*
	-------------------------------------------------------
	This function takes two structures of files and their
	names to print their Fingerprinting similarity. 
	-------------------------------------------------------
	*/

	/*
	-------------------------------------------------------
	string1 length->string1ln-4
	string2 length->string2ln-4
	k->5
	p->10
	-------------------------------------------------------
	*/
	int k = 5;
	int p = 10;
	int string1ln = strlen(file1->ffingerstring);
	int string2ln = strlen(file2->ffingerstring);

	/*
	------------------------------------------------------
	if one or both lengths less than 5 then print Small
	------------------------------------------------------
	*/

	if((string1ln<5)||((string2ln<5)))
	{
		printf("SMALL\t\t");
	}

	else
	{
		
		/*
		-------------------------------------------------
		hash array1->hash1
		hash array2->hash2
		-------------------------------------------------
		*/

		int hash1[(string1ln-4)];
		int hash2[(string2ln-4)];

		for(int i =0;i<(string1ln-4);i++)
		{
			hash1[i] = hasher(file1->ffingerstring,i);
		}

		for(int i =0;i<(string2ln-4);i++)
		{
			hash2[i] = hasher(file2->ffingerstring,i);
		}

		/*
		------------------------------------------------
		p-mods array1->hash1
		p-mods array2->hash2
		------------------------------------------------
		*/

		for(int i=0;i<(string1ln-4);i++)
		{
			if((hash1[i]%p)!=0)
			{
				for(int j=(i+1);j<(string1ln-4);j++)
				{
					hash1[j-1]=hash1[j];
				}
				string1ln--;
			}
		}

		for(int i=0;i<(string2ln-4);i++)
		{
			if((hash2[i]%p)!=0)
			{
				for(int j=(i+1);j<(string2ln-4);j++)
				{
					hash2[j-1]=hash2[j];
				}
				string2ln--;
			}
		}
		/*
		----------------------------------------------
		p-mods array1 length->string1ln
		p-mods array2 length->string2ln
		p-mods total length->totalln
		----------------------------------------------
		*/
		string1ln = string1ln-4;
		string2ln = string2ln-4;
		double totalln = string2ln+string1ln;
		/*
		-----------------------------------------------
		Calculating similarity for two p-mod arrays.
		-----------------------------------------------*/
		int z = 0;
		int i = 0;
		int c = 0;

		for(i=0;i<string1ln;i++)
		{
			int k = i;
			int j = 0;
			c = 0;
			while(k<string1ln && j<string2ln)
			{
				while (((k<string1ln)&&(j<string2ln))&&((hash1[k]==hash2[j])))
				{	
					c += 1;
					k += 1;
					j += 1;
				}
				if((k<string1ln) && (j<string2ln))
				{
					if((hash1[k]!=hash2[j]))
					{
						k = i;
						if(c>z)
							{
								z = c;
							}
						c = 0;
						if((hash1[k]!=hash2[j]))
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
		/*
		------------------------------------------------------
		Handling Zero division error and printing the 
		similarity percentage.
		------------------------------------------------------
		*/
		if(totalln==0)
		{
			printf("SMALL\t\t");
		}
		else
		{
			double fnprnt = ((2*z)/totalln)*100;
			printf("%.2f\t\t",fnprnt);
		}
	}
}