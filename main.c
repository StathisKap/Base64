#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "TestCode.h"

//**************************
//***BASE64 encoding table**
//**************************
static char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                '4', '5', '6', '7', '8', '9', '+', '/'};

char * char_to_binary(unsigned char c)
{
    char * letter_byte = malloc(sizeof(char)+1);
    
    for( int i = 7; i >= 0; i-- ){
        letter_byte[7-i] = (char)(( c >> i ) & 1 ? 1 : 0) + '0'; 
    }
    letter_byte[8] = '\0';
    return letter_byte;
}

char *string_to_binary(const char * Sentence)
{
    int len = sizeof(char)*strlen(Sentence)+1;
    char * Sentence_in_binary = malloc(len);
    
    for(size_t i = 0, len = strlen(Sentence); i < len; i++){
        strcat(Sentence_in_binary,char_to_binary(Sentence[i]));
    }
    Sentence_in_binary[len] = '\0';

    // printf("%s\n%ld\n\n",Sentence_in_binary,strlen(Sentence_in_binary));
    return Sentence_in_binary;
}

char * binary_to_decimal(int n)
{
    int dec = 0, i = 0, rem = 0;
    char *string_num = malloc(sizeof(char)*7);

    while (n!=0) {
        rem = n % 10;
        n /= 10;
        dec += rem * pow(2, i);
        ++i;
    }
    sprintf(string_num,"%d",dec);
    return string_num;
}

void binary_string_to_decimal_string(char * Sentence_in_binary)
{
    char * Sentence_in_decimal = malloc(strlen(Sentence_in_binary));
    char * six_bit_chunks = malloc(6);
    
    for(size_t i = 0, len = strlen(Sentence_in_binary); i < len; i = i + 6){
        
        for(size_t j = 0; j < 6; j++)
        {
            six_bit_chunks[j] = Sentence_in_binary[i+j];
            strcat(Sentence_in_decimal,binary_to_decimal(atoi(six_bit_chunks)));
            strcat(Sentence_in_decimal," ");
            // printf("\ni: %ld, j: %ld\n",i,j);
        }
        printf("\n%s\n",six_bit_chunks);
    }
    // printf("%s\n%ld\n\n",Sentence_in_decimal,strlen(Sentence_in_decimal));
}

int main()
{
   const char Sentence[] = "This a long sentence that I wanna encode into base64";
   
    binary_string_to_decimal_string(string_to_binary(Sentence));
    string_to_binary(Sentence);
  
   return 0;
}