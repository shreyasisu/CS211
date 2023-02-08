// Online C compiler to run C program online
#include <stdio.h>
double divide(double x, double y, int isPrint){
    double z;
    z = (int)x / (int)y;

    //z = (int)z;
    if(isPrint == 1){
        printf("%.f / %.f = %.f.\n", x, y, z);
    }
    return z;
}
int main() {
    divide(12,8,1);

    return 0;
}