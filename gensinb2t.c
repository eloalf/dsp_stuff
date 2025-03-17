
/*  g e n s i n b 2 t . c                                             */
/*  DL8NDQ, 16.03.2025                                                */
/*                                                                    */
/*  Programm zur Erzeugung eines gewobbelten Sinussignals             */
/*  mit Raised-Cosine-Fensterfunktion,                                */
/*  Ausgabe erfolgt nur auf "stdout",                                 */
/*  Es werden 8192 Werte erzeugt: 0.34133s Dauer bei 24kSps,          */
/*  Ausgabeformat wird gewaehlt als Eingabeformat f. "sox",           */
/*  inkl. 2 Headerzeilen:                                             */
/*     ; Sample Rate 24000                                            */
/*     ; Channels 1                                                   */
/*  Alle Folgezeilen enthalten jeweils:                               */
/*  Spalte 1 = Zeitpunkt des Abtastwertes ab 0.0s                     */
/*  Spalte 2 = Abtastwert, normalisiert auf +/-1.0                    */
/*                                                                    */
/*  Formatumwandlung und Soundausgabe erfordern Installation von SoX  */
/*  Verwendung am Beispiel mit Uebersetzung, Anzeige des Signal-      */
/*  Maximums, Soundausgabe:                                           */
/*     gcc -o gensinb2t gensinb2t.c -lm                               */
/*     ./gensinb2t > sin2.dat                                         */
/*     head -n 4092 sin2.dat | tail -n 40                             */
/*     sox -t dat sin2.dat -r 24000 -c 1 -b 16 sin2.wav               */
/*     play sin2.wav                                                  */
/*                                                                    */
/*  Hilfe wird ausgegeben bei Aufruf mit beliebigem Argument.         */

#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[])
{
   unsigned long NN = 8192;  /* Anzahl der Samples                    */
   unsigned long n = 0;      /* Laufvariable f. Abtastwert            */
   float EKO = 4.0;          /* Exponentialkoeffizient                */
   float smp;                /* Aktueller Abtastwert                  */
   float fdv, fv, amp;       /* Hilfsvariablen                        */

   if (argc==2)  {
      printf(" ---> gensinb2t.c                                            \n");
      printf("      DL8NDQ, 16.03.2025                                     \n");
      printf("      Signalburst wird numerisch auf Bildschirm ausgegeben:  \n");
      printf("      8192 Abtastwerte im Bereich -0.999 ... +0.999          \n");
      return -1;
   }

   n=0;

         /* Frequenzhilfsfaktor : Wird errechnet aus der Endfrequenz des  */
         /* Sweeps (noch keine Unterabtastung) und der gewuenschten       */
         /* Steilheit des Exponentialverlaufs: Typ. Werte f. EKO = 2..5 , */
         /* die Anfangsfrequenz des Sweeps ist damit variabel :           */
   fdv = (exp(EKO)-0.95) / 0.14;

   printf("; Sample Rate 24000\n; Channels 1\n");

   do
   {
         /* Amplitudenfenster: Raised-Cosine : */
      amp = 0.5 * (1.0-(cos((float)n/(float)NN * 2.0 * M_PI)));
         /* exponentiell ansteigender Frequenzverlauf : */
      fv = (exp((float)n/(float)NN*EKO) - 0.95) / fdv;
         /* Einfacher linear ansteigender Frequenzverlauf alternativ : */
   /* fv = (float)n / (float)NN / 10.0 + 0.05; */
      smp = amp * sin(fv*(float)n*M_PI);

      printf("%15.7f  %15.7f\n",((float)n/24000.),smp);
      n++;
   }
   while (n<NN);

   return 0;
}

