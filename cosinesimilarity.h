/*
----------------------------------------------------------------------
@Author
Kadiyam Yaswant Reddy
----------------------------------------------------------------------
*/

void cosinesimilarity(struct files *file1,struct files *file2)
{
	/*
	------------------------------------------------------------------
	This function takes two files and thier structures and print's the 
	cosine similarity between those.
	------------------------------------------------------------------
	*/
	if(file1->isempty||file2->isempty){
		printf("EMPTY\t\t");
	}
	else{
			int sum = 0;
			double product = 1.0;
			double cossim = 0.0;

			/*
			---------------------------------
			This loop gives us the numerator.
			---------------------------------
			*/

			for(int i=0;i<file1->fnonrepwordslen;i++)
			{
				for(int j=0;j<file2->fnonrepwordslen;j++)
				{
					int rtn = strcmp(file1->fnonrepwords[i],file2->fnonrepwords[j]);
					if(rtn==0)
					{
						sum = sum + (file1->fcount[i]*file2->fcount[j]);
						break;
					}
				}
			}

			/*
			------------------------------------
			This loop gives us the denominator.
			------------------------------------
			*/

			double sum1 = 0.0;
			for(int i=0;i<file1->fnonrepwordslen;i++)
			{
				sum1 = sum1 + pow(file1->fcount[i],2);
			}
			sum1 = sqrt(sum1);
			double sum2 = 0.0;
			for(int j=0;j<file2->fnonrepwordslen;j++)
			{
				sum2 = sum2 + pow(file2->fcount[j],2);
			}
			sum2 = sqrt(sum2);
			product = sum1*sum2;
			cossim = (sum/product)*100.0;
			printf("%.2f\t\t",cossim);
	}


}
