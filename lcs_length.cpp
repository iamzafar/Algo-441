/*
 * 11-30-2017
 * Zafar Mamarakhimov
 * Project 2 milestone 1
 * Implementation of the serial longest common subsequence algorithm.
 * This is tabulated approach of LSC algorithm where each character of string 
 * is placed in 2-D array.
 *
 * ./lcs_length <file1> <n1> <file2> <n2> ===> how to run after compiling
 */


 /* -------------------------------------------------------------------------
    Random string was obtained using following commnand:
    cat /dev/urandom | tr -dc 'ACTG' | fold -w 10000 | head -n 1 | tr -d '\n'
  ---------------------------------------------------------------------------*/
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>

// ======================================================
// Function prototypes 

char *getInput(const char *);

int getMax(int first, int second);

int getLCS( char * String1, int, char * String2, int);

void doLSC( const char *, int, const char *, int);

// ======================================================



int main(int argc, char const *argv[])
{
    /* code */

  if (argc < 2)
  {
    /* code */
    std::cout << "Incorrect number of arguments\n";
    exit(EXIT_FAILURE);

  }else if(argc == 5){

    // after getting right arguments, get the LSC
    doLSC(argv[1], std::stoi(argv[2]), argv[3], std::stoi(argv[4]));    
    
    std::cout << "End of the program" << std::endl;

  }
    return 0;
}


// Get the input and do the LSC algorithm
void doLSC( const char * file1, int n1, const char * file2, int n2){
  std::cout << "inside of doLCS()\n";
  char * str1 = getInput(file1);
  char * str2 = getInput(file2);

  int lcs_length = getLCS(str1, n1, str2, n2);

  std::cout << "The length of the LCS = " << lcs_length << std::endl;
  delete str1;
  delete str2;
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
int getLCS( char *X, int m, char *Y, int n )
{
   
   int length;
   int **matrix = new int * [m + 1];
   for(int i = 0; i <= m; i++){
    matrix[i] =  new int[n+1];
   }

   // int L[m+1][n+1];
   // int i, j;
  
   /* Following steps build L[m+1][n+1] in bottom up fashion. Note 
      that L[i][j] contains length of LCS of X[0..i-1] and Y[0..j-1] */
   for (int i=0; i<=m; i++)
   {
     for (int j=0; j<=n; j++)
     {
       if (i == 0 || j == 0)
         matrix[i][j] = 0;
  
       else if (X[i-1] == Y[j-1])
         matrix[i][j] = matrix[i-1][j-1] + 1;
  
       else
         matrix[i][j] = getMax(matrix[i-1][j], matrix[i][j-1]);
     }
   }
    
   /* L[m][n] contains length of LCS for X[0..n-1] and Y[0..m-1] */
   

   length = matrix[m][n];

   for (int i = 0; i <= m; ++i)
   {
     delete [] matrix[i];
     matrix[i] = NULL;
   }

   delete[] matrix;
   matrix = NULL;
   return length;
}

// Read the input file
char *getInput(const char * input_file){
  FILE *f = fopen(input_file, "r"); 

  // get the file size
  fseek(f, 0, SEEK_END);
  size_t size = ftell(f);

  // std::cout << "**** size " << size << std::endl;
  fseek(f, 0, SEEK_SET);
  // rewind(f);

  char * str = new char[size + 1];
  fread(str, size, 1, f);

  // std::cout << f << std::endl;
  // std::cout << size << std::endl;

  fclose(f);
  str[size] = '\0'; 
  // std::cout << str << std::endl;
  return str;
}