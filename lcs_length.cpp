/*
 * 11-30-2017
 * Zafar Mamarakhimov
 * Project 2 milestone 1
 * Implementation of the serial longest common subsequence algorithm.
 * This is tabulated approach of LSC algorithm where each character of string 
 * is placed in 2-D array.
 *
 * The file can be compiled using commnand 'make'
 * ./lcs_length <file1> <n1> <file2> <n2> ===> how to run after compiling
 */


 /* -------------------------------------------------------------------------
    Random string was obtained using following commnand:
    cat /dev/urandom | tr -dc 'ACTG' | fold -w 10000 | head -n 1 | tr -d '\n'
  ---------------------------------------------------------------------------*/
#include <iostream>
#include <omp.h>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <utility>
#include <time.h>

// ======================================================
// Function prototypes 

char *getInput(const char *);

int getLCS( char * String1, int, char * String2, int);

void doLSC( const char *, int, const char *, int);

void cleanMatrix(int **, int);

void swapString(char **, char **);

void swapNum(int&, int&);

// ======================================================


int main(int argc, char const *argv[])
{
    
  if (argc < 2)
  {
    std::cout << "Incorrect number of arguments\n";
    exit(EXIT_FAILURE);

  }else if(argc == 5){

    // after getting right arguments, get the LSC
    doLSC(argv[1], std::stoi(argv[2]), argv[3], std::stoi(argv[4]));    
    
    std::cout << "End of the program\n" << std::endl;

  }
    return 0;
}


// Get the input and do the LSC algorithm
void doLSC( const char * file1, int n1, const char * file2, int n2){
  // std::cout << "inside of doLCS()\n";
  char * str1 = getInput(file1);
  char * str2 = getInput(file2);

  int lcs_length = getLCS(str1, n1, str2, n2);

  std::cout << "The length of the LCS = " << lcs_length << std::endl;
  delete str1;
  delete str2;
}

/* Returns length of LCS for String1[0..m-1], String2[0..n-1] */
int getLCS( char * String1, int m, char * String2, int n )
{
   
   int length;   

   if (n > m){
      swapNum(m, n);
      swapString(&String1, &String2); // swap the string
   }

   // creating matrix on the heap, because the size can be different and
   // there is limit if matrix was created on the stack;   
   int **matrix = new int * [m+n];   
   // #pragma omp parallel for
   for(int i = 0; i <= m; i++){
    matrix[i] =  new int[n+m]; 
   }

   #pragma omp parallel for
   for (int a = 0; a <= m; ++a)
   {
     /* code */
    matrix[a][0] = 0;
   }

   #pragma omp parallel for
   for (int b = 0; b <= n; ++b)
   {
     /* code */
    matrix[0][b] = 0;
   }

   //std::cout << "======here=======" << std::endl;
   /* Following steps build matrix[m+1][n+1] in bottom up fashion. Note 
      that matrix[i][j] contains length of LCS of string1[0..i-1] and string2[0..j-1] */
   
   double t0 = omp_get_wtime();
   
   for (int i=1; i<=m; ++i)
   {
      #pragma omp parallel for shared(matrix)
      for (int j=1; j<=n; ++j){
       // if (i == 0 || j == 0)
       //   matrix[i][j] = 0;
  
       if (String1[i-1] == String2[j-1])
         matrix[i][j] = matrix[i-1][j-1] + 1;
  
       else {
          if (matrix[i-1][j] > matrix[i][j-1])
            matrix[i][j] = matrix[i-1][j];
          else
            matrix[i][j] = matrix[i][j-1];           
       } 
     }
   }
    
  int weight = 0;

   for (int k = 2; k <= m; ++k){
     if(weight < m-n){
        weight +=1;
     }
     #pragma omp parallel for
     for (int j = k; j < n+weight; ++j)
     {
        if(String2[j] == String1[j]){
          matrix[n-j+k][j] = matrix[n-j+k-1][j-1]+1;
        }else if(matrix [n-j+k-1][j] >= matrix[n-j+k][j-1]){
          matrix[n-j+k][j] = matrix[n-j+k-1][j];
        }else
          matrix[n-j+k][j] = matrix[n-j+k][j-1];
     }

   }

   double t = omp_get_wtime() - t0;

   length = matrix[m][n];
   cleanMatrix(matrix, m);

   std::cout << "Total time is " << t << std::endl;
   return length;
}

// Free the memory by deleting matrix
void cleanMatrix(int ** matrix, int size){
  for (int i = 0; i <= size; ++i)
  {
    delete [] matrix[i];
    matrix[i] = NULL;
  }
  delete[] matrix;
  matrix = NULL;
}

// Read the input file
char *getInput(const char * input_file){
  FILE *f = fopen(input_file, "r"); 

  // get the file size
  fseek(f, 0, SEEK_END);
  size_t size = ftell(f);
  rewind(f);

  // create a string and copy contents into this string
  char * str = new char[size + 1];
  fread(str, size, 1, f);

  fclose(f);  
  return str;
}

// Swaps pointers of two strings
void swapString(char **str1_ptr, char **str2_ptr)
{
    char *temp = *str1_ptr;
    *str1_ptr = *str2_ptr;
    *str2_ptr = temp;
} 

// Swap two numbers
void swapNum(int& num1, int& num2){
  int temp = num1;
  num1 = num2;
  num2 = temp;
}