#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

char map[100][100] = {};
char basket[10] = "\\___/";
int basketPos = 15;
char name [30] = {"Lorem ipsum"};
int score = 0;

void printMenu(char arr[]){
    system("cls");
    printf("1. %-20s %c\n", "New Game", arr[0]);
    printf("2. %-20s %c\n", "Load Game", arr[1]);
    printf("3. %-20s %c\n", "View Highscore", arr[2]);
    printf("4. %-20s %c\n", "How To Play", arr[3]);
    printf("5. %-20s %c\n", "Quit", arr[4]);
}

int moveMenu(char arr[], int pos){
    switch(char move = getch()){
        case 'W':
        case 'w':
            if (pos > 0){
                arr[pos] = ' ';
                arr[--pos] = '<';
            }
            break;
        
        case 'S':
        case 's':
            if (pos < 4){
                arr[pos] = ' ';
                arr[++pos] = '<';
            }
            break;
        
        case '\r':
            pos += 10;
    }
    return pos;
}

void setGame(int basketLevel){
    if (basketLevel == 2) strcpy(basket, "\\____/");
    else if (basketLevel == 3) strcpy(basket, "\\_____/");
    for (int i = 0; i < 15; i++){
        for (int j = 0; j < 35; j++) map[i][j] = ' ';
    }
    for (int i = 0; i < strlen(basket); i++) map[14][15+i] = basket[i];
    basketPos = 15;
}

void printMap(){
    system("cls");
    printf ("\n");
    for (int i = 0; i < 15; i++){
        for (int j = 0; j < 35; j++){
            printf ("%c", map[i][j]);
        }
        if (i == 4) printf (" |%s|", name);
        else if (i == 5) printf (" |%d|", score);
        printf ("\n");
    }
}

int moveBasket(){
    for (int i = basketPos; i < strlen(basket)+basketPos; i++) map[14][i] = ' ';
    switch(char move = getch()){
        case 'A':
        case 'a':
            if (basketPos > 0) basketPos--;
            break;
        
        case 'D':
        case 'd':
            if (basketPos < 34) basketPos++;
            break;
    }
    for (int i = 0; i < strlen(basket); i++) map[14][basketPos+i] = basket[i];
}

void gameplay(int basketLevel){
	setGame(basketLevel);
    int basketPos = 15, time = 0;
    while(time < 3){
        printMap();
        moveBasket();
        time++;
    }
}

void displayHighscore(){
    FILE *database = fopen("Database.txt", "r");
    if (database == NULL) printf("Database doesn't exist!\n");

    int size = 0;
    char buffer[100];
    while (fscanf(database, "%[^\n]\n", buffer) != EOF) size++;
	rewind(database);

    struct info{
        char name[50];
        int highscore;
        int basketLevel;
    } user[size+5];

    int i = 0;
    while (fscanf(database, "%[^#]#%d#%d\n", user[i].name, &user[i].highscore, &user[i].basketLevel) != EOF) i++;
    system("cls");
    
    //selection sort using highscore
   int temp;
   for (int i = 0; i < size-1; i++){
       struct info min = user[i];
       for (int j = i; j < size; j++){
           if (min.highscore <= user[j].highscore){
               min = user[j];
               temp = j;
           }
       }
       user[temp] = user[i];
       user[i] = min;
   }

    printf ("HIGHSCORE\n");
    printf ("=========\n");
    for (int j = 0; j < i; j++) printf ("%s %d\n", user[j].name, user[j].highscore);
    fclose(database);
    getchar();
}

void displayGuide(){
    system("cls");
    printf("Welcome to Catch The Fruit!\n");
    printf("In the Lands of Harvest, you are asked to collect the falling fruits.\n");
    printf("You are also given a basket to store the collected fruits.\n\n");

    printf("BASICS\n");
    printf("=====\n\n");
    printf("General:\n");
    printf("W - Move basket to the left\n");
    printf("S - Move basket to the right\n");
    printf("* Basket level increases by every 170 points milestone, capped at level 3\n");
    printf("* Game lasts for 45 seconds each round before the score is recorded!\n");
    printf("\nGood luck!\n");

    getchar();
}

int menu(){
    char cursorMove[5] = {};
    cursorMove[0] = '<';
    int curIdx = 0;
    do{
        printMenu(cursorMove);
        curIdx = moveMenu(cursorMove, curIdx);
    } while (curIdx < 10);
    return curIdx;
}

int main(){
    int choice;
    do{
        switch(choice = menu()){
            case 10: //start new game
                gameplay(1);
                break;
            case 11: //load game

                break;
            case 12: //game highscore
                displayHighscore();
                break;
            case 13: //game guide
                displayGuide();
                break;
        }
   } while (choice != 14); //quit game
    system("cls");
    return 0;
}
