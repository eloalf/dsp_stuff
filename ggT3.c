
/*  g g T 3 . c                                                                               */
/*  Groesster gemeinsamer Teiler     = ggT  und                                               */
/*  Kleinstes gemeinsames Vielfaches = kgV  zweier langer Ganzzahlen                          */
/*  English terms:  "ggT" == "greatest common divisor" = "GCD"                                */
/*                  "kgV" == "least common multiple"   = "LCM"                                */
/*  Maximum der Eingabezahlen = (2^32)-1 = 4,294,967,295                                      */
/*  Alfred Schmiedl DL8NDQ, 2020-06-04                                                        */
/*  Compilerlauf:  gcc -o ggT3 ggT3.c                                                         */
/*  Anwendung:     ./ggT3 zahl1 zahl2                                                         */
/*  Quellen:                                                                                  */
/*      https://de.wikipedia.org/wiki/Kleinstes_gemeinsames_Vielfaches                        */
/*      https://jumk.de/formeln/kgv.shtml                                                     */
/*      https://de.wikibooks.org/wiki/C%2B%2B-Programmierung/_Br%C3%BCche/_Die_Methoden       */
/*      https://www.mathematik.de/analysis/177-erste-hilfe/                                   */
/*                               zahlenbereiche/nat%C3%BCrliche-zahlen/2311-kgv-und-ggt       */
/*  Entwicklung der Begriffe kgV und ggT: CF Gauss (1801) in: Disquisitiones Arithmeticae     */
/*  Anwendungen z.B. bei:                                                                     */
/*      Finden der PLL-Frequenz zur phasenstarren Kopplung zweier Frequenzen,                 */
/*      Interpolations-/Dezimations-Faktoren f. "Rational-Resampling-FIR"                     */

#include <stdio.h> 

unsigned long ggT(unsigned long a, unsigned long b)
{
    if (b == 0)  {
        return a;
    } else  {
          return(ggT(b, a%b ));     // die rekursive Variante
      }
}

int main(int argc, char *argv[])
{
    unsigned long x=1 ,y=1, kgV;

    if (argc != 3)  {
        printf("--> ggT3.c \n");
        printf("    DL8NDQ, Erlangen, 31.05.2020  \n");
        printf("    Ermittle ggT und kgV zweier positiver Ganzzahlen.  \n");
        printf("    Anwendung:  ./ggT3 zahl1 zahl2  \n");
        return(-1);
    }

    if (!(sscanf(argv[1],"%lu",&x)))  return(-2);
    if (!(sscanf(argv[2],"%lu",&y)))  return(-3);

    printf("ggT(%lu,%lu) = %lu  \n", x, y, ggT(x,y));
    kgV = (x*y) / ggT(x,y);
    printf("kgV(%lu,%lu) = %lu  \n", x, y, kgV);
    printf("%lu/%lu = %lu = Interpolationsfaktor \n", kgV, x, kgV/x);
    printf("%lu/%lu = %lu = Dezimations-Divisor  \n", kgV, y, kgV/y);
}
