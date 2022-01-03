#include <stdio.h>
#include <stdlib.h>
#define ODDELOVACE ";"
#define POMLCKY "_"
#define VELIKOST 200
#define VSTUP "zbozi.txt"
#define VYSTUP "vysledovka.html"

void pomlcky(char*nazev){
char *pch = NULL;
char buffer[VELIKOST]= "";
pch = strtok(nazev, POMLCKY);
while(pch!=NULL){
    strcat(buffer,pch);
    strcat(buffer," ");
    pch=strtok(NULL, POMLCKY);
}
strcat(buffer, "\0");
strcpy(nazev, buffer);

}

typedef struct{
    char dodavatel[VELIKOST];
    char nazev[VELIKOST];
    int hmotnost;
    int pocet;
    float cena;
}ZBOZI;

int main(int argc, char ** argv)
{
    FILE *fp;
    char buffer[VELIKOST];
    int pocetRadku = 0;
    char *pch = NULL;
    ZBOZI *zbozi =NULL;
    int castCyklu = 0;
    int cenaCelkem =0;
    int hmotnostCelkem = 0;
    int maxCena = 0;

fp = fopen(VSTUP, "r");
if(fp == NULL){
    printf("soubor %s se nepodarilo otevrit. \n", VSTUP);
    return (EXIT_FAILURE);
}
while(fgets(buffer, VELIKOST, fp)!=NULL){
if(pocetRadku!=0){
    zbozi = (ZBOZI*)realloc(zbozi, pocetRadku *sizeof(ZBOZI));
    if(zbozi!=NULL){
    castCyklu = 1;
    pch = strtok(buffer, ODDELOVACE);
    while(pch!=0){
        switch(castCyklu){
            case 1:
                strcpy(zbozi[pocetRadku-1].dodavatel, pch);
                break;
            case 2:
                strcpy(zbozi[pocetRadku-1].nazev, pch);
            case 3:
                zbozi[pocetRadku-1].hmotnost =atoi(pch);
            case 4:
                zbozi[pocetRadku-1].pocet = atoi(pch);
            case 5:
                zbozi[pocetRadku-1].cena = atof(pch);


        }
        pch = strtok(NULL, ODDELOVACE);
        castCyklu++;
        }
    }
}pocetRadku ++;
}pocetRadku--;
    printf("UCTENKA\n");
    printf("--------------------------------------------------------------------\n");
    printf("DODAVATEL |        NAZEV     | HMOTNOST |POCET| CENA  | CELKOVA CENA |\n");
    printf("--------------------------------------------------------------------\n");
for(int i=0;i<pocetRadku;i++){
        if(zbozi[i].cena >zbozi[maxCena].cena){
            maxCena = i;
        }
    pomlcky(zbozi[i].nazev);
    printf("| %s | %21s | %5dg | %3d | %6.2f | %6.2f |\n", zbozi[i].dodavatel, zbozi[i].nazev, zbozi[i].hmotnost, zbozi[i].pocet,zbozi[i].cena, zbozi[i].pocet*zbozi[i].cena);
    cenaCelkem+=(zbozi[i].cena*zbozi[i].pocet);
    hmotnostCelkem+=(zbozi[i].hmotnost*zbozi[i].pocet);
}
printf("-----------------------------------------------------------------\n");
printf("\n");
printf("Celkova cena je %d \n", cenaCelkem);
printf("Celkova hmotnost je %dkg a %dg \n", hmotnostCelkem/1000, hmotnostCelkem%1000);
printf("Nejdrazsi polozka je %s za %3.2fkc", zbozi[maxCena].nazev, zbozi[maxCena].cena);


if(fclose(fp)==EOF){
    printf("soubor %s se nepodarilo uzavrit. \n", VSTUP);
    return (EXIT_FAILURE);
}
fp = fopen(VYSTUP, "w");
if(fp == NULL){
    printf("soubor %s se nepodarilo vytvorit. \n", VYSTUP);
    return (EXIT_FAILURE);
}
fprintf(fp,"<style>th, td {border:1px solid black;}</style>");
fprintf(fp, "<table><tr><th>dodavatel</th><th>nazev</th><th>hmotnost v gramech</th><th>cena jednoho ks</th></tr>");
for(int i=0;i<pocetRadku;i++){
         fprintf(fp, "<tr><td>%s</td><td>%s</td><td>%d</td><td>%.2f</td></tr>", zbozi[i].dodavatel, zbozi[i].nazev, zbozi[i].hmotnost, zbozi[i].pocet,zbozi[i].cena);
}
fprintf(fp, "</table>");

if(fclose(fp)==EOF){
    printf("soubor %s se nepodarilo uzavrit. \n", VYSTUP);
    return (EXIT_FAILURE);

}
else{
    printf("\nsoubor %s byl vytvoren \n", VYSTUP);
    return EXIT_SUCCESS;
}
}
