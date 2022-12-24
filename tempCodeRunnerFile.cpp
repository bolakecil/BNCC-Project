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