#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    int idC;
    char *nume;
} cartier;

typedef struct
{
    int idP, adresa[18], idC, strada, numar;
    int prioritate;
    float greutate;
    char *mesaj;
    int cod_mesaj;
} pachet;

typedef struct
{
    int idC, nP;
    int p_distrib[50];
} postas;

/*functia de citire pentru datele problemei*/
void citire(int *nrC, int *nrP, cartier cartiere[], pachet pachete[])
{
    /*citesc numarul de cartiere*/
    scanf("%d", nrC);

    int i;
    for (i = 0; i < (*nrC); i++)
    {
        cartiere[i].idC = i; /*completez id-ul cartierului*/

        /*aloc dinamic memorie pentru sirul de caractere ce reprezinta numele
        cartierului*/
        cartiere[i].nume = malloc(200 * sizeof(char));
        scanf("%s", cartiere[i].nume);

        /*dupa ce am citit sirul de caractere si stiu lungimea exacta a
        numelui, realoc dinamic memoria acestuia astfel incat sa fie exact
        spatiul necesar*/
        int l = strlen(cartiere[i].nume);
        cartiere[i].nume = realloc(cartiere[i].nume, (l + 1) * sizeof(char));
        cartiere[i].nume[l] = '\0'; /*marchez sfarsitul sirului*/
    }

    /*citesc numarul de pachete*/
    scanf("%d", nrP);

    for (i = 0; i < (*nrP); i++)
    {
        pachete[i].idP = i; /*completez id-ul pachetului*/

        int j;
        for (j = 0; j < 18; j++) /*citesc vectorul adresa al pachetului*/
            scanf("%d", &pachete[i].adresa[j]);

        /*citesc valoarea prioritatii si a greutatii pachetului*/
        scanf("%d", &pachete[i].prioritate);
        scanf("%f", &pachete[i].greutate);

        /*similar cu abordarea pentru numele cartierelor, inital aloc dinamic
        mai multa memorie decat este necesar pentru mesajul pachetului, il
        citesc si ii aflu lungimea, iar apoi realoc dinamic memoria acestuia,
        astfel incat sa ocupe exact spatiul necesar in memorie*/
        pachete[i].mesaj = malloc(200 * sizeof(char));
        getchar();
        fgets(pachete[i].mesaj, 200, stdin);

        int l = strlen(pachete[i].mesaj);
        pachete[i].mesaj = realloc(pachete[i].mesaj, (l + 1) * sizeof(char));
        pachete[i].mesaj[l] = '\0'; /*marchez sfarsitul sirului*/
    }
}

/*functia de afisare pentru cerinta 1*/
void afisare_c1(int nrC, int nrP, cartier cartiere[], pachet pachete[])
{
    int i;
    for (i = 0; i < nrC; i++)
        printf("%d %s\n", cartiere[i].idC, cartiere[i].nume);

    for (i = 0; i < nrP; i++)
    {
        printf("%d\n", pachete[i].idP);

        int j;
        for (j = 0; j < 17; j++)
            printf("%d ", pachete[i].adresa[j]);
        printf("%d\n", pachete[i].adresa[17]);
        printf("%d %.3f\n", pachete[i].prioritate, pachete[i].greutate);
        printf("%s", pachete[i].mesaj);
    }
}

/*functia de extragere a datelor din vectorul adresa al unui pachet*/
pachet extragere(pachet p)
{
    int i;

    p.idC = 0;
    p.strada = 0;
    p.numar = 0;

    /*variabila care reprezinta puterea lui 2 corespunzatoare bitului*/
    int pdoi = 1;
    /*pentru id-ul cartierului in care pachetul va fi livrat, merg descrescator
    de la pozitia 4 pana la 0 din vectorul adresa si calculez in baza 10
    numarul reprezentat in baza 2*/
    for (i = 4; i >= 0; i--)
    {
        /*daca valoarea din vector este 1 atunci la valorea id-ului cartierului
        se aduna puterea lui 2 corespunzatoare, in caz contrar se aduna 0*/
        p.idC = p.idC + p.adresa[i] * pdoi;
        pdoi *= 2; /*pdoi se inmulteste cu cu 2 de fiecare data*/
    }

    pdoi = 1; /*variabila pdoi primeste din nou valoarea 1*/
    /*in mod analog cu aflarea id-ului cartierului, aflu strada pe care va fi
    livrat pachetul. Merg descrescator de la pozitia 9 pana la pozitia 5 din
    vectorul adresa si calculez strada*/
    for (i = 9; i >= 5; i--)
    {
        p.strada = p.strada + p.adresa[i] * pdoi;
        pdoi *= 2;
    }

    /*analog cu operatiile efectuate anterior, calculez numarul la care va fi
    livrat pachetul, de data aceasta mergand descrescator de la pozitia 17 pana
    la pozitia 10*/
    pdoi = 1;
    for (i = 17; i >= 10; i--)
    {
        p.numar = p.numar + p.adresa[i] * pdoi;
        pdoi *= 2;
    }

    /*returnez pachetul p cu campurile corespunzatoare completate*/
    return p;
}

/*functia de afisare pentru cerinta 2*/
void afisare_c2(int nrP, pachet pachete[])
{
    int i;
    for (i = 0; i < nrP; i++)
    {
        printf("%d\n", pachete[i].idP);
        printf("%d %d %d\n", pachete[i].idC, pachete[i].strada, pachete[i].numar);
    }
}

/*functia de distribuire a pachetelor*/
void distributie(int nrC, int nrP, pachet pachete[], postas postasi[])
{
    int i;

    /*completez id-ul postasilor, care este acelasi cu id-ul cartierului in
    care va livra pachetele*/
    for (i = 0; i < nrC; i++)
    {
        postasi[i].idC = i;
        postasi[i].nP = 0; /*initializez nr de pachete livrate de postas cu 0*/
    }

    for (i = 0; i < nrP; i++) /*parcurg vectorul de pachete*/
    {
        /*iau id-ul cartierului in care va fi livrat pachetul*/
        int j = pachete[i].idC;
        /*adaug id-ul pachetului in vectorul postasului cu pachete de distribuit*/
        postasi[j].p_distrib[postasi[j].nP] = pachete[i].idP;
        /*cresc numarul de pachete pe care le va distribui postasul*/
        postasi[j].nP++;
    }
}

/*functia de afisare pentru cerintele 3 si 4*/
void afisare_c3_c4(int nrC, postas postasi[])
{
    int i;
    for (i = 0; i < nrC; i++)
    {
        printf("%d %d\n", postasi[i].idC, postasi[i].nP);

        if (postasi[i].nP > 0)
        {
            int j;
            for (j = 0; j < postasi[i].nP - 1; j++)
                printf("%d ", postasi[i].p_distrib[j]);

            printf("%d", postasi[i].p_distrib[postasi[i].nP - 1]);
            printf("\n");
        }
    }
}

/*functia de sortare a pachetelor postasilor*/
void sortare(int nrP, int idP[], pachet pachete[])
{
    /*nrP - numarul de pachete ale unui postas
    idP[] - vectorul cu indicii pachetelor pe care livreaza postasul*/
    int i;
    for (i = 0; i < nrP - 1; i++)
    {
        int j;
        for (j = i + 1; j < nrP; j++)
            if (pachete[idP[i]].prioritate < pachete[idP[j]].prioritate)
            {
                /*daca prioritatea pachetului coresp id-ului de pe pozitia i
                este mai mica decat a celui de pe poz j atunci interschimb
                valorile id-urilor pachetelor*/
                int aux = idP[i];
                idP[i] = idP[j];
                idP[j] = aux;
            }
            else if (pachete[idP[i]].prioritate == pachete[idP[j]].prioritate)
            {
                if (pachete[idP[i]].greutate < pachete[idP[j]].greutate)
                {
                    /*daca prioritatile sunt egale, dar greutatea pachetului
                    coresp id-ului de pe pozitia i este mai mica decat a celui
                    de pe poz j atunci interschimb valorile id-urilor pachetelor*/
                    int aux = idP[i];
                    idP[i] = idP[j];
                    idP[j] = aux;
                }
            }
    }
}

/*functia de inversare a ordinii cuvintelor si eliminare a semnelor de
punctuatia pentru un mesaj*/
char *inversare_text(char *mesaj)
{
    /*aloc dinamic un sir de caractere ce va contine mesajul inversat
    si fara semne de punctuatie*/
    int l = strlen(mesaj);
    char *invers = malloc((l + 1) * sizeof(char));
    invers[0] = '\0';

    /*st- indice care marcheaza inceputul unui cuvant, dr- marcheaza sfarsitul
    unui cuvant, k- variabila care tine minte lungimea lui invers*/
    int st, dr, k = 0;
    st = dr = l - 1; /*parcurg sirul de la final, astfel st si dr sunt initial l-1*/

    /*scad indicii st si dr pentru a fi sigura ca pornesc de pe litera, numar
    sau caracter '-'*/
    while (isalnum(mesaj[st]) == 0 && mesaj[st] != '-')
    {
        st--;
        dr--;
    }

    while (st >= 0)
    {
        /*daca caracterul nu este litera mica, mare, numar sau caracterul '-'*/
        if (isalnum(mesaj[st]) == 0 && mesaj[st] != '-')
        {
            int i;
            /*copiez cuvantul dintre indicii st+1 si dr in vectorul invers*/
            for (i = st + 1; i <= dr; i++)
                invers[k++] = mesaj[i];

            /*scad indicele st pentru a fi sigura ca urmatorul cuvant se va
            termina intr-o litera, numar sau caracter '-'*/
            while (isalnum(mesaj[st]) == 0 && mesaj[st] != '-')
                st--;

            dr = st; /*setez indicele pentru final de cuvant*/
        }
        else
            st--; /*altfel scad indicele st*/
    }

    /*daca ies din while sirul mesaj incepe cu o litera, numar sau caracter '-'
    atunci copiez primul cuvant din mesaj in invers*/
    if (isalnum(mesaj[0]) || mesaj[0] == '-')
    {
        int i;
        for (i = 0; i <= dr; i++)
            invers[k++] = mesaj[i];
    }

    invers[k] = '\0';      /*marchez sfarsitul sirului*/
    strcpy(mesaj, invers); /*copiez sirul invers in sirul mesaj*/
    free(invers);          /*eliberez memoria pentru sirul invers*/

    return mesaj; /*returnez sirul mesaj modificat corespunzator*/
}

/*functia de codificare a mesajului unui pachet*/
int codificare_mesaj(pachet p)
{
    int cod = 0, l = strlen(p.mesaj);
    int i;
    /*calculez codul intermediar, care este suma codurilor ascii al caracterelor
    din p.mesaj si pozitia lor*/
    for (i = 0; i < l; i++)
        cod += (int)p.mesaj[i] * i;

    /*calculez codul final conform formulei*/
    p.cod_mesaj = cod % (p.numar * p.strada + 1);
    return p.cod_mesaj; /*returnez codul mesajului*/
}

/*functia de afisare pentru cerinta 5*/
void afisare_c5(int nrC, int nrP, postas postasi[], pachet pachete[])
{
    int i;
    for (i = 0; i < nrC; i++)
    {
        printf("%d %d\n", postasi[i].idC, postasi[i].nP);

        if (postasi[i].nP > 0)
        {
            int j;
            for (j = 0; j < postasi[i].nP; j++)
            {
                int k = postasi[i].p_distrib[j];
                printf("%d %d\n", k, pachete[k].cod_mesaj);
            }
        }
    }
}

/*functia de alterare a codului unui pachet*/
int algoritm_alterare_cod(int id, int cod)
{
    /*daca id ul este 0, postasul modifica bitul paritatii*/
    if (id == 0)
    {
        if (cod % 2 == 0)
            cod++; /*daca codul este par, il incrementez*/
        else
            cod--;  /*daca este impar, il decrementez*/
        return cod; /*returnez valorea alterata*/
    }

    if (id == 1)
    {
        if (cod & (1 << 1)) /*daca bitul de pe pozitia 1 este 1 il fac 0*/
            cod &= ~(1 << 1);
        else
            cod |= (1 << 1); /*altfel bitul este 0 si il fac 1*/
        return cod;          /*returnez valorea alterata*/
    }

    int d = 2; /*variabila divizor pentru id*/
    /*descompun in factori primi id-ul postasului*/
    while (id > 1)
    {
        int exp = 0;
        /*cat timp d este divizor pentru id, id se imparte prin d si exp creste*/
        while (id % d == 0)
        {
            id /= d;
            exp++;
        }

        if (exp > 0 && d <= 31) /*daca d este divizor pentru id si <= 31*/
        {
            if (cod & (1 << d)) /*daca bitul de pe pozitia d este 1 il fac 0*/
                cod &= ~(1 << d);
            else
                cod |= (1 << d); /*altfel bitul este 0 si il fac 1*/
        }

        d = d + 1 + d % 2; /*il cresc pe d*/
    }

    return cod; /*returnez codul modificat*/
}

/*functia in care verific daca codul mesajului pachetelor unui postas poate fi
alterat*/
void alterare_cod(int nrP, postas P, pachet pachete[])
{
    int j;
    /*parcurg pachetele pe care distribuie P*/
    for (j = 0; j < P.nP; j++)
    {
        /*afisez indicele pachetului*/
        printf("%d ", P.p_distrib[j]);

        int k = P.p_distrib[j];         /*retin indicele pachetului*/
        int id = P.idC, ok = 0;         /*retin indicele cartierului*/
        int cod = pachete[k].cod_mesaj; /*retin codul mesajului*/
        while (cod > 0 && ok == 0)
        {
            /*daca id ul e de o cifra si se gaseste in cod atunci ok ia val 1*/
            if (id < 10 && cod % 10 == id)
                ok = 1;
            else if (id > 9 && (cod % 10 == id / 10 || cod % 10 == id % 10))
                ok = 1; /*daca id-ul e de doua cifra si una dintre ele se
                          gaseste in cod atunci ok ia valoarea 1*/
            cod /= 10;
        }

        cod = pachete[k].cod_mesaj;
        /*daca ok este 1 atunci postasul va altera codul*/
        if (ok == 1)
            pachete[k].cod_mesaj = algoritm_alterare_cod(id, cod);

        /*afisez codul mesajului*/
        printf("%d\n", pachete[k].cod_mesaj);
    }
}

/*functia de afisare pentru cerinta 6*/
void afisare_c6(int nrC, int nrP, postas postasi[], pachet pachete[])
{
    int i;
    for (i = 0; i < nrC; i++)
    {
        printf("%d %d\n", postasi[i].idC, postasi[i].nP);

        /*daca postasul livreaza pachete*/
        if (postasi[i].nP > 0)
            alterare_cod(nrP, postasi[i], pachete);
    }
}

/*functia de calculare a scorului unui postas*/
float calculare_scor(int nrP, postas P, pachet pachete[])
{
    float scor = 0;
    int cnt = 0; /*numarul de pachete pe care P le poate altera*/

    int j;
    /*parcurg pachetele pe care P le poate distribui*/
    for (j = 0; j < P.nP; j++)
    {
        int k = P.p_distrib[j];         /*retin indicele pachetului*/
        int id = P.idC, ok = 0;         /*retin indicele cartierului*/
        int cod = pachete[k].cod_mesaj; /*retin codul mesajului*/
        while (cod > 0 && ok == 0)
        {
            /*daca id ul e de o cifra si se gaseste in cod atunci ok ia val 1*/
            if (id < 10 && cod % 10 == id)
                ok = 1;
            else if (id > 9 && (cod % 10 == id / 10 || cod % 10 == id % 10))
                ok = 1; /*daca id-ul e de doua cifra si una dintre ele se
                          gaseste in cod atunci ok ia valoarea 1*/
            cod /= 10;
        }

        cod = pachete[k].cod_mesaj;
        if (ok == 1) /*inseamna ca postasul P poate modifica codul pachetului k*/
            cnt++;   /*cresc numarul de pachete alterate*/
    }

    /*scorul este numarul de pachete distribuite corect impartit la numarul de
    pachete pe care le poate distribui*/
    scor = (float)(P.nP - cnt) / P.nP;
    return scor; /*returnez scorul*/
}

/*functia de afisare pentru cerinta 7*/
void afisare_c7(int nrC, int nrP, postas postasi[], pachet pachete[])
{
    int i;
    for (i = 0; i < nrC; i++)
    {
        float scor = 0;
        /*daca postasul livreaza pachete ii calculez scorul*/
        if (postasi[i].nP > 0)
            scor = calculare_scor(nrP, postasi[i], pachete);

        /*afisez id-ul postasului si scorul sau (cu 3 zecimale)*/
        printf("%d %.3f\n", postasi[i].idC, scor);
    }
}

int main()
{
    int cerinta;
    int nrC, nrP, i;

    cartier cartiere[32];
    pachet pachete[1600]; /*32 (cartiere) * 50 (pachete per cartier) == 1600*/
    postas postasi[32];

    scanf("%d", &cerinta);

    /*pentru fiecare cerinta citesc datele problemei*/
    if (cerinta >= 1)
        citire(&nrC, &nrP, cartiere, pachete);

    if (cerinta == 1)
        afisare_c1(nrC, nrP, cartiere, pachete);
    if (cerinta >= 2)
    {
        /*pentru cerintele 2->7 extrag datele din adresa pachetelor*/
        for (i = 0; i < nrP; i++)
            pachete[i] = extragere(pachete[i]);

        if (cerinta == 2)
            afisare_c2(nrP, pachete);
    }
    if (cerinta == 3 || cerinta == 4)
    {
        /*distribui pachetele postasilor*/
        distributie(nrC, nrP, pachete, postasi);

        /*daca este cerinta 4 sortez pachetele postasilor*/
        if (cerinta == 4)
            for (i = 0; i < nrC; i++)
                sortare(postasi[i].nP, postasi[i].p_distrib, pachete);

        /*afisez corespunzator cerintei*/
        afisare_c3_c4(nrC, postasi);
    }
    if (cerinta >= 5)
    {
        /*pentru cerintele 5->7 distribui pachetele, sortez pachetele fiecarui
        postas si apoi codific mesajele fiecarui pachet*/

        distributie(nrC, nrP, pachete, postasi);

        for (i = 0; i < nrC; i++)
            sortare(postasi[i].nP, postasi[i].p_distrib, pachete);

        for (i = 0; i < nrP; i++)
        {
            /*inversez ordinea cuvintelor si elimin semnele de punctuatie
            pentru mesajul pachetului*/
            strcpy(pachete[i].mesaj, inversare_text(pachete[i].mesaj));

            /*realoc dinamic memoria pentru mesajul pachetului, deoarece dupa
            prelucrare, acesta va ocupa mai putin spatiu in memorie*/
            int l = strlen(pachete[i].mesaj);
            pachete[i].mesaj = realloc(pachete[i].mesaj, (l + 1) * sizeof(char));

            /*codific mesajul*/
            pachete[i].cod_mesaj = codificare_mesaj(pachete[i]);
        }

        if (cerinta == 5)
            afisare_c5(nrC, nrP, postasi, pachete);
        if (cerinta == 6)
            afisare_c6(nrC, nrP, postasi, pachete);
        if (cerinta == 7)
            afisare_c7(nrC, nrP, postasi, pachete);
    }

    /*eliberez memoria*/
    for (i = 0; i < nrC; i++)
        free(cartiere[i].nume);

    for (i = 0; i < nrP; i++)
        free(pachete[i].mesaj);

    return 0;
}
