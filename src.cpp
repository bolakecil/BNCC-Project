#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

char map[100][100] = {};
char basket[10] = "\\___/";
int basketWeight = 200; //max basket lv1 capacity
int basketPos = 15;
char name [30] = {"Lorem ipsum"};
int score = 0;
int weight = 0;

struct fruit{
    int weight;
    int point;
} apple, mango, orange;

void printExit(){
    FILE *exit = fopen("Exit.txt", "r");
    char buffer[10000];
    while (fscanf(exit,"%[^\n]\n", buffer) != EOF) printf ("%s\n", buffer);
    printf ("\n");
    fclose(exit);
    getchar();
}

void printHeader(){
    FILE *header = fopen("Title.txt", "r");
    char buffer[1000];
    while (fscanf(header,"%[^\n]\n", buffer) != EOF) printf ("%s\n", buffer);
    printf ("\n");
    fclose(header);
}

void printMenu(char arr[]){
    system("cls");
    printHeader();
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

void setFruit(){
    apple.point = 50;
    apple.weight = 20;

    orange.point = 60;
    orange.weight = 15;

    mango.point =  55;
    mango.weight = 30; 
}

void setGame(int basketLevel){
    if (basketLevel == 2){
        strcpy(basket, "\\____/");
        basketWeight = 270;
    }
    else if (basketLevel == 3){
        strcpy(basket, "\\_____/");
        basketWeight = 350;
    }
    setFruit();
    for (int i = 0; i < 15; i++){
        for (int j = 0; j < 35; j++) map[i][j] = ' ';
    }
    basketPos = 15; //starting position for basket
    for (int i = 0; i < strlen(basket); i++) map[14][basketPos+i] = basket[i];
}

void printMap(int timeElapsed){
    system("cls");
    printf ("\n");
    for (int i = 0; i < 15; i++){
        for (int j = 0; j < 35; j++){
            printf ("%c", map[i][j]);
        }
        if (i == 4) printf (" %s", name);
        else if (i == 5) printf (" Score: %d", score);
        else if (i == 6) printf (" Weight acquired: %d", weight);
        else if (i == 7) printf (" Time elapsed: %d", timeElapsed);
        printf ("\n");
    }
}

void delay(){
    for (int i = 0; i < 100000; i++);
}

void generateFruit(){
    int spawnPos;
    do{
        spawnPos = rand()%35;
    } while (spawnPos < 0 || spawnPos >= 35);

    int chosenFruit = rand()%3;
    if (chosenFruit == 1) map[0][spawnPos] = '@'; //apple
    else if (chosenFruit == 2) map[0][spawnPos] = 'o'; //orange
    else if (chosenFruit == 3) map[0][spawnPos] = ','; //mango
    //nanti generate print, kalo misalnya user collect, brrti add in attribute di struct ke total user
}

void moveFruit(){
    for (int i = 1; i < 14; i++){
        for (int j = 0; j < 35; j++){
            char temp = map[i][j];
            map[i][j] = map[i-1][j];
            map[i-1][j] = temp;
        }
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
            if (basketPos < 34-strlen(basket)) basketPos++;
            break;
    }
    for (int i = 0; i < strlen(basket); i++) map[14][basketPos+i] = basket[i];
}

void gameplay(int basketLevel){
	setGame(basketLevel);
    int timeUp = 0;
    clock_t start = clock();
    while(weight <= basketWeight && (clock()-start)/CLOCKS_PER_SEC < 45){ //current time elapsed from start
        printMap((clock()-start)/CLOCKS_PER_SEC);
        delay();
        if (kbhit()) moveBasket();
        moveFruit();
    }
}

// void storeScore(){ //inget pass basketLevel
//     FILE *database = fopen("Database.txt", "r");
//     FILE *temp = fopen("Temp.txt", "w");

//     if (database == NULL || temp == NULL){
//         printf("Error Opening file(s).\n");
//         return;
//     }

//     bool isPlayerFound = false, isNewHighScore = false;

//     while(!feof(database)){
//         char curPlayer[100];
//         int curScore;
//         int curBasketLvl;
//         fscanf(database, "%[^#]#%d#%d\n", curPlayer, &curScore, &curBasketLvl);

//         if(strcmp(curPlayer, name) == 0){ // if found same player
//             if(score > curScore){ // if reach new high score
//                 fprintf(temp, "%s#%d#%d\n", curPlayer, score, curBasketLvl);
//                 isNewHighScore = true;
//             }
//             else{ // else not high score
//                 fprintf(temp, "%s#%d#%d\n", curPlayer, curScore, curBasketLvl);
//             }
//             isPlayerFound = true;
//         }
//         else{ // else copy data like normal
//             fprintf(temp, "%s#%d#%d\n", curPlayer, curScore, curBasketLvl);
//         }
//     }

//     if(!isPlayerFound){ // if no player found, add new data to the list
//         fprintf(temp, "%s#%d#%d\n", name, score, basketLevel);
//     }

//     fclose(temp);
//     fclose(database);

//     remove("Database.txt");
//     rename("Temp.txt", "Database.txt");

//     if(!isPlayerFound || isNewHighScore){
//         system("cls");
//         printf("> Congratulation, you have reached a new high score of %d!\n", score);
//         puts("> Your new high score have been stored in the database, you can check it in the high score menu.");
//         getchar();
//     }
// }

int newGame(){
    system("cls");
    FILE *database = fopen("Database.txt", "r");
    printf("Insert player name to create profile: ");
    scanf("%[^\n]", name); getchar();
    printf("\n");
    strupr(name);

    bool isDuplicate = false;

    while(!feof(database)){
        char curPlayer[100];
        int curScore, curBasketLvl;
        fscanf(database, "%[^#]#%d#%d\n", curPlayer, &curScore, &curBasketLvl);
        if(strcmp(curPlayer, name) == 0){
            puts("> Player profile already existed in database, returning to Main Menu..");
            getchar();
            isDuplicate = true;
            break;
        }
    }
    fclose(database);

    if(!isDuplicate){
        printf("> Profile created succesfully for %s, Ready To Play? [Press Any Key to Continue]\n", name);
        getchar();
        return 1;
    }
    else return 0;
}

int loadGame(){
    system("cls");
    FILE *database = fopen("Database.txt", "r");

    char target[100];
    printf("Insert player name to load profile: ");
    scanf("%[^\n]", target); getchar();
    printf("\n");
    strupr(target);

    bool isPlayerFound = false;
    int curBasketLvl = 0;

    while(!feof(database)){
        char curPlayer[100];
        int curScore;
        fscanf(database, "%[^#]#%d#%d\n", curPlayer, &curScore, &curBasketLvl);
        if(strcmp(curPlayer, target) == 0){
            puts("Profile Loaded:");
            printf("Player Name: %s\n", curPlayer);
            printf("Current Highscore: %d\n", curScore);
            printf("Current Basket Level: %d\n\n", curBasketLvl);
            printf("> Welcome back %s, Ready To Play? [Press Any Key to Continue]\n", curPlayer);
            isPlayerFound = true;
            strcpy(name, curPlayer);
            break;
        }
    }

    if(!isPlayerFound){
        printf("> Player profile not found, returning to Main Menu..\n");
        curBasketLvl = 0;
    }

    fclose(database);
    getchar();
    return curBasketLvl;
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

    printHeader();
    printf ("H I G H S C O R E\n");
    printf ("=================\n");
    for (int j = 0; j < i; j++) printf ("%s %d\n", user[j].name, user[j].highscore);
    fclose(database);
    getchar();
}

void displayGuide(){
    system("cls");
    printHeader();
    printf("Welcome to Catch The Fruit!\n");
    printf("In the Lands of Harvest, you are asked to collect the falling fruits.\n");
    printf("You are also given a basket to store the collected fruits.\n\n");

    printf("BASICS\n");
    printf("=====\n\n");
    printf("General:\n");
    printf("A - Move basket to the left\n");
    printf("D - Move basket to the right\n");
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
    srand(time(NULL));
    int choice, basketLevel;
    do{
        switch(choice = menu()){
            case 10: //start new game
                basketLevel = newGame();
                if (basketLevel == 1) gameplay(basketLevel);
                break;
            case 11: //load game
                basketLevel = loadGame();
                if (basketLevel != 0) gameplay(basketLevel);
                // gameplay(1);
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
    printExit();
    return 0;
}
