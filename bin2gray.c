
/* bin2gray.c                                           */
/* A.Schmiedl , 2021-06-23                              */
/* Calculate 4-bit cyclic Gray code from 4-bit binary   */
/* https://www.elektormagazine.de/news/kurze-schaltung-binar-zu-gray-code */
/* Logic circuit: 4* 2-input-XOR gates, truth table:    */
/*     G0 = B0 xor B1 ,                                 */
/*     G1 = B1 xor B2 ,                                 */
/*     G2 = B2 xor B3 ,                                 */
/*     G3 = B3 xor 0  = B3                              */

#include <stdio.h>
#include <string.h>

static char buff[8];       // global string buffer for binary representation

void uint2bstr(unsigned num)  {        // convert to 8-character bin string
    unsigned a, b=7;
    for (a=0; a<8; a++)  {
        if(num & (1 << a))
            buff[b]='1';
        else
            buff[b]='0';
        b--;
    }
}

void main(void) {
    unsigned bnum, gray;
    for (bnum=0; bnum<16; bnum++)  {
        uint2bstr(bnum);
        printf("binary = %02x = %s ",bnum,buff);
        gray=bnum^(bnum>>1);           // calculate the gray code from binary
        uint2bstr(gray);
        printf(": graycode = %02x = %s \n",gray,buff);
    }
}

