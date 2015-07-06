#include <bits/stdc++.h>

using namespace std;

int pl, pr;
char lf[26], rf[26];
int wl, wr;
int att, des;
char a;
char temp[26];
int val, t, c;

void printBlank() {
    for (int i = 0; i < 8; i++)
        printf(".");
}

void print1() {
    printf(".../\\...");
}

void print2() {
    printf("../..\\..");
}

void print3() {
    printf("./....\\.");
}

void printSep() {
    printf("||");
}

void print4(char * ref) {
    printf("%s", ref);
}

void print5() {
    printf("\\");
    for (int i = 0; i < 6; i++)
        printf("_");
    printf("/");
}

int getVal (char a) {
    int val = 0;
//    printf("%c -> %d = %d\n", a, a, a - 'A' + 65);
    a = a - 'A' + 65;
    while (a != 0) {
        val += 1 + a%2;
        a /= 2;
    }
    return val;
}

int main () {
    scanf("%d ", &t);
    for (c = 1; c <= t; c++) {
        wl = wr = 0;
        pl = pr = -10;
        for (int i = 0; i < 8; i++) {
            scanf(" %s", temp);
            if (i == 7) continue;
            for (int j = 0; j < 8; j++) {
                a = temp[j];
                if (a == '.' || a == '_' || a == '-' ||  a == '\\');
                else if (a == '/') {
                    if (pl == -10)
                        pl = i;
                } else if (a >= 'A' && a <= 'Z') {
                    wl += getVal(a);
                    if (j > 1) continue;
                    for (int k = 0; k < 8; k++) {
                        lf[k] = temp[k];
                    }
                    lf[8] = '\0';
                }
            }
            for (int j = 0; j < 8; j++) {
                a = temp[j+10];
                if (a == '.' || a == '_' || a == '-' ||  a == '\\');
                else if (a == '/') {
                    if (pr == -10)
                        pr = i;
                } else if (a >= 'A' && a <= 'Z') {
                    wr += getVal(a);
                    if (j > 1) continue;
                    for (int k = 0; k < 8; k++) {
                        rf[k] = temp[k+10];
                    }
                    rf[8] = '\0';
                }
            }
        }
        
        if (pl > pr) att = -1;
        else if (pl == pr) att = 0;
        else att = 1;
        
        if (wl > wr) des = -1;
        else if (wl == wr) des = 0;
        else des = 1;

//        printf("p %d %d -> %d\n", pl, pr, att);
//        printf("w %d %d -> %d\n", wl, wr, des);
//            printf("%s\n", lf);
//            printf("%s\n", rf);
    
        printf("Case %d:\n", c);
        if (des == att) {
            printf("The figure is correct.\n");
        } else {
            if (des == -1) {
                printBlank();
                printSep();
                print1();
                printf("\n");

                printBlank();
                printSep();
                print2();
                printf("\n");

                print1();
                printSep();
                print3();
                printf("\n");

                print2();
                printSep();
                print4(rf);
                printf("\n");

                print3();
                printSep();
                print5();
                printf("\n");

                print4(lf);
                printSep();
                printBlank();
                printf("\n");
                
                print5();
                printSep();
                printBlank();
                printf("\n");
            } else if (des == 0) {
                printBlank();
                printSep();
                printBlank();
                printf("\n");

                print1();
                printSep();
                print1();
                printf("\n");

                print2();
                printSep();
                print2();
                printf("\n");

                print3();
                printSep();
                print3();
                printf("\n");

                print4(lf);
                printSep();
                print4(rf);
                printf("\n");

                print5();
                printSep();
                print5();
                printf("\n");
                
                printBlank();
                printSep();
                printBlank();
                printf("\n");
            } else {
                print1();
                printSep();
                printBlank();
                printf("\n");

                print2();
                printSep();
                printBlank();
                printf("\n");

                print3();
                printSep();
                print1();
                printf("\n");

                print4(lf);
                printSep();
                print2();
                printf("\n");

                print5();
                printSep();
                print3();
                printf("\n");

                printBlank();
                printSep();
                print4(rf);
                printf("\n");
                
                printBlank();
                printSep();
                print5();
                printf("\n");
            }
        }
    }
}
