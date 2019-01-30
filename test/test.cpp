#include <utility>
#include <iostream>
#include <fstream>
#include <vector>


// using namespace std;

// template <class T> void swap (T& a, T& b)
// {
//     T c(std::move(a)); a = std::move(b); b=std::move(c);
// }
template <class T, size_t N> void swap (T (&a)[N], T (&b)[N])
{
    for (size_t i = 0; i<N; ++i) swap (a[i],b[i]);
}

/* Swaps strings by swapping pointers */
void swap1(char **str1_ptr, char **str2_ptr)
{
    char *temp = *str1_ptr;
    *str1_ptr = *str2_ptr;
    *str2_ptr = temp;
}  

void swapNum(int& num1, int& num2){
  int temp = num1;
  num1 = num2;
  num2 = temp;
}

int main(int argc, char const *argv[])
{
    /* code */
    std::vector<char> v1;
    v1.push_back('a');
    v1.push_back('b');

    for (size_t i = 0; i < v1.size(); ++i)
    {
        std::cout << v1[i] << " ";
    }
    std::cout << std::endl;

    std::vector<char> v2;
    v2.push_back('c');
    v2.push_back('d');

    swap(v1, v2);

    for (size_t i = 0; i < v1.size(); ++i)
    {
        std::cout << v1[i] << " ";
    }
    std::cout << "\n";


    // char * str1 = "this text";
    // char * str2 = "another text";

    // std::cout << "str1 is ---- "<< str1 << std::endl;
    // //swap(str1, str2); // will not work

    // swap1(&str1, &str2);

    // std::cout << "str1 is ---- "<< str1 << std::endl;


    int a = 4;
    int b = 10;

    std::cout << "====== a is ---- "<< a << std::endl;
    swapNum(a, b);

    std::cout << "====== a is ---- "<< a << std::endl;


    int num = std::stoi("12");

    std::cout << "num is " << num << std::endl;



    // std::cout << "this is test" << std::endl;
    // std::cout << "Adding something simple\n";
    // std::cout << "another simple thing\n";
    return 0;
}