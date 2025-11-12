#include <stdio.h>
#include <string.h>

typedef struct {
    char descr[100];
    int c[6];
} TLoc;

typedef struct {
    char descr[50];
    int loc;
} TObj;

void printobjloc(TObj a[], int nobjs, int cloc) {
    for (int i=0;i<nobjs;i++) {
        if (a[i].loc == cloc)
            printf("Blepeis: %s\n", a[i].descr);
    }
}

void printinventory(TObj a[], int nobjs) {
    int empty = 1;
    printf("Exeis mazi sou:\n");
    for (int i=0;i<nobjs;i++) {
        if (a[i].loc == -2) {
            printf(" - %s\n", a[i].descr);
            empty = 0;
        }
    }
    if (empty) printf(" (tipota)\n");
}

int main(void) {
    TLoc a[5];
    TObj objs[4];
    char cmd[50], objname[50];
    int x=0, xx;

    strcpy(a[0].descr, "Eisai sto dasos. Blepeis ena monopati boreia.");
    strcpy(a[1].descr, "Eisai sto ksefwto. Blepeis monopatia notia,\n anatolika kai dytika kai mia skala se ena dentro.");
    strcpy(a[2].descr, "Eisai sth pediada. Ena monopati sta dytika odigei sto ksefwto.");
    strcpy(a[3].descr, "Eisai sthn oxthh enos potamou Ena monopati sta anatolika odhgei sto ksefwto.");
    strcpy(a[4].descr, "Brikes ena dentrospito. Blepeis notia to monopati pou irthes\n kai dytika thn oxthi enos potamou.");

    for (int i=0;i<6;i++){ for (int j=0;j<6;j++){ a[i].c[j]=-1;}}
    a[0].c[0]=1;
    a[1].c[1]=0;
    a[1].c[2]=2;
    a[1].c[3]=3;
    a[1].c[4]=4;
    a[2].c[3]=1;
    a[3].c[2]=1;
    a[4].c[5]=1;

    strcpy(objs[0].descr, "fanari"); objs[0].loc=2;
    strcpy(objs[1].descr, "kibwtio"); objs[1].loc=2;
    strcpy(objs[2].descr, "sako"); objs[2].loc=3;
    strcpy(objs[3].descr, "kyalia"); objs[3].loc=4;
    
    printf("\nKsekinas to paixnidi! Grapse entoles (BOREIA, NOTIA, ANATOLIKA, DYTIKA, ANEBA, KATEBA, PARE <obj>, ASE <obj>, KATALOGOS, TELOS)\n");

    do {
        printf("\n%s\n", a[x].descr);
        printobjloc(objs, 4, x);
        printf("> ");
        scanf(" %[^\n]", cmd);

        if (strcasecmp(cmd, "BOREIA")==0) xx=a[x].c[0];
        else if (strcasecmp(cmd, "NOTIA")==0) xx=a[x].c[1];
        else if (strcasecmp(cmd, "ANATOLIKA")==0) xx=a[x].c[2];
        else if (strcasecmp(cmd, "DYTIKA")==0) xx=a[x].c[3];
        else if (strcasecmp(cmd, "ANEBA")==0) xx=a[x].c[4];
        else if (strcasecmp(cmd, "KATEBA")==0) xx=a[x].c[5];
        else xx=-999;

        if (xx >= 0 && xx < 7) {
            x = xx;
            continue;
        } else if (xx == -1) {
            printf("Den mporeis apo ekei!\n");
            continue;
        }

        if (strncasecmp(cmd, "PARE", 4)==0) {
            sscanf(cmd+5, "%s", objname);
            int found=0;
            for (int i=0;i<4;i++) {
                if (objs[i].loc==x && strcasecmp(objs[i].descr,objname)==0) {
                    objs[i].loc=-2;
                    printf("Phres to %s.\n", objname);
                    found=1;
                    break;
                }
            }
            if (!found) printf("Den blepeis tetoio antikeimeno edw.\n");
        }
        else if (strncasecmp(cmd, "ASE", 3)==0) {
            sscanf(cmd+4, "%s", objname);
            int found=0;
            for (int i=0;i<4;i++) {
                if (objs[i].loc==-2 && strcasecmp(objs[i].descr,objname)==0) {
                    objs[i].loc=x;
                    printf("Afises to %s.\n", objname);
                    found=1;
                    break;
                }
            }
            if (!found) printf("Den exeis tetoio antikeimeno.\n");
        }
        else if (strcasecmp(cmd,"KATALOGOS")==0) {
            printinventory(objs,4);
        }
        else if (strcasecmp(cmd,"TELOS")==0) {
            break;
        }
        else {
            printf("Den katalavainw thn entolh.\n");
        }

    } while (1);

    printf("Telos paixnidiou.\n");
    return 0;
}