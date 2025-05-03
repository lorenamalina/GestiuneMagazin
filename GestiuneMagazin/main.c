#include <stdio.h>
#include <conio.h>
#include <string.h>

struct produs {
    char nume[50];
    int pret;
    int cantitate;
};
#define COLOR_ORANGE "\033[0;33m"
#define COLOR_BLUE "\033[0;34m"
#define COLOR_YELLOW "\033[0;33m"
#define COLOR_RESET "\033[0m"
int main() {
    int optiune = 0;
    int pret_total = 0;
    char choice;
    char vector_comenzi[200][50];
    struct produs produse[100];
    int numar_zile = 0;

    FILE* file_zile = fopen("C:\\Users\\LORENA\\OneDrive\\Desktop\\zile.txt", "r");
    if (file_zile != NULL) {
        fscanf(file_zile, "%d", &numar_zile);
        fclose(file_zile);
    }

    FILE* file_cantitati = fopen("C:\\Users\\LORENA\\OneDrive\\Desktop\\cantitati.txt", "r");
    for (int i = 0; i < 100; i++) {
        fscanf(file_cantitati, "%d", &produse[i].cantitate);
    }
    fclose(file_cantitati);

    while (1) {
        system("cls");

        printf("Lista produse");
        if (optiune == 0)
            printf(" <<");
        printf("\n");

        printf("Istoric vanzari");
        if (optiune == 1)
            printf(" <<");
        printf("\n");

        printf("Cantitati");
        if (optiune == 2)
            printf(" <<");
        printf("\n");

        printf("Zile");
        if (optiune == 3)
            printf(" <<");
        printf("\n");

        printf("Incheiere zi");
        if (optiune == 4)
            printf(" <<");
        printf("\n");

        printf("Iesire");
        if (optiune == 5)
            printf(" <<");
        printf("\n");

        choice = getch();

        if (choice == 72 && optiune > 0)
            optiune--;
        else if (choice == 80 && optiune < 5)
            optiune++;
        else if (choice == 13) {
            system("cls");
            switch (optiune) {
             case 0:
                printf("LISTA PRODUSE:\n");
                int nr_produse;
                FILE* file_produse = fopen("C:\\Users\\LORENA\\OneDrive\\Desktop\\P2\\GestiuneMagazin\\produse.txt", "r");
                FILE* file_comenzi = fopen("C:\\Users\\LORENA\\OneDrive\\Desktop\\P2\\GestiuneMagazin\\comenzi.txt", "r+");
                int nr_comenzi;

                fscanf(file_comenzi, "%d", &nr_comenzi);

                for (int i = 0; i < nr_comenzi; i++) {
                    fscanf(file_comenzi, "%s", vector_comenzi[i]);
                }

                fscanf(file_produse, "%d", &nr_produse);
                fgetc(file_produse);
                for (int i = 0; i < nr_produse; i++) {
                    fscanf(file_produse, "%s %d", produse[i].nume, &produse[i].pret);
                    printf(COLOR_ORANGE "%d." COLOR_RESET " Nume %s - Pret " COLOR_BLUE "%d\n" COLOR_RESET, i, produse[i].nume, produse[i].pret);
                }

                int nr_comenzi_nou = nr_comenzi;
                printf("Selecteaza produs sau apasa -1 pentru a iesi:");
                int nr_comanda;
                do {
                    scanf("%d", &nr_comanda);
                    if (nr_comanda == -1) break;
                    if (nr_comanda >= nr_produse || nr_comanda < 0)
                        printf("Nr gresit. Selecteaza din nou\n");
                } while (nr_comanda >= nr_produse || nr_comanda < 0);
                if (nr_comanda == -1) break;
                else {
                    strcpy(vector_comenzi[nr_comenzi_nou], produse[nr_comanda].nume);
                    pret_total += produse[nr_comanda].pret;
                    produse[nr_comanda].cantitate += 1;
                    nr_comenzi_nou++;
                    printf("Ati selectat: %s\nPret produs: %d\n", produse[nr_comanda].nume, produse[nr_comanda].pret);
                }
                char choice_comanda;
                do {
                    printf("Selectati alt produs sau apasati Enter pentru a finaliza:\n");
                    choice_comanda = getch();
                    if (choice_comanda != 13) {
                        do {
                            scanf("%d", &nr_comanda);
                            if (nr_comanda == -1) break;
                            if (nr_comanda >= nr_produse || nr_comanda < 0)
                                printf("Nr gresit. Selecteaza din nou\n");
                        } while (nr_comanda >= nr_produse || nr_comanda < 0);
                        if (nr_comanda < nr_produse && nr_comanda >= 0) {
                            strcpy(vector_comenzi[nr_comenzi_nou], produse[nr_comanda].nume);
                            pret_total += produse[nr_comanda].pret;
                            produse[nr_comanda].cantitate += 1;
                            nr_comenzi_nou++;
                            printf("Ati selectat: %s\nPret produs: %d\n", produse[nr_comanda].nume, produse[nr_comanda].pret);
                        }
                    }
                } while (choice_comanda != 13);

                fseek(file_comenzi, 0, SEEK_SET);
                fprintf(file_comenzi, "%d\n", nr_comenzi_nou);

                for (int i = 0; i < nr_comenzi_nou; i++) {
                    fprintf(file_comenzi, "%s\n", vector_comenzi[i]);
                }

                FILE* file_pret_total = fopen("C:\\Users\\LORENA\\OneDrive\\Desktop\\pret total.txt", "w");
                fprintf(file_pret_total, "%d", pret_total);
                fclose(file_comenzi);
                fclose(file_produse);
                fclose(file_pret_total);
                file_cantitati = fopen("C:\\Users\\LORENA\\OneDrive\\Desktop\\cantitati.txt", "w");
                for (int i = 0; i < nr_produse; i++) {
                    fprintf(file_cantitati, "%d\n", produse[i].cantitate);
                }
                fclose(file_cantitati);

                break;

            case 1:
                printf("Istoric comenzi\n");
                FILE* file_pret_total_read = fopen("C:\\Users\\LORENA\\OneDrive\\Desktop\\pret total.txt", "r");
                FILE* file_comenzi_read = fopen("C:\\Users\\LORENA\\OneDrive\\Desktop\\comenzi.txt", "r");
                int total_comenzi;
                fscanf(file_comenzi_read, "%d", &total_comenzi);
                for (int i = 0; i < total_comenzi; i++) {
                    fscanf(file_comenzi_read, "%s", vector_comenzi[i]);
                    printf("%s\n", vector_comenzi[i]);
                }
                fscanf(file_pret_total_read, "%d", &pret_total);
                printf("Pret total: " COLOR_ORANGE "%d\n" COLOR_RESET, pret_total);
                fclose(file_comenzi_read);
                fclose(file_pret_total_read);
                break;

            case 2:
                printf("Cantitati\n");
                int max_cantitate = -1;
                for (int i = 0; i < nr_produse; i++) {
                    printf(COLOR_ORANGE"%d." COLOR_RESET " Nume %s - Cantitate vanduta: " COLOR_BLUE"%d\n"COLOR_RESET, i, produse[i].nume, produse[i].cantitate);
                    if (produse[i].cantitate > max_cantitate) {
                        max_cantitate = produse[i].cantitate;
                    }
                }

                printf("Cel mai bine vandut produs: \n");
                for (int i = 0; i < nr_produse; i++) {
                    if (produse[i].cantitate == max_cantitate) {
                        printf( COLOR_YELLOW "%s " COLOR_RESET, produse[i].nume);
                        printf ("\n");
                    }
                }
                break;

            case 4:
    printf("INCHEIERE ZI:\n");
    printf("Doriti sa incheiati ziua curenta? " COLOR_ORANGE "(da/nu): " COLOR_RESET);
    char raspuns[3];
    scanf("%s", raspuns);
    if (strcmp(raspuns, "da") == 0) {
        FILE* file_zi_curenta;
        char nume_fisier[50];
        sprintf(nume_fisier, "ziua_%d.txt", numar_zile + 1);
        file_zi_curenta = fopen(nume_fisier, "a");
        if (file_zi_curenta != NULL) {
            fprintf(file_zi_curenta, "PRET TOTAL: %d\n", pret_total);
            FILE* file_comenzi = fopen("C:\\Users\\LORENA\\OneDrive\\Desktop\\comenzi.txt", "r+");
            if (file_comenzi != NULL) {
                char linie[100];
                while (fgets(linie, sizeof(linie), file_comenzi)) {
                    fprintf(file_zi_curenta, "%s", linie);
                }
                fclose(file_comenzi);
                FILE* file_comenzi_clear = fopen("C:\\Users\\LORENA\\OneDrive\\Desktop\\comenzi.txt", "w");
                fclose(file_comenzi_clear);
            }
            fclose(file_zi_curenta);
            numar_zile++;
            FILE* file_zile_update = fopen("C:\\Users\\LORENA\\OneDrive\\Desktop\\zile.txt", "w");
            if (file_zile_update != NULL) {
                fprintf(file_zile_update, "%d", numar_zile);
                fclose(file_zile_update);
            }
            FILE* file_pret_total_clear = fopen("C:\\Users\\LORENA\\OneDrive\\Desktop\\pret total.txt", "w");
            fclose(file_pret_total_clear);
            FILE* file_cantitati_clear = fopen("C:\\Users\\LORENA\\OneDrive\\Desktop\\cantitati.txt", "w");
            for (int i = 0; i < nr_produse; i++) {
                fprintf(file_cantitati_clear, "%d\n", produse[i].cantitate);
            }
            fclose(file_cantitati_clear);

            printf("Ziua a fost incheiata cu succes. Istoricul comenzilor a fost salvat in %s.\n", nume_fisier);
        }
    }
    break;

case 3:
    printf("ZILE:\n");
    for (int i = 1; i <= numar_zile; i++) {
        printf("Ziua " COLOR_ORANGE "%d\n" COLOR_RESET, i);
    }

    printf("Alege o zi pentru a vizualiza istoricul comenzilor (0 pentru a reveni):\n");
    int optiune_zi;
    if (scanf("%d", &optiune_zi) != 1) {
        printf("Eroare\n");
        break;
    }

    if (optiune_zi == 0) {
        break;
    } else if (optiune_zi > 0 && optiune_zi <= numar_zile) {
        char nume_fisier[50];
        sprintf(nume_fisier, "ziua_%d.txt", optiune_zi);
        FILE* file_istoric_zi = fopen(nume_fisier, "r");
        if (file_istoric_zi != NULL) {
            printf("ISTORIC COMENZI ZIUA %d:\n", optiune_zi);
            char comanda[50];
            while (fgets(comanda, sizeof(comanda), file_istoric_zi)) {
                printf("%s", comanda);
            }
            fclose(file_istoric_zi);
        }
    }
    break;


            case 5:
                printf("IESIRE\n");
                return 0;
            }

            printf("Apasa Enter pentru a reveni la meniul principal");
            choice = getch();
            while (choice == 13)
                break;
        }
    }
    return 0;
}
