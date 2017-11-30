/*
 * 11-30-2017
 * Zafar Mamarakhimov
 * Project 2 milestone 1
 * Implementation of the serial longest common subsequence algorithm.
 * This is tabulated approach of LSC algorithm where each character of string 
 * is placed in 2-D array.
 */
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>

// ======================================================
// Function prototypes 

char *getInput(char * input_file);

int getMax(int first, int second);

int getLCS( char *X, char *Y, int m, int n );

// ======================================================

int main(int argc, char const *argv[])
{
    /* code */

  if (argc < 2)
  {
    /* code */
    std::cout << "Incorrect number of arguments\n";
    exit(EXIT_FAILURE);
  }else{



    char X[] = "AGGTAB";
    char Y[] = "GXTXAYB";

    int m = strlen(X);
    int n = strlen(Y);
 
    std::cout << "The length of the LCS " << getLCS(X, Y, m, n) << std::endl;
    std::cout << "End of the program" << std::endl;
  }
    return 0;
}

// Utility function that returns maximum number
int getMax(int first, int second)
{
    if (first > second)
    {
        return first;
    }
    return second;
}

/* Returns length of LCS for X[0..m-1], Y[0..n-1] */
int getLCS( char *X, char *Y, int m, int n )
{
   int L[m+1][n+1];
   int i, j;
  
   /* Following steps build L[m+1][n+1] in bottom up fashion. Note 
      that L[i][j] contains length of LCS of X[0..i-1] and Y[0..j-1] */
   for (i=0; i<=m; i++)
   {
     for (j=0; j<=n; j++)
     {
       if (i == 0 || j == 0)
         L[i][j] = 0;
  
       else if (X[i-1] == Y[j-1])
         L[i][j] = L[i-1][j-1] + 1;
  
       else
         L[i][j] = getMax(L[i-1][j], L[i][j-1]);
     }
   }
    
   /* L[m][n] contains length of LCS for X[0..n-1] and Y[0..m-1] */
   return L[m][n];
}