#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> //to include true in bool statements
#include <ctype.h> // to include toupper()
#include <string.h>
#include <time.h>
/*Name: Shreyas Isukapalli
 * CS211 Program 1
 * 24 Game code
 * F 1pm-1:50pm
 * Description:
 * this program gives the user 4 values which they have to combine using the four basic operators to get 24
 * the numbers must be combined in the order they are shown.*/
//This function adds two doubles
void add(double *x, double y, int isPrint){
    double temp;
    temp = *x;
    *x += y;
    if(isPrint == 1){
        printf("%.f + %.f = %.f.\n", temp, y, *x);
    }
}
//this function subtracts two doubles
void minus(double *x, double y, int isPrint){
    double temp;
    temp = *x;
    *x -= y;
    if(isPrint == 1){
        printf("%.f - %.f = %.f.\n", temp, y, *x);
    }
}
//this function mulitplies two doubles
void multiply(double *x, double y, int isPrint){
    double temp;
    temp = *x;
    *x *= y;
    if(isPrint == 1){
        printf("%.f * %.f = %.f.\n", temp, y, *x);
    }
}
//this function divides two doubles with the exception of 12/8 because of test case 4 error
void divide(double *x, double y, int isPrint){
    double temp;
    temp = *x;
    *x = *x / y;
    if(isPrint == 1){
        printf("%.f / %.f = %.f.\n", temp, y, *x);
    }
}
void divide_easy(double *x, double y, int isPrint){
    double temp;
    temp = *x;
    *x = (double)((int)(*x / y));
    if(isPrint == 1){
        printf("%.f / %.f = %.f.\n", temp, y, *x);
    }
}
//this function checks if user input is valid to continue
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

int solutions[3188][4];
char debug_solutions[3188][3];
//this value will find all possible solutions for the game 24 and store it in two lists, one for the numbers, one for the operators
void solve(){
    double answer = 0.0;
    int ctr=0;
    char symbols[3];
    //These will generate all the possible combinations of numbers.
    for(double i = 1.0; i<10.0; i++){
        for(double t = 1.0; t<10.0; t++){
            for(double r = 1.0; r<10.0; r++){
                for(double z = 1.0; z<10.0; z++){
                    //this will loop through the combinations array of operators
                    for(int i1 = 0; i1 <4; i1++){
                        for(int k1 = 0; k1 <4; k1++){
                            for(int j1 = 0; j1 <4; j1++){
                                symbols[0] = operators[i1];
                                symbols[1] = operators[k1];
                                symbols[2] = operators[j1];
                                answer = i; //first value of the numbers
                                //first index
                                if(symbols[0] == '+'){
                                    add(&answer, t,0);
                                    debug_solutions[ctr][0] = '+';
                                }
                                else if(symbols[0] == '-') {
                                    minus(&answer, t, 0);
                                    debug_solutions[ctr][0] = '-';
                                }
                                else if(symbols[0] == '*'){
                                    multiply(&answer, t,0);
                                    debug_solutions[ctr][0] = '*';
                                }
                                else if (symbols[0] == '/'){
                                    divide(&answer, t,0);
                                    debug_solutions[ctr][0] = '/';
                                }
                                //second index
                                if(symbols[1] == '+'){
                                    add(&answer, r,0);
                                    debug_solutions[ctr][1] = '+';
                                }
                                else if(symbols[1] == '-') {
                                    minus(&answer, r, 0);
                                    debug_solutions[ctr][1] = '-';
                                }
                                else if(symbols[1] == '*'){
                                    multiply(&answer, r,0);
                                    debug_solutions[ctr][1] = '*';
                                }
                                else if (symbols[1] == '/'){
                                    divide(&answer, r,0);
                                    debug_solutions[ctr][1] = '/';
                                }
                                //third index
                                if(symbols[2] == '+'){
                                    add(&answer, z,0);
                                    debug_solutions[ctr][2] = '+';
                                }
                                else if(symbols[2] == '-') {
                                    minus(&answer, z, 0);
                                    debug_solutions[ctr][2] = '-';
                                }
                                else if(symbols[2] == '*'){
                                    multiply(&answer, z,0);
                                    debug_solutions[ctr][2] = '*';
                                }
                                else if (symbols[2] == '/') {
                                    divide(&answer, z, 0);
                                    debug_solutions[ctr][2] = '/';
                                }
                                //Is the answer we got 24, if so assign the values to solutions array

                                if((answer - 24.0) < 0.001 && ((answer - 24.0) >= 0.0)){
                                    solutions[ctr][0] = i;
                                    solutions[ctr][1] = t;
                                    solutions[ctr][2] = r;
                                    solutions[ctr][3] = z;
                                    //ctr only goes up if the solution is correct
                                    //therefore debug_solutions will get rewritten if the answer is wrong
                                    ctr++;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

int main(int argc, char *argv[]) {
    srand(1);//used to have same input as test cases
    char current_str[4];
    solve();//call solve function
    bool easymode = true;
    bool debugger = false;//default settings for game
    int easyArray[10][4] = {
            {3, 9, 4, 1},
            {8, 5, 8, 1},
            {6, 1, 5, 1},
            {2, 8, 7, 8},
            {5, 2, 9, 2},
            {2, 6, 8, 4},
            {5, 5, 4, 3},
            {6, 6, 2, 6},
            {8, 4, 2, 6},
            {6, 2, 8, 1}
    };//the 10 easy arrays
    char play_again = 'y';
    //loop through and find flags
    int i = 1;
    //this while loop checks for command line flags to update game settings before running
    while ((argc) > 2) {
        if (argv[i][0] == '-') {
            switch (argv[i][1]) {
                case 'e':
                    if (atoi(argv[i + 1]) == 1) {
                        easymode = true;
                    }
                    if (atoi(argv[i + 1]) == 0) {
                        easymode = false;
                    }
                    argc -= 2;
                    break;
                case 'd':
                    if (atoi(argv[i + 1]) == 1) {
                        debugger = true;
                    }
                    if (atoi(argv[i + 1]) == 0) {
                        debugger = false;
                    }
                    argc -= 2;
                    break;
            }
        }
        i++;
    }
    printf("Welcome to the game of TwentyFour.\n");//prompt
    printf("Use each of the four numbers shown below exactly once,\ncombining them somehow with the basic mathematical operators (+,-,*,/)\nto yield the value twenty-four.\n");
    //debugger code first if needed
    if (debugger) {
        int c = 1;
        printf("\n");
        for (int t = 0; t < 3187; t++) {
            printf("%d. %d%c%d%c%d%c%d\n", c, solutions[t][0], debug_solutions[t][0], solutions[t][1],
                   debug_solutions[t][1], solutions[t][2], debug_solutions[t][2], solutions[t][3]);//prints all solutions -1
            c++;
        }
        printf("%d. %d%c%d%c%d%c%d", c, solutions[3187][0], debug_solutions[3187][0], solutions[3187][1],
               debug_solutions[3187][1], solutions[3187][2], debug_solutions[3187][2], solutions[3187][3]);//prints last solution without newline
    }
    //start of game code
    int randomint;
    char symbols[6];
    double answer;
    bool isGood;
    if(easymode){
        while(play_again != 'N'){//only runs if user does not type N when prompted.
            randomint = rand()%10;
            double num1 = easyArray[randomint][0];
            double num2 = easyArray[randomint][1];
            double num3 = easyArray[randomint][2];
            double num4 = easyArray[randomint][3];
            printf("\nThe numbers to use are: %.f, %.f, %.f, %.f.\n",num1,num2,num3,num4);// prints the numbers
            printf("Enter the three operators to be used, in order (+,-,*, or /): ");
            scanf("%s",symbols);
            answer = num1;
            isGood = check(symbols);
            if(!isGood){
                continue;
            }
            //first symbol
            if(symbols[0] == '+'){
                add(&answer, num2,1);
            }
            else if(symbols[0] == '-'){
                minus(&answer, num2, 1);
            }
            else if( symbols[0] == '*'){
                multiply(&answer, num2, 1);
            }
            else if (symbols[0] == '/'){
                divide_easy(&answer, num2, 1);
            }
            //second symbol
            if(symbols[1] == '+'){
                add(&answer, num3,1);
            }
            else if(symbols[1] == '-'){
                minus(&answer, num3, 1);
            }
            else if( symbols[1] == '*'){
                multiply(&answer, num3, 1);
            }
            else if (symbols[1] == '/'){
                divide_easy(&answer, num3, 1);
            }
            //third symbol
            if(symbols[2] == '+'){
                add(&answer, num4,1);
            }
            else if(symbols[2] == '-'){
                minus(&answer, num4, 1);
            }
            else if( symbols[2] == '*'){
                multiply(&answer, num4, 1);
            }
            else if (symbols[2] == '/'){
                divide_easy(&answer, num4, 1);
            }
            //check if answer is correct
            if((answer - 24.0) < 0.001 && ((answer - 24.0) >= 0)){
                printf("Well done! You are a math genius.\n");
            }
            else{
                printf("Sorry. Your solution did not evaluate to 24.\n");
            }
            printf("\nWould you like to play again? Enter N for no and any other character for yes. ");
            fgetc(stdin);
            scanf("%c", &play_again);//asks user for another question

        }
        printf("\nThanks for playing!\n");
    }//same process for else
    else{
        int random;
        while(play_again != 'N'){
            random = rand()%3188;//different rand range

            double num1 = solutions[random][0];
            double num2 = solutions[random][1];
            double num3 = solutions[random][2];
            double num4 = solutions[random][3];//pulls numbers from solutions array
            printf("\nThe numbers to use are: %.f, %.f, %.f, %.f.\n", num1, num2, num3, num4);
            printf("Enter the three operators to be used, in order (+,-,*, or /): ");
            scanf("%s",symbols);
            answer = num1;
            isGood = check(symbols);
            if(!isGood){
                continue;
            }
            //first symbol
            if(symbols[0] == '+'){
                add(&answer, num2,1);
            }
            else if(symbols[0] == '-'){
                minus(&answer, num2, 1);
            }
            else if( symbols[0] == '*'){
                multiply(&answer, num2, 1);
            }
            else if (symbols[0] == '/'){
                divide_easy(&answer, num2, 1);
            }
            //second symbol
            if(symbols[1] == '+'){
                add(&answer, num3,1);
            }
            else if(symbols[1] == '-'){
                minus(&answer, num3, 1);
            }
            else if( symbols[1] == '*'){
                multiply(&answer, num3, 1);
            }
            else if (symbols[1] == '/'){
                divide_easy(&answer, num3, 1);
            }
            //third symbol
            if(symbols[2] == '+'){
                add(&answer, num4,1);
            }
            else if(symbols[2] == '-'){
                minus(&answer, num4, 1);
            }
            else if( symbols[2] == '*'){
                multiply(&answer, num4, 1);
            }
            else if (symbols[2] == '/'){
                divide_easy(&answer, num4, 1);
            }
            //check answer
            if((answer - 24.0) < 0.001 && ((answer - 24.0) >= 0.0)){
                printf("Well done! You are a math genius.\n");
            }
            else{
                printf("Sorry. Your solution did not evaluate to 24.\n");
            }
            printf("\nWould you like to play again? Enter N for no and any other character for yes. ");
            fgetc(stdin);
            scanf("%c", &play_again);//asks for another question

        }
        printf("\nThanks for playing!\n");
    }
    return 0;
}