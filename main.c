#include <stdio.h>
#include <stdlib.h>
#include "skel.h"

int main(int argc, char *argv[])
{
    /*****this program is about calculator****/
    /*this list is about input and outputs*/
    d_list *expA = NULL;
    d_list *evaB = NULL;
    d_list *result = NULL;

    /*slice the arguments and store it in seperate list*/
    seperate(argv[1], &expA, &evaB, &result);

}
