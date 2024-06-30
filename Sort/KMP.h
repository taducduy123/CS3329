#ifndef	 KMP_H
#define	 KMP_H
#include <iostream>
using namespace std;


void Compute_Prefix_Function(char P[], int size, int pi[])
{
	pi[0] = 0;
	int i = 0;
	int j = 1;
	while(j < size)								//# Comparisons = O(n), the worst case a a b a b a b a b ....
	{
		if(P[j] == P[i])					
		{
			pi[j] = i+1;
			i++;
			j++;
		}
		else
		{
			if(i > 0)
			{
				i = 0;
			}
			else
			{
				pi[j] = 0;
				j++;
			}
		}
	}
}


void KMP_Matcher(char T[], int tSize, char P[], int pSize)  //Caution: Text and Pattern do not include null terminator
{
	int pi[pSize];
	Compute_Prefix_Function(P, pSize, pi);
	
	int i = 0;			//Point to character of pattern
	int j = 0;			//Point to character of text
	
	while(j < tSize)
	{
		if(T[j] == P[i])
		{
			if(i == pSize - 1)
			{
				cout << "Occurrence at index " << j - pSize + 1 << endl;
				i = pi[i];			//Look for the next match
			}
			else
			{
				i++;
			}
			j++;
		}
		else
		{
			if(i > 0)
			{
				i = pi[i-1];
			}
			else
			{
				j++;
			}
		}
	}
}



#endif
