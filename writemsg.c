//Andrew ZiYu Wang, Alisa Sumwalt 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "stego.h"
#include "stego.c"

void write_hidden_byte(char c, FILE *fp);
int readHeader(struct ppm *pi, FILE *fp);

int main()
{
    struct ppm ppm;
    struct ppm *p = &ppm;
    FILE * file;

    if((file = fopen("white640_480.ppm", "r")) == NULL)
    {
        printf("Failed!");
        return 1;
    }

    readHeader(p, file); //reads header and assigns values to struct

    //printf("%d", ppm.Maxval);
    if((ppm.Maxval != 255)) //checking ppm value
    {
        printf("Error");
        fclose(file);
        return 1;
    }

    //char length[4];
    char charM[102];
    
   
    printf("What message do you want to write? Max 99 characters ");
    scanf("%s", charM);

    int len = strlen(charM);
    printf("%d", len);
    char length[2];
    sprintf(length, "%c", len);
    printf("%c", length);

    
    strcpy(charM, length);
    printf("%x", charM);

    char *c = charM;

    while(*c != '\0')
    {
        write_hidden_byte(*c, file);
        c++;
    }

    fclose(file);

    free(c);
    return 0;
}


void write_hidden_byte(char c, FILE *fp) {
    char byte = 0;
    for (int i = 7; i >= 0; i--) {
        byte = getc(fp); // Read a byte
        ungetc(0, fp);   // Rewind the file pointer
        putc((byte & ~0x01) | ((c >> i) & 0x01), fp); // Write modified byte
        printf("f");
    }

}
           