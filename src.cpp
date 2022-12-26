#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

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

void displayHighscore(){
    FILE *database = fopen("Database.txt", "r");
    if (database == NULL) printf("Database doesn't exist!\n");

    int size = 0;
    char buffer[100];
    while (fscanf(database, "%[^\n]\n", buffer) != EOF) size++;
	rewind(database);
    struct player{
        char name[50];
        int highscore;
        int basketLevel;
    } user[size+5];

    int i = 0;
    while (fscanf(database, "%[^#]#%d#%d\n", user[i].name, &user[i].highscore, &user[i].basketLevel) != EOF) i++;
    system("cls");
    for (int j = 0; j < i; j++) printf ("%s %d %d\n", user[j].name, user[j].highscore, user[j].basketLevel);
    printf ("ah");
    getchar();
}

void displayGuide(){
    system("cls");
    printf("Welcome to Catch The Fruit!\n");
    printf("In the Lands of Harvest, you are asked to collect the falling fruits.\n");
    printf("You are also given a basket to store the collected fruits.\n");

    printf("BASICS\n");
    printf("=====\n\n");
    printf("General:\n");
    printf("W - Move basket to the left\n");
    printf("S - Move basket to the right\n");
    printf("* Basket level increases by every 150 points milestone, capped at level 3\n");
    printf("* Game lasts for 45 seconds each round before the score is recorded!\n");

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
            
                break;
            case 11: //load game

                break;
            case 12: //game highscore

                break;
            case 13: //game guide
                displayGuide();
                break;
        }
   } while (choice != 14); //quit game
    
    return 0;
}
