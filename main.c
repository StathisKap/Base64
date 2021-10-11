#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

bool padding;

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

char *string_to_binary(char * Sentence)
{
   int len = strlen(Sentence)*8;
    char * Sentence_in_binary = malloc(len+1);

    for(size_t i = 0 ; i < len+1; i++){
        strcat(Sentence_in_binary,char_to_binary(Sentence[i]));
    }
    Sentence_in_binary[len] = '\0';

    return Sentence_in_binary;
}

int binary_to_decimal(int n)
{
    int dec = 0, i = 0, rem = 0;

    while (n!=0) {
        rem = n % 10;
        n /= 10;
        dec += rem * pow(2, i);
        ++i;
    }
    return dec;
}

char * binary_string_to_base64(char * Sentence_in_binary)
{
    size_t len = strlen(Sentence_in_binary);
    char * Sentence_in_base64 = malloc(len/4);
    char * Sentence_in_base64_start = Sentence_in_base64;
    char * six_bit_chunks = malloc(6);
    
    for(size_t i = 0; i < len; i += 6){
        
        for(size_t j = 0; j < 6; j++)
        {
            if(i+j < len){
            six_bit_chunks[j] = Sentence_in_binary[i+j];
            six_bit_chunks[6] = '\0';
            }
            else{
            six_bit_chunks[i+j] = '\0';
            break;
            }
       }
        *Sentence_in_base64 = encoding_table[binary_to_decimal(atoi(six_bit_chunks))];
        Sentence_in_base64++;
    }
     
    return Sentence_in_base64_start;
}

char * base64_Encode(char * Sentence)
{
    int modulo = strlen(Sentence)%3;
    char *encoded_string = malloc(strlen(Sentence)+modulo+1);
    strcpy(encoded_string,binary_string_to_base64(string_to_binary(Sentence)));
    if(modulo > 0)
        while(modulo--)
            strcat(encoded_string,"=");
    return encoded_string;
}

int main(int argc, char * argv[])
{

    clock_t time1, time2;
    double time_elapsed;
    time1 = clock();
    char Sentence[] = "Hello there mister fantastic, mister boombastik, dara dara dara duuuuum";
    printf("\n%s",base64_Encode(Sentence));
    time2 = clock();
    time_elapsed = (time2 - time1)/(CLOCKS_PER_SEC / (double) 1000.0);
    printf("\n%.5f",time_elapsed);
    return 0;
}
