#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void printMenu(char arr[]){
    system("cls");
    printf ("1. %-20s %c\n", "New Game", arr[0]);
    printf ("2. %-20s %c\n", "Load Game", arr[1]);
    printf ("3. %-20s %c\n", "How to Play", arr[2]);
    printf ("4. %-20s %c\n", "View Highscore", arr[3]);
    printf ("5. %-20s %c\n", "Quit", arr[4]);
}

// int moveMenu(char arr[], int pos){
//    // char move;
//    switch(int input = getch()){
//        case 224: //control key for unicode x0
//            switch (int moveTo = getch()){
//                case 72:
//                    if (pos > 0){
//                        arr[pos] = ' ';
//                        arr[--pos] = '<'; 
//                    }
//                    break;

//                case 80:
//                    if (pos < 4){
//                        arr[pos] = ' ';
//                        arr[++pos] = '<';
//                    }
//                    break;
                   
//            }
//        case '\r': pos+=10;
//    }
//    return pos;
// }

int moveMenu(char arr[], int pos){
    switch(char move = getch()){
        case 'w':
            if (pos > 0){
                arr[pos] = ' ';
                arr[--pos] = '<';
            }
            break;
        
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

int menu(){
    char cursorMove[5] = {};
    // for (int i = 0; i < 5; i++) cursorMove[i] = ' ';
    cursorMove[0] = '<';
    int curIdx = 0;
    do{
        printMenu(cursorMove);
        curIdx = moveMenu(cursorMove, curIdx);
    } while (curIdx < 10);
    return curIdx;
}

int main(){
    int choice = 0;
   do{
        choice = menu();
   } while (choice != 14);
    
    return 0;
}
