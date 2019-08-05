#include <stdio.h>
#include <math.h>

int main(int argc, char const *argv[]) {
    int x,y,z;
    float d;
    int p = pow(3,2);
    printf("3 ^ 2 = %d\n", p);
    printf("inserire elemento ");
    scanf("%d",&x);
    printf("hai inserito %d\n", x);
    y=3;z=2;
    d=(float)y/z;
    printf("%d / %d = %.2f \n",y,z,d);
    return 0;
}
