#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> //to include true in bool statements
#include <ctype.h> // to include toupper()
#include <string.h>
#include <math.h>

double add(double x, double y, int isPrint){
    double z;
    z = x + y;
    if(isPrint == 1){
        printf("%.f + %.f = %.f.\n", x, y, z);
    }
    return z;
}
double minus(double x, double y, int isPrint){
    double z;
    z = x - y;
    if(isPrint == 1){
        printf("%.f - %.f = %.f.\n", x, y, z);
    }
    return z;
}
double multiply(double x, double y, int isPrint){
    double z;
    z = x * y;
    if(isPrint == 1){
        printf("%.f * %.f = %.f.\n", x, y, z);
    }
    return z;
}
double divide(double x, double y, int isPrint){
    double z;
    z = x / y;

    if(isPrint == 1){
        printf("%.f / %.f = %.f.\n", x, y, (int)z);
    }
    return z;
}
bool check(char x[]){
    bool isGood;
    if(strlen(x)==3){
        for(int i = 0; i<3; i++){
            if(x[i] == '+' || x[i] == '-' || x[i] == '*' || x[i] == '/'){
                isGood = true;
            }
            else{
                isGood = false;
                printf("Error! Invalid operator entered. Please try again.\n");
                break;
            }
        }
    }
    else{
        isGood = false;
        printf("Error! The number of operators is incorrect. Please try again.\n");
    }
    return isGood;
}

char operators[] = {'+', '-', '*', '/'};
char combo_array[64][4]; // 64 possible combinations of 3 operators
int count = 0;

void generate_combinations(int index, char current_str[]) {
    if (index == 3) {
        strcpy(combo_array[count++], current_str);
        return;
    }
    for (int i = 0; i < 4; i++) {
        current_str[index] = operators[i];
        generate_combinations(index + 1, current_str);
    }
}
int solutions[3188][4];
char debug_solutions[3188][3];
int ctr=0;

void solve(){
    double answer;
    int new_array[4];

    for(int i = 1; i<10; i++){
        new_array[0] = i;
        for(int k = 1; k<10; k++){
            new_array[1] = k;
            for(int j = 1; j<10; j++){
                new_array[2] = j;
                for(int z = 1; z<10; z++){
                    new_array[3]=z;

                    for(int k = 0; k<64; k++){
                        answer = new_array[0];
                        for(int j = 0; j <3; j++){
                            if(combo_array[k][j] == '+'){
                                answer = add(answer, (double)new_array[j+1],0);
                            }
                            else{
                                if(combo_array[k][j] == '-'){
                                    answer = minus(answer, (double)new_array[j+1],0);
                                }
                                else{
                                    if(combo_array[k][j] == '*'){
                                        answer = multiply(answer, (double)new_array[j+1],0);
                                    }
                                    else{
                                        answer = divide(answer, (double)new_array[j+1],0);
                                    }
                                }
                            }
                        }
                        if((answer - 24.0) < 0.001 && ((answer - 24.0) >= 0)){
                            for(int l = 0; l<4; l++){
                                solutions[ctr][l] = new_array[l];
                            }
                            for(int j = 0; j <3; j++){
                                if(combo_array[k][j] == '+'){
                                    debug_solutions[ctr][j] = '+';
                                }
                                else{
                                    if(combo_array[k][j] == '-'){
                                        debug_solutions[ctr][j] = '-';
                                    }
                                    else{
                                        if(combo_array[k][j] == '*'){
                                            debug_solutions[ctr][j] = '*';
                                        }
                                        else{
                                            debug_solutions[ctr][j] = '/';
                                        }
                                    }
                                }
                            }
                            ctr++;
                        }
                    }
                }
            }
        }
    }
}

int main(int argc, char *argv[])
{
    char current_str[4];
    generate_combinations(0, current_str);
    solve();
    bool easymode = true;
    bool debugger = false;
    int easyArray[10][4] = {
            {3,9,4,1},{8,5,8,1}, {6,1,5,1}, {2,8,7,8}, {5,2,9,2}, {2,6,8,4}, {5,5,4,3},{6,6,2,6}, {8,4,2,6}, {6,2,8,1}
    };
    char play_again = 'y';
    //loop through and find flags
    int i = 1;
    while((argc) > 2)
    {
        if(argv[i][0]=='-'){
            switch(argv[i][1])
            {
                case 'e':
                    if(atoi(argv[i+1]) == 1)
                    {
                        easymode = true;
                    }
                    if(atoi(argv[i+1]) == 0)
                    {
                        easymode = false;
                    }
                    argc -=2;
                    break;
                case 'd':
                    if(atoi(argv[i+1]) == 1)
                    {
                        debugger = true;
                    }
                    if(atoi(argv[i+1]) == 0)
                    {
                        debugger = false;
                    }
                    argc -=2;
                    break;
            }
        }
        i++;
    }
    //debugger code first
    if(debugger){
        int c = 1;
        for(int t = 0; t<3188; t++){
            printf("%d. %d%c%d%c%d%c%d\n", c, solutions[t][0], debug_solutions[t][0], solutions[t][1],debug_solutions[t][1],solutions[t][2],debug_solutions[t][2], solutions[t][3]);
            c++;
        }
    }
    //start of game code
    printf("Welcome to the game of TwentyFour.\n");
    printf("Use each of the four numbers shown below exactly once,\ncombining them somehow with the basic mathematical operators (+,-,*,/)\nto yield the value twenty-four.\n");
    int randomint = 0;
    char symbols[3];
    double answer = 0;
    bool isGood;
    if(easymode){
        while(play_again != 'N'){
            randomint = rand()%10;
            printf("\nThe numbers to use are: %d, %d, %d, %d.\n",easyArray[randomint][0],easyArray[randomint][1],easyArray[randomint][2],easyArray[randomint][3]);
            printf("Enter the three operators to be used, in order (+,-,*, or /): ");
            scanf("%s",symbols);
            answer = easyArray[randomint][0];
            isGood = check(symbols);
            if(!isGood){
                continue;
            }
            for(int j = 0; j <3; j++){
                if(symbols[j] == '+'){
                    answer = add(answer, (double)easyArray[randomint][j+1],1);
                }
                else{
                    if(symbols[j] == '-'){
                        answer = minus(answer, (double)easyArray[randomint][j+1],1);
                    }
                    else{
                        if(symbols[j] == '*'){
                            answer = multiply(answer, (double)easyArray[randomint][j+1],1);
                        }
                        else{
                            answer = divide(answer, (double)easyArray[randomint][j+1],1);
                        }
                    }
                }
            }
            if(answer == (double)24){
                printf("Well done! You are a math genius.\n");
            }
            else{
                printf("Sorry. Your solution did not evaluate to 24.\n");
            }
            printf("\nWould you like to play again? Enter N for no and any other character for yes. ");
            fgetc(stdin);
            scanf("%c", &play_again);

        }
        printf("\nThanks for playing!\n");
    }
    else{
        int new_array[4];
        int random;
        while(play_again != 'N'){
            random = rand()%3189;
            //printf("Random is: %d", random);
            for(int start = 0; start<4; start++){
                new_array[start] = solutions[random][start];
            }
            printf("The numbers to use are: %d, %d, %d, %d.\n", new_array[0], new_array[1], new_array[2], new_array[3]);
            printf("Enter the three operators to be used, in order (+,-,*, or /): ");
            scanf("%s",symbols);
            answer = new_array[0];
            isGood = check(symbols);
            if(!isGood){
                continue;
            }
            for(int j = 0; j <3; j++){
                if(symbols[j] == '+'){
                    answer = add(answer, (double)new_array[j+1],1);
                }
                else{
                    if(symbols[j] == '-'){
                        answer = minus(answer, (double)new_array[j+1],1);
                    }
                    else{
                        if(symbols[j] == '*'){
                            answer = multiply(answer, (double)new_array[j+1],1);
                        }
                        else{
                            answer = divide(answer, (double)new_array[j+1],1);
                        }
                    }
                }
            }
            if(answer == (double)24){
                printf("Well done! You are a math genius.\n");
            }
            else{
                printf("Sorry. Your solution did not evaluate to 24.\n");
            }
            printf("Would you like to play again? Enter N for no and any other character for yes. ");
            fgetc(stdin);
            scanf("%c", &play_again);

        }
        printf("\nThanks for playing!\n");
    }
    return 0;
}