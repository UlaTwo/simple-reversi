/*"Reversi"
 *Program zaliczeniowy - 1 semestr
 *autor: UlaTwo
 *data: 9.12.17
 */
#include <stdio.h>

#define WIERSZE 8
#define KOLUMNY 9

/******************************************************************************
*Wpisuje do tablicy pustą planszę(zapełnioną znakami: "-"), w ostatniej
 *kolumnie tablicy wpisuje cyfry oznaczające numer wiersza, wpisuje do
 *tablicy początkowe dwa piony białe(na pozycje d4 i e5) i dwa piony czarne
 *(na pozycje d5 i e4)
 */
void wejscie(char a[][KOLUMNY]) {
    int w=WIERSZE;
    int k;
    int pom='1';
    for(w=0; w<=WIERSZE-1; w++) {
        for(k=0; k<KOLUMNY-1; k++) {
            a[w][k]='-';
        }
        a[w][KOLUMNY-1]=pom;
        pom++;
    }
    a[3][3]='B';
    a[4][4]='B';
    a[3][4]='C';
    a[4][3]='C';
}

/******************************************************************************
 *Sprawdza poprawność dla danego koloru gracza (B lub C):
 *zwraca 1, jeśli ruch jest poprawny, zwraca 0, jeśli jest niepoprawny.
 */

int czyruchpoprawny(char A[][KOLUMNY],int achar, int bchar, int kolor) {

    /*achar-znak kolumny(litera); bchar-znak wiersza(cyfra)
     *sprawdza, czy dana achar jest z zakresu znaków a-h,
     *czy bchar jest z zakresu 1-8 oraz czy znakiem w tablicy
     *na tym miejscu jest znak pusty
     */

    if(achar<'a'||achar>'h'||bchar<'1'||bchar>'8'||A[bchar-'1'][achar-'a']!='-')
        return 0;
    else {
        int i,j,kolor2;
        i=bchar-'1';
        j=achar-'a';
        if(kolor=='B') kolor2='C';
        else kolor2='B';
        /*szukam możliwości ruchu we wszystkie osiem stron od
         *sprawdzanego pola, tj. sprawdzam, czy za sprawdzanym
         *polem jest przynajmniej jeden pion przeciwnika(lub więcej),
         *po którym jest pion grającego gracza
         */
        while (j<KOLUMNY-2 && A[i][j+1]==kolor2)j++;
        if(j!= achar-'a' && A[i][j+1]==kolor) return 1;
        j=achar-'a';

        while (j>0 && A[i][j-1]==kolor2) j--;
        if(j!=achar-'a' && j!=0)
            if( A[i][j-1]==kolor) return 1;
        j=achar-'a';

        while(i>0 && A[i-1][j]==kolor2) i--;
        if(i!=bchar-'1' && i!=0)
            if(A[i-1][j]==kolor) return 1;
        i=bchar-'1';

        while(i<WIERSZE-1 && A[i+1][j]==kolor2) i++;
        if(i!=bchar-'1' && i!=WIERSZE-1)
            if(A[i+1][j]==kolor) return 1;
        i=bchar-'1';

        while(i>0 && j<KOLUMNY-2 && A[i-1][j+1]==kolor2) {
            i--;
            j++;
        }
        if(i!=bchar-'1' && j!=achar-'a' && i!=0 && j!=KOLUMNY-2)
            if(A[i-1][j+1]==kolor) return 1;
        i=bchar-'1';
        j=achar-'a';

        while(i<WIERSZE-1 && j<KOLUMNY-2 && A[i+1][j+1]==kolor2) {
            i++;
            j++;
        }
        if(i!=bchar-'1' && j!=achar-'a' && i!=WIERSZE-1 && j!=KOLUMNY-2)
            if(A[i+1][j+1]==kolor) return 1;
        i=bchar-'1';
        j=achar-'a';

        while(i>0 && j>0 && A[i-1][j-1]==kolor2) {
            i--;
            j--;
        }
        if(i!=bchar-'1' && j!=achar-'a' && i!=0 && j!=0)
            if(A[i-1][j-1]==kolor) return 1;
        i=bchar-'1';
        j=achar-'a';

        while(i<WIERSZE-1 && j>0 && A[i+1][j-1]==kolor2) {
            i++;
            j--;
        }
        if(i!=bchar-'1' && j!=achar-'a' && i!=WIERSZE-1 && j!=0)
            if(A[i+1][j-1]==kolor) return 1;
        i=bchar-'1';
        j=achar-'a';

        /*jeżeli program doszedł do tego miejsca, to znaczy,
         *że żaden z powyższych warunków nie został spełniony,
         *więc ruch nie jest możliwy (funkcja zwraca 0)
         */
        return 0;
    }
}

/******************************************************************************
 *Ustawia na planszy na podanym polu pion grającego gracza i "odwraca"
 *(zamienia na przeciwny kolor piona) odpowiednie piony.
 *(argumenty jak w funkcji "czyruchpoprawny")
 */

void obroty(char A[][KOLUMNY],int achar, int bchar, int kolor) {
    int i, j, kolor2;
    i=bchar-'1';
    j=achar-'a';
    if (kolor=='B') kolor2='C';
    else kolor2='B';

    A[i][j]=kolor;

    while (j<KOLUMNY-2 && A[i][j+1]==kolor2)j++;
    if(j!= achar-'a' && A[i][j+1]==kolor) {
        while(j!=achar-'a') {
            A[i][j]=kolor;
            j--;
        }
    }
    j=achar-'a';

    while (j>0 && A[i][j-1]==kolor2) j--;
    if(j!=achar-'a' && j!=0)
        if( A[i][j-1]==kolor) {
            while(j!=achar-'a') {
                A[i][j]=kolor;
                j++;
            }
        }
    j=achar-'a';

    while(i>0 && A[i-1][j]==kolor2) i--;
    if(i!=bchar-'1' && i!=0)
        if(A[i-1][j]==kolor) {
            while(i!=bchar-'1') {
                A[i][j]=kolor;
                i++;
            }
        }
    i=bchar-'1';

    while(i<WIERSZE-1 && A[i+1][j]==kolor2) i++;
    if(i!=bchar-'1' && i!=WIERSZE-1)
        if(A[i+1][j]==kolor) {
            while(i!=bchar-'1') {
                A[i][j]=kolor;
                i--;
            }
        }
    i=bchar-'1';


    while(i>0 && j<KOLUMNY-2 && A[i-1][j+1]==kolor2) {
        i--;
        j++;
    }
    if(i!=bchar-'1' && j!=achar-'a' && i!=0 && j!=KOLUMNY-2)
        if(A[i-1][j+1]==kolor) {
            while(i!=bchar-'1' && j!=achar-'a') {
                A[i][j]=kolor;
                i++;
                j--;
            }
        }
    i=bchar-'1';
    j=achar-'a';
    while(i<WIERSZE-1 && j<KOLUMNY-2 && A[i+1][j+1]==kolor2) {
        i++;
        j++;
    }
    if(i!=bchar-'1' && j!=achar-'a' && i!=WIERSZE-1 && j!=KOLUMNY-2)
        if(A[i+1][j+1]==kolor) {
            while(i!=bchar-'1' && j!=achar-'a') {
                A[i][j]=kolor;
                i--;
                j--;
            }
        }
    i=bchar-'1';
    j=achar-'a';

    while(i>0 && j>0 && A[i-1][j-1]==kolor2) {
        i--;
        j--;
    }
    if(i!=bchar-'1' && j!=achar-'a' && i!=0 && j!=0)
        if(A[i-1][j-1]==kolor) {
            while(i!=bchar-'1' && j!=achar-'a') {
                A[i][j]=kolor;
                i++;
                j++;
            }
        }
    i=bchar-'1';
    j=achar-'a';
    while(i<WIERSZE-1 && j>0 && A[i+1][j-1]==kolor2) {
        i++;
        j--;
    }
    if(i!=bchar-'1' && j!=achar-'a' && i!=WIERSZE-1 && j!=0)
        if(A[i+1][j-1]==kolor) {
            while(i!=bchar-'1' && j!=achar-'a') {
                A[i][j]=kolor;
                i--;
                j++;
            }
        }
    i=bchar-'1';
    j=achar-'a';
}

/******************************************************************************
 *Sprawdza ile pionów zostanie obróconych po podanym ruchu gracza
 *(argumenty jak w funkcji "czyruchpoprawny")
 */

int ocenaruchu(char A[][KOLUMNY],int achar, int bchar, int kolor) {
    int i, j, kolor2;
    int wynik=0;
    i=bchar-'1';
    j=achar-'a';
    if (kolor=='B') kolor2='C';
    else kolor2='B';

    while (j<KOLUMNY-2 && A[i][j+1]==kolor2)j++;
    if(j!= achar-'a' && A[i][j+1]==kolor) {
        while(j!=achar-'a') {
            wynik++;
            j--;
        }
    }
    j=achar-'a';

    while (j>0 && A[i][j-1]==kolor2) j--;
    if(j!=achar-'a' && j!=0)
        if( A[i][j-1]==kolor) {
            while(j!=achar-'a') {
                wynik++;
                j++;
            }
        }
    j=achar-'a';

    while(i>0 && A[i-1][j]==kolor2) i--;
    if(i!=bchar-'1' && i!=0)
        if(A[i-1][j]==kolor) {
            while(i!=bchar-'1') {
                wynik++;
                i++;
            }
        }
    i=bchar-'1';

    while(i<WIERSZE-1 && A[i+1][j]==kolor2) i++;
    if(i!=bchar-'1' && i!=WIERSZE-1)
        if(A[i+1][j]==kolor) {
            while(i!=bchar-'1') {
                wynik++;
                i--;
            }
        }
    i=bchar-'1';

    while(i>0 && j<KOLUMNY-2 && A[i-1][j+1]==kolor2) {
        i--;
        j++;
    }
    if(i!=bchar-'1' && j!=achar-'a' && i!=0 && j!=KOLUMNY-2)
        if(A[i-1][j+1]==kolor) {
            while(i!=bchar-'1' && j!=achar-'a') {
                wynik++;
                i++;
                j--;
            }
        }
    i=bchar-'1';
    j=achar-'a';

    while(i<WIERSZE-1 && j<KOLUMNY-2 && A[i+1][j+1]==kolor2) {
        i++;
        j++;
    }
    if(i!=bchar-'1' && j!=achar-'a' && i!=WIERSZE-1 && j!=KOLUMNY-2)
        if(A[i+1][j+1]==kolor) {
            while(i!=bchar-'1' && j!=achar-'a') {
                wynik++;
                i--;
                j--;
            }
        }
    i=bchar-'1';
    j=achar-'a';

    while(i>0 && j>0 && A[i-1][j-1]==kolor2) {
        i--;
        j--;
    }
    if(i!=bchar-'1' && j!=achar-'a' && i!=0 && j!=0)
        if(A[i-1][j-1]==kolor) {
            while(i!=bchar-'1' && j!=achar-'a') {
                wynik++;
                i++;
                j++;
            }
        }
    i=bchar-'1';
    j=achar-'a';

    while(i<WIERSZE-1 && j>0 && A[i+1][j-1]==kolor2) {
        i++;
        j--;
    }
    if(i!=bchar-'1' && j!=achar-'a' && i!=WIERSZE-1 && j!=0)
        if(A[i+1][j-1]==kolor) {
            while(i!=bchar-'1' && j!=achar-'a') {
                wynik++;
                i--;
                j++;
            }
        }
    i=bchar-'1';
    j=achar-'a';

    return wynik;
}

/******************************************************************************
 *Liczy różnicę między liczbą czarnych a liczbą białych pionów na planszy
 */
int ocenaplanszy(char A[][KOLUMNY]) {
    int czarne=0;
    int biale=0;
    int i=0,j=0;
    for(i=0; i<WIERSZE; i++) {
        for(j=0; j<KOLUMNY-1; j++) {
            if(A[i][j]=='B') biale++;
            if(A[i][j]=='C') czarne++;
        }
    }
    return (czarne-biale);
}

/******************************************************************************
 *Wypisuje tablicę i ciąg liter od a do h oznaczających kolumny planszy
 */
void pisztablice(char a[][KOLUMNY]) {
    int k;
    int i;
    int pom;
    for(i=0; i<=WIERSZE-1; i++) {
        for(k=0; k<=KOLUMNY-1; k++) {
            putchar(a[i][k]);
        }
        putchar('\n');
    }

    pom='a';
    for(i=0; i<=WIERSZE-1; i++) {
        putchar(pom);
        pom++;
    }
    putchar('\n');

}

/******************************************************************************
* Znajduje ruch, który powinien wykonać program. Wynik jest zwracany w formie
* liczby trzycyfrowej, której cyfra dziesiątek jest równa indeksowi wiersza,
* a cyfra jedności indeksowi kolumny ruchu programu.
*/
int ruchprogramu(char A[][KOLUMNY]) {
    int i,j;
    int k=0;
    /* W pomocniczej tablicy B zapisuje wszystkie możliwe do wykonania
     * ruchy gracza białego
     */
    int B[WIERSZE*(KOLUMNY-1)][3];
    for(i=0; i<WIERSZE; i++) {
        for(j=0; j<KOLUMNY-1; j++) {
            if(czyruchpoprawny(A,j+'a',i+'1','B')==1) {
                B[k][0]=i;
                B[k][1]=j;
                B[k][2]=ocenaruchu(A,j+'a',i+'1','B');
                k++;
            }
        }
    }

    //uzupełnia -1 nieużywaną część tablicy B
    for(i=k; i<64; i++) {
        B[i][0]=-1;
        B[i][1]=-1;
        B[i][2]=-1;
    }

    //sprawdza, czy istnieje jakikolwiek możliwy ruch, jeśli nie zwraca 0
    if(B[0][0]==-1) return 0;

    //szuka maksymalnej oceny strategi
    int max=0;
    for(i=0; i<k; i++) if(B[i][2]>max) max=B[i][2];

    //W tablicy C wpisuje indeksy ruchów o maksymalnej ocenie strategii
    int C[WIERSZE*(KOLUMNY-1)][2];

    j=0;
    for(i=0; i<k; i++) {
        if(B[i][2]==max) {
            C[j][0]=B[i][0];
            C[j][1]=B[i][1];
            j++;
        }
    }

    //uzupełniam -1 nieużywaną część tablicy C
    for(i=j; i<WIERSZE*(KOLUMNY-1); i++) {
        C[i][0]=-1;
        C[i][1]=-1;
    }

    //sortuje wiersze w tablicy C od najmniejszego indeksu wiersza ruchu
    int l,pom1,pom2;
    for(i=0; i<j-1; i++) {
        for(l=0; l<j-1; l++) {
            if(C[l][0]>C[l+1][0]) {
                pom1=C[l][0];
                pom2=C[l][1];
                C[l][0]=C[l+1][0];
                C[l][1]=C[l+1][1];
                C[l+1][0]=pom1;
                C[l+1][1]=pom2;
            }
        }

    }

    /*sortuję w tablicy C wiersze, w których indeks wiersza ruchu jest najmniejszy,
     *według wartości indeksu kolumny ruchu
     */
    int d=0;
    while(C[d][0]==C[d+1][0]) d++;
    for(i=0; i<d+1; i++) {
        for(l=0; l<d; l++) {
            if(C[l][1]>C[l+1][1]) {
                pom1=C[l][0];
                pom2=C[l][1];
                C[l][0]=C[l+1][0];
                C[l][1]=C[l+1][1];
                C[l+1][0]=pom1;
                C[l+1][1]=pom2;
            }
        }

    }

    int wynik;
    wynik = 100+(C[0][0]*10)+C[0][1];
    return wynik;

}

/******************************************************************************
 *zamienia wynik z ruchuprogramu na liczbę reprezentującą w ASCII
 *literę kolumny wyniku
 */
int wyjsciewiersz(int t) {
    int d;
    d=(t/10)-10;
    return d+'1';
}
/******************************************************************************
 *zamienia wynik z ruchuprogramu na liczbę reprezentującą w ASCII
 *cyfrę wiersza wyniku
 */
int wyjsciekolumna(int t) {
    int j;
    j=t%10;
    return j+'a';
}
/******************************************************************************
 * Wypisuje planszę początkową, zczytuje dane z wejścia,
 * rozważa wszystkie możliwe warianty podanych danych i w zależności od nich
 * wypisuje dane wyjściowe.
 */
int main(void) {
    char A[WIERSZE][KOLUMNY];
    wejscie(A);
    pisztablice(A);
    int a,b,c,czy,t,w,k;
    a=getchar();
    while(a!=EOF) {
        if(a!='\n') {
            b=getchar();
            if(b=='\n') {
                if(a=='=') {
                    printf("= ");
                    t=ruchprogramu(A);
                    if (t==0) {
                        printf("=");
                    }
                    else {
                        // gdy przeciwnik pasuje i ruch programu jest mozliwy
                        k=wyjsciekolumna(t);
                        w=wyjsciewiersz(t);
                        putchar(k);
                        putchar(w);
                        obroty(A,k,w,'B');
                    }
                }
                else {
                    printf("?");
                }
            }
            else {
                c=getchar();
                if(c!='\n') {
                    printf("?");
                    while (c!='\n') c=getchar();
                }
                else {
                    czy=czyruchpoprawny(A,a,b,'C');
                    if(czy==1) {
                        //gdy przeciwnik podał poprawny ruch, nie będący rezygnacją
                        putchar(a);
                        putchar(b);
                        printf(" ");
                        obroty(A,a,b,'C');
                        t=ruchprogramu(A);
                        if (t==0) printf("="); //program rezygnuje z ruchu
                        else {
                            //wykonuje ruch programu
                            k=wyjsciekolumna(t);
                            w=wyjsciewiersz(t);
                            putchar(k);
                            putchar(w);
                            obroty(A,k,w,'B');
                        }
                    }
                    else printf("?");
                }
            }
            printf(" %d",ocenaplanszy(A));
            printf("\n");
            pisztablice(A);
            a=getchar();
        }
        else {
            // gdy wiersz polecenia jest pusty
            printf("?");
            printf(" %d",ocenaplanszy(A));
            printf("\n");
            pisztablice(A);
            a=getchar();
        }
    }
    return 0;
}
