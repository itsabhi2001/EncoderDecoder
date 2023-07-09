//Abhimanyu Verma
//1216449273

using namespace std;

#include <iostream>
#include <fstream>
#include <string>  
#include "defns.h"

    void insertionSort(tree *arr, int n);//declaring functions from below
    void binaryTree(tree *arr, int n);
    void decode(symbol * sym, symbol * root, string line, int *index, int length);
    bool isLeaf(symbol *sym);
    void merge(tree *arr, int const left, int const mid, int const right);
    void mergeSort(tree * arr, int const begin, int const end);
    //void reverseString(string *input);
    void printBT(const std::string& prefix, symbol* sym, bool isLeft);

int main(int argc, char *argv[]){
    ifstream input_file;
        input_file.open(argv[1]);//first arguemnt used to open txt file
        
        symbol Symbols[NSYMBOLS] = {0};
        
        int index;
        int frequency;
        int letters = 0;
        int nums = 0;
        if(input_file.is_open()){
            while(input_file >> index >> frequency){
                if((index > 64 && index < 91) || (index > 96 && index < 123)){//counting Alpha and NonAlpha array sizes
                    letters++;
                }
                else{
                    nums++;
                }
                Symbols[index].symbol = (char)index;//initializing valies in symbols again form txt file
                Symbols[index].freq = frequency;
                Symbols[index].parent = nullptr;
                Symbols[index].left = nullptr;
                Symbols[index].right = nullptr;
                Symbols[index].encoding[0] = '\0';
            }
        }
        
        input_file.close();
        tree *Alpha = (tree*)malloc(letters*sizeof(tree));//dynamically allocated array
        tree *NonAlpha = (tree*)malloc(nums*sizeof(tree));
        
        for(int i = 0, j = 0, k = 0;i < NSYMBOLS; i++){//iterate through Symbols, j and k used for Alpha and NonAlpha indexes respectively
            if(Symbols[i].freq > 0){
                if((i > 64 && i < 91) || (i > 96 && i < 123)){
                    Alpha[j].index = i;//when alpha char found, initialize from Symbol struct at that index
                    Alpha[j].freq = Symbols[i].freq;
                    Alpha[j].symbol = (char)i;
                    Alpha[j].root = &(Symbols[i]);
                    j++;//advance to next index
                }
                else{//when non alpha char found, initialize from Symbol struct at that index
                    NonAlpha[k].index = i;
                    NonAlpha[k].freq = Symbols[i].freq;
                    NonAlpha[k].symbol = (char)i;
                    NonAlpha[k].root = &(Symbols[i]);
                    k++;//advance to next index
                }
            }
            
        }
        
       
        if((string)(argv[2]) == "insertion"){//cehck comnd line for insertion sort
            insertionSort(Alpha, letters);
            insertionSort(NonAlpha, nums);
        }
        else if((string)(argv[2]) == "merge"){//check command line for merge sort
            mergeSort(Alpha, 0, letters-1);
            mergeSort(NonAlpha, 0, nums - 1);
        }
        
        binaryTree(Alpha, letters);//create binary tree
        binaryTree(NonAlpha,nums);
        
        struct symbol Root;//create root node
        Root.parent = nullptr;
        Root.freq = Alpha[0].freq + NonAlpha[0].freq;
        Root.left = Alpha[0].root;
        Root.right = NonAlpha[0].root;
        Alpha[0].root->parent = &Root;
        NonAlpha[0].root->parent = &Root;

        //printBT("", &Root, false);  //prints the tree for debugging

        string line;
        int i = 0;
        while(cin){//cin through command line; the entire file into 1 string.
            std::getline(std::cin, 
                         line, 
                         std::string::traits_type::to_char_type(std::string::traits_type::eof()));
        }
        int length = line.length();
        decode(&Root, &Root, line, &i, length);

return 0;
}
void decode(symbol * sym, symbol * root, string line, int *index, int length){
    if(*index >= length){//end of string
        return;
    }
    if(line[*index] == '0'){
        index++;
        if(isLeaf(sym->left)){
            std::cout << sym->left->symbol;
            decode(root, root, line, index, length);
        }
        decode(sym->left, root, line, index, length);
    }
    else{
        index++;
        if(isLeaf(sym->right)){
            std::cout << sym->right->symbol;
            decode(root, root, line, index, length);
        }
        decode(sym->right, root, line, index, length);
    }
}
void binaryTree(tree *arr, int n){// builds binary tree
    
    
    struct symbol* t = (symbol*)malloc(sizeof(symbol));
    
    t->parent = nullptr;
    t->left = arr[0].root;
    t->right = arr[1].root;
    t->freq = arr[0].freq + arr[1].freq;
    
    arr[0].root->parent = t;
    arr[1].root->parent = t;
    
    
    if(n == 2){//last two nodes
        arr[0].root = t;
        arr[0].freq = t->freq;
        return;
    }
    int insertPnt = 0;
    

    for(int i = 2; i < n; i++){//deletion and finding insertion point
        if(arr[i].freq <= t->freq){
            insertPnt = i-1;
        }
        arr[i-2] = arr[i];
    }

    for(int i = n-1; i > insertPnt; i--){//insertion
        arr[i] = arr[i-1];
    }

    arr[insertPnt].root = t;
    arr[insertPnt].freq = t->freq;
    binaryTree(arr, (n-1));
}



bool isLeaf(symbol *sym){
    if(((sym->left) == nullptr)&&((sym->right) == nullptr)){//checks if node is a leaf node
        return true;
    }
    return false;
}


void printBT(const std::string& prefix, symbol* sym, bool isLeft)
{
    if( sym != nullptr )
    {
        std::cout << prefix;

        std::cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        std::cout << (sym->freq) << std::endl;

        // enter the next tree level - left and right branch
        printBT( prefix + (isLeft ? "|   " : "    "), sym->left, true);
        printBT( prefix + (isLeft ? "|   " : "    "), sym->right, false);
    }
}
void insertionSort(tree *arr, int n)//adjusted Instertion sort template
{
    struct tree key{};
    for (int i = 1; i < n; i++)
    {
        key = arr[i];
        int j = i - 1;
        
        while ((j >= 0 && arr[j].freq > key.freq) || (j >= 0 && arr[j].freq == key.freq && arr[j].index > key.index))
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
    
    
}

void merge(tree *arr, int const left, int const mid, int const right)//adjusted Merge sort template
{
    auto const leftArray = mid - left + 1;
    auto const rightArray = right - mid;
  
    tree *leftTree = (tree*)malloc(leftArray*sizeof(tree));
    tree *rightTree = (tree*)malloc(rightArray*sizeof(tree));

    for (int i = 0; i < leftArray; i++)
    {
        leftTree[i] = arr[left + i];
    }
        
    for (int j = 0; j < rightArray; j++)
    {
        rightTree[j] = arr[mid + 1 + j];
    }
        
  
    int i = 0;
    int j = 0; 
    int k = left; 
  
    while (i < leftArray && j < rightArray) {
        if ((leftTree[i].freq)<(rightTree[j].freq))
        {
            arr[k] = leftTree[i];
            i++;
        }
        else {
            arr[k] = rightTree[j];
            j++;
        }
        k++;
    }
    while (i < leftArray) {
        arr[k] = leftTree[i];
        i++;
        k++;
    }
    while (j < rightArray) {
        arr[k] = rightTree[j];
        j++;
        k++;
    }
}

void mergeSort(tree * arr, int const begin, int const end)
{
    if (begin < end){
        auto mid = begin + (end - begin) / 2;
        mergeSort(arr, begin, mid);
        mergeSort(arr, mid + 1, end);
        merge(arr, begin, mid, end);
    }
}