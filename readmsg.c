//Andrew ZiYu Wang, Alisa Sumwalt

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "stego.h"
#include "stego.c"

char* readMsg(FILE *fp);
int getLength(FILE *fp);
int readHeader(struct ppm *pi, FILE *fp);

int main(FILE *fp)
{ 
    struct ppm ppm;
    struct ppm *p = &ppm;
    if((fp = fopen("TU_modified.ppm", "r")) == NULL)
    {
        printf("Failed!");
        return 1;
    }
    readHeader(p,fp);
    char * message = readMsg(fp);

    fclose(fp);
    printf("%x", message);
    return 0;
   
}

char* readMsg(FILE *fp)
{
    int length = getLength(fp);
    printf("%x", length);
    char message[length * 8]; //message length (times 8 since each char is last bit of byte)
    int len = length; //copy of length 
    int j = 0;
    char byte = 0;
    while(len != 0);
    {
        //printf("h");
        for(int i = 7; i >= 0; i--) 
        {   
            byte = getc(fp);
            char c = byte >> i & 0x01; //getting the last bit of the byte
            message[j] = c; //putting that bit into the array
            j++;
        }
        len--;
    }
    char *m = message;
    return m;

}

int getLength(FILE *fp)
{
    int length;
    char lengthC[9];
    //char byte = 0;
    
    int j = 0;
    for(int i = 7; i >= 0; i--)
    {
        char c = getc(fp); //getting the length of the character by getting the last digit of the byte BUT GETC DOESNT TAKE TWO PARAM SO FIX TO READMSG method one 
        lengthC[j] = (c>>i & 0x01); //putting that character in length
        j++; 
    }
    length = (binConv(atoi(lengthC))); //getting the length of the message from the bytes and then converting it from character-> bits-> integer
    return length;
}








