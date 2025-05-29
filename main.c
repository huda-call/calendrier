#include <stdio.h>
#include <conio.h>
#include <windows.h>

// Prototypes des fonctions
void display(int, int, int, int[]);
void calendar(int, int);
void gotoxy(int x, int y);
void SetColor(int Forgc);

// Définition des fonctions
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void SetColor(int Forgc) {
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
        wColor = (csbi.wAttributes & 0xF0) + (Forgc & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}
void delay(int milliseconds) {
    Sleep(milliseconds); // Fonction Sleep pour introduire une pause en millisecondes
}

int main() {
   int nmonth, nyr, ch;
entreryear:
    system("cls");
while (1) {
        system("color F");
    printf("Enter year:");
    scanf("%d", &nyr);
    printf("Enter month:");
    scanf("%d", &nmonth);
    if (nyr < 1945) {
        SetColor(4);
        printf("Please enter a year above 1945.");
      getch();
       system("cls");
    }
    else if (nmonth > 12 || nmonth < 1) {
            SetColor(4);
        printf("The month is invalid\n");
       getch();
       system("cls");
    } else {
        calendar(nyr, nmonth);
        break;
    }
}
    while (1) {
        ch = getch();
        switch (ch) {

       case 80:
                if (nmonth == 12) {
                    nmonth = 1;
                    nyr++;
                } else {
                    nmonth++;
                }
                calendar(nyr, nmonth);
                break;
            case 77:
                nyr++;
                calendar(nyr, nmonth);
                break;
            case 72:
                if (nmonth == 1) {
                    nyr--;
                    nmonth = 12;
                } else {
                    nmonth--;
                }
                calendar(nyr, nmonth);
                break;
            case 75:
                if (nyr == 1945) {
                    gotoxy(15, 2);printf("Year below 1945 not available");
                } else {
                    nyr--;
                    calendar(nyr, nmonth);
                }
                break;
            case 'q':
                system("cls");
                gotoxy(50, 14);printf("Exiting program.");
                exit(0);
                case 'p': // Touche 'p' pour revenir à l'écran d'entrée de l'année et du mois
    system("cls");
    goto entreryear;
    break;

        }
    }

    getch();
    return 0;
}

void display(int nyr, int nmonth, int tdays, int days[]) {
    char *month[] = {"Janvier", "Fevrier", "Mars", "Avril", "Mai", "Juine", "Juiellet", "Aout", "September", "October", "November", "December"};
    char *week[] = {"LUN", "MAR", "MER", "JEU", "VEN", "SAM", "DIM"};

    int i, j, pos;
    SetColor(11);
    gotoxy(56, 6);printf("%s %d", month[nmonth - 1], nyr);
    for (i = 0, pos = 30; i < 7; i++, pos += 10) {
        if (i == 6)
            SetColor(4);
        else
            SetColor(15);
        gotoxy(pos, 8);
        printf("%s", week[i]);
    }

    tdays++;
    if (tdays == 0 || tdays == 7)
        pos = 91;
    if (tdays == 1)
        pos = 31;
    if (tdays == 2)
        pos = 41;
    if (tdays == 3)
        pos = 51;
    if (tdays == 4)
        pos = 61;
    if (tdays == 5)
        pos = 71;
    if (tdays == 6)
        pos = 81;
    for (i = 0, j = 10, pos; i < days[nmonth - 1]; i++, pos += 10) {
        if (pos == 91)
            SetColor(4);
        else
            SetColor(7);
        gotoxy(pos, j);
        printf("%d", i + 1);
        if (pos == 91) {
            pos = 21;
            j++;
        }
    }
    SetColor(5);
    for (i = 22; i < 102; i++) {
        gotoxy(i, 4);
        printf("%c", 196);
        gotoxy(i, 17);
        printf("%c", 196);
    }
    gotoxy(22, 4);
    printf("%c", 218);
    gotoxy(102, 4);
    printf("%c", 191);
    gotoxy(21, 17);
    printf("%c", 192);
    gotoxy(102, 17);
    printf("%c", 217);

    for (i = 5; i < 17; i++) {
        gotoxy(21, i);
        printf("%c", 179);
        gotoxy(102, i);
        printf("%c", 179);
    }
    SetColor(11);// party flesh
    gotoxy(61,5);printf("/\\");
    gotoxy(61,16);printf("V");
    gotoxy(24, 11);printf("<");
    gotoxy(98, 11);printf(">");
}

void calendar(int nyr, int nmonth) {
    int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int tdays = 0, k, myear;
    system("cls");
    myear = nyr - 1;
    if (myear >= 1945) {
        for (k = 1945; k <= myear; k++) {
            if (k % 4 == 0)
                tdays = tdays + 366;
            else
                tdays = tdays + 365;
        }
    }
    if (nyr % 4 == 0)
        days[1] = 29;
    else
        days[1] = 28;

    for (k = 0; k < (nmonth - 1); k++) {
        tdays = tdays + days[k];
    }
    tdays = tdays % 7;
    display(nyr, nmonth, tdays, days);
    if (nmonth == 1) {
        gotoxy(20, 20);
        printf("> 1 janvier : nouvelle annee");
        gotoxy(20, 22);
        printf("> 11 janvier : anniversaire de l'independance");
    } else if (nmonth == 5) {
        gotoxy(20, 20);
        printf("> 1 mai : fete du travail");
    } else if (nmonth == 7) {
        gotoxy(20, 20);
        printf("> 30 juillet : fete du trone");
    } else if (nmonth == 8) {
        gotoxy(20, 20);
        printf("> 14 aout : commemoration de l'allegeance de Ouaed Ed-Dahab ");
        gotoxy(20, 22);
        printf("> 20 aout : anniversaire de la revolution du roi et du peuple");
        gotoxy(20, 24);
        printf("> 21 aout : anniversaire du roi Mohammed VI");
    } else if (nmonth == 11) {
        gotoxy(20, 20);
        printf("> 18 novembre : fete de l'indépendance");
        gotoxy(20, 22);
        printf("> 6 novembre : la marche verte");

    }
}
