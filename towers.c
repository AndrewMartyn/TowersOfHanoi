#include <stdlib.h>
#include <stdio.h>

// Structs
typedef struct Towers {
    int N;
    int numPegs;
    struct Peg * pegs;
} Towers;

typedef struct Peg {
    char name;
    int numDiscs;
    int * discs;
} Peg;


// Function Prototypes
Towers * createTowers(int N);
void move(char src, char dest);
void solve(int a, char src, char aux, char dest);
void show();

Towers * towers;

int main(int argc, char * argv[]) {
    // Check for arguments
    if(argc == 2) {
        int N = atoi(argv[1]);
        towers = createTowers(N);
        show();
        solve(N, 'A', 'B', 'C');
        show();
    } else {
        printf("Usage: towers.exe <NumberOfDiscs>\n");
    }

    return 0;
}

// Allocates and returns a Towers struct with an assumed numPegs of 3
Towers * createTowers(int N) {
    Towers * ret = (Towers*)malloc(sizeof(Towers));
    ret->N = N;
    ret->numPegs = 3;
    ret->pegs = malloc(ret->numPegs * sizeof *ret->pegs);

    for(int i = 0; i < ret->numPegs; i++) {
        ret->pegs[i].name = (char)65+i;
        ret->pegs[i].discs = malloc(N*sizeof(int));
        ret->pegs[i].numDiscs = 0;
        for(int j = 0; j < N; j++) 
            ret->pegs[i].discs[j] = -1;
    }

    int c = N;
    for(int i = 0; i < N; i++) {
        ret->pegs[0].discs[i] = c;
        c--;
    }
    ret->pegs[0].numDiscs = N;

    return ret;
}

// Move a disc from one peg to another and update structs
void move(char src, char dest) {
    if(towers->pegs[src-65].numDiscs < 1) 
        return;

    towers->pegs[dest-65].discs[towers->pegs[dest-65].numDiscs] = towers->pegs[src-65].discs[towers->pegs[src-65].numDiscs-1];
    towers->pegs[src-65].discs[towers->pegs[src-65].numDiscs-1] = -1;
    towers->pegs[src-65].numDiscs--;
    towers->pegs[dest-65].numDiscs++;
}

// Standard solve function
void solve(int a, char src, char aux, char dest) {
    if(a == 1) {
        move(src, dest);
        printf("Moved disc %d from %c to %c\n", a, src, dest);
        return;
    } else {
        solve(a-1, src, dest, aux);
        move(src, dest);
        printf("Moved disc %d from %c to %c\n", a, src, dest);
        solve(a-1, aux, src, dest);
    }
}

// Print the towers in a pretty ish way.
void show() {
    char str1[10], str2[10], str3[10];
    for(int i = towers->N-1; i >= 0; i--) {
        towers->pegs[0].discs[i] != -1 ? itoa(towers->pegs[0].discs[i], str1, 10) : strcpy(str1, "");
        towers->pegs[1].discs[i] != -1 ? itoa(towers->pegs[1].discs[i], str2, 10) : strcpy(str2, "");
        towers->pegs[2].discs[i] != -1 ? itoa(towers->pegs[2].discs[i], str3, 10) : strcpy(str3, "");

        printf("%s\t%s\t%s\n", str1, str2, str3);
    }
    printf("%c\t%c\t%c\n", towers->pegs[0].name, towers->pegs[1].name, towers->pegs[2].name);
}
