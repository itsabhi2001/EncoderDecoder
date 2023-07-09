//Abhimanyu Verma
//1216449273

using namespace std;

#include <iostream>
#include <fstream>
#include <string>  
#include "defns.h" 

    int main(int argc, char *argv[]){

        std::string input_txt;
        
        while(cin){//cin through command line; the entire file into 1 string.
            std::getline(std::cin, 
                         input_txt, 
                         std::string::traits_type::to_char_type(std::string::traits_type::eof()));
        }
        
        struct symbol Symbols[NSYMBOLS];//create symbol struct for every ascii char

        for(int i = 0; i < NSYMBOLS; i++){//initialize sybol and freq on whole array
            Symbols[i].symbol = (char)i;
            Symbols[i].freq = 0;
        }
        
        for(int i=0; i < input_txt.length(); i++){//translated input file into ascii codes to count for Symbols.freq
            int j = (int)input_txt[i];
            Symbols[j].freq ++;
            
        }
        Symbols[10].freq ++;//new line at end
        
        for(int i = 0; i<NSYMBOLS; i++){//print out index and frequency
            if(Symbols[i].freq > 0){
                std::cout << i << "\t" << Symbols[i].freq << '\x0A';
            }
        }
        
        return 0;
    }
