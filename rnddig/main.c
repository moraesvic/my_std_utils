#include <stdio.h>
#include "../libs/my_random.h"

#define GROUP 4
#define LINE  15
#define TOTAL_LINE (GROUP*LINE)

int main(int argc, char *argv[]){
    int i, dig;
    if(argc != 2)
    {
        printf("rnddig: Please type the desired number of digits.\n");
        return 0;
    }
    time_seed();
    dig = atoi(argv[1]);
    for(i = 0; i < dig; i++){
        printf("%c", '0' + (char)my_randlong_mod(10));
        if(i % GROUP == GROUP - 1) printf(" ");
        if(i % TOTAL_LINE == TOTAL_LINE - 1) printf("\n");
    }
    printf("\n");
    return 0;
}
