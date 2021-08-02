
/* lfsr.c                                                                          */
/* A.Schmiedl, DL8NDQ, 2019-01-27 2021-08-02                                       */
/* Function:                                                                       */
/*     Generates an MLS using a 16-bit register with Galois LFSR architecture,     */
/*     with 4 feedback taps and period of 65535 clock cycles.                      */
/*     Output of LFSR values are stored in "lfsr.log" and of bit stream (LSB of    */
/*     LFSR) as ASCII into file "lfsr.dat".                                        */
/*     Feedback of the bit values at the tap positions is done through a           */
/*     "Toggle mask", which mimicks the function of XOR gates: bits 15,13,12,10    */
/*     of shift register are inverted depending of the LSB bit value.              */
/* Compilation:                                                                    */
/*     Define constants in lfsr.c : SEEDV and POLYN then compile with:             */
/*         gcc -o lfsr lfsr.c                                                      */
/* Properties of the sequence:                                                     */
/*     Each possible bit pattern in LSFR is emerging just once, except 0x0000.     */
/*     Different seed values give shifted versions of the same sequence.           */
/*     Counting the run lengths of the longest stretches of 0s and 1s :            */
/*         grep -o 000000000000 lfsr.dat                                           */
/*     There are 8 matches of 12 0s in succession, 4 of 13 0s, 2 of 14 0s,         */
/*     1 match of 15 0s, and identical for the 1s, but with 1 additional           */
/*     stretch of 16 1s.                                                           */
/* Keywords:                                                                       */
/*     Maximum length sequence, Linear feedback shift register.                    */
/* Links for further reading about LFSR, Galois architecture, MLS:                 */
/*   https://en.wikipedia.org/wiki/Linear-feedback_shift_register                  */
/*   https://stackoverflow.com/questions/16891655/galois-lfsr-explanation-of-code  */
/*   http://courses.cse.tamu.edu/walker/csce680/lfsr_table.pdf                     */
/*   https://core.ac.uk/download/pdf/26192470.pdf                                  */
/*   https://users.ece.cmu.edu/~koopman/lfsr/                                      */
/*                                                                                 */
/* Further ideas worth pursueing:                                                  */
/*     *** Implementation of a digital filter to use the 0-/1-stream as +1/-1      */
/*         delta impulses for converting into an analog noise signal with          */
/*         visualisation afterwards.                                               */
/*     *** Experimenting with Gold codes: Make two uncorrelated 8-bit-MLS and      */
/*         XORing them to a Gold code.                                             */
/*         See here:                                                               */
/*         http://pages.hmc.edu/harris/class/e11/lect7.pdf  (from page 19)         */

#define   SEEDV  0xACE1u       /* Seed value for LFSR                              */
#define   POLYN  0xB400u       /* XOR taps = Toggle mask (bits 15,13,12,10 set)    */

#include  <stdint.h>
#include  <stdio.h>

char *bin2str(uint16_t regi)
{
    int b;
    static char strg[17];                   /* string must be static since it is needed in main() */
    for (int b=0; b<16; b++)
    {
        strg[15-b] = (regi & (1<<b)) ? '1' : '0';
    }
    strg[16] = '\0';
    return(strg);
}

int main(int argc, char* argv[])
{
    uint16_t lfsr = SEEDV;                /* Seed value of register with fixed length of 16 bits  */
    unsigned period = 0;                  /* Counter of shift operations                          */
    unsigned cnt0 = 0,    cnt1 = 0;       /* Counter of total zero and one bits                   */
    char *s="1010101010101010x";          /* 1-0-string of shift register, 17 bytes needed        */
    FILE *outf1=fopen("lfsr.dat","w");    /* Ausgabedatei fuer 1-0-Zeichenkette der Bitfolge      */
    FILE *outf2=fopen("lfsr.log","w");    /* Ausgabedatei fuer alle Werte des LFSR                */

    printf("-->   lfsr.c \n");
    printf("      16-bit MLS register (LFSR) with XOR taps at bits 15,13,12,10 \n");
    printf("      result see text files 'lfsr.dat' and 'lfsr.log' \n");

    s = bin2str(lfsr);                    /* Convert register to 1-0-string: here with seed value */
    fprintf(outf2, "-->   seed: %04X = %s ", lfsr, s);

    do {
        unsigned lsb = lfsr & 1;    /* Get LSB (the output bit) after shifting     */
        lfsr >>= 1;                 /* Arithmetic right shift of register          */
        if (lsb == 1) {             /* Only apply toggle mask if output bit was 1  */
            lfsr ^= POLYN;          /* Apply toggle mask (bits 15,13,12,10 set)    */
            fprintf(outf1,"1");
            cnt1++;
        }
        else  {
            fprintf(outf1,"0");
            cnt0++;
        }
        ++period;
        s = bin2str(lfsr);          /* Convert register to 1-0-string and write to log file   */
        fprintf(outf2, "\n%10d: %04X = %s ", period, lfsr, s);
    }  while(lfsr != SEEDV);        /* Terminate loop when seed value is resurfacing again    */

    fprintf(outf2, "\n--> number of 0 bits = %d , number of 1 bits = %d \n", cnt0, cnt1);
    fclose(outf1);
    fclose(outf2);
    return 0;
}
