#include <cstdio>

int hue (char * vet, int i, int * memo) {
    if (vet[i] == '\0') return memo[i] = 0;
    if (memo[i] != -2) return memo[i];
    if (vet[i] == '0') return memo[i] = -1; // não é pra chegar aqui nunca
    if (vet[i+1] == '0') {
        if (vet[i] != '1' && vet[i] != '2') return memo[i] = -1; // caso impossível
        else memo[i+2] = hue(vet, i+2, memo);

        // fuck case
        if (memo[i+2] > -1) return memo[i+2]+1;
        else return -1;
    }
    if (vet[i] == '1') {
        memo[i+1] = hue(vet, i+1, memo);
        if (memo[i+1] > -1) {
            memo[i+2] = hue(vet, i+2, memo);
        } else return -1;
        if (memo[i+2] > -1) {
            return memo[i+1] + memo[i+2];
        } else return -1;
    }

    if (vet[i] == '2') {
        if (vet[i+1] > '6') {
            memo[i+1] = hue(vet, i+1, memo);
            if (memo[i+1] > -1) return memo[i+1];
            else return -1;
        } else {
            memo[i+1] = hue(vet, i+1, memo);
            if (memo[i+1] > -1) {
                memo[i+2] = hue(vet, i+2, memo);
            } else return -1;
            if (memo[i+2] > -1) {
                return memo[i+1] + memo[i+2];
            } else return -1;
        }
    }
    else return memo[i+1] = hue(vet, i+1, memo);
}

int main () {
    char    codigo[5001];
    int     memo[5003];

    for (int i = 0; i < 5000; i++) {
        memo[i] = -2;
    }

    while(scanf(" %s", codigo) != EOF && codigo[0] != '0') {
        printf("%d\n", hue(codigo, 0, memo));
    }
}
