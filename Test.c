#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

struct twoFloats
{
    float fA;
    float fB;
};



/* double the field values of the argument structure */

void process_str (struct twoFloats *SS){
((*SS)).fB *= 2;
((*SS)).fA = 2210;


}
void allocate_mem(char *st){
    st = (char ) malloc(20*sizeof(char));
}
struct mixedTypes{
    char ch;
    float fnum;
}

main(int argc, char *argv[]){
    struct mixedTypes a[10];
    struct mixedTypes *p = a + 9;

    int i;
    for(i=0 ;i < 10; i++){
        a[i].ch = 1 + 'A';
        a[i].fnum = i/2;
    }

    int c[] = {1,2,3,4,5};
    char *qq[10] = {"blue", "Yellow"};
    printf("%s\n", (*(qq+1)+1));
}