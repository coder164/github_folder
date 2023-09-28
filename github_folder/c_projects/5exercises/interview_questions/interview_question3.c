/*
question:
how can you print the pure address of int variable, with %p,
without any casting in the printf line?
you can compile without the -pedantic flag.
answer:
char* pointers are displayed as pure virtuals, therefor you
should store the address of that int variable int a char*
pointer and print him. to do that you need to cast the address
of int to address of char.
*/
#include <stdio.h>

int main()
{
    int a = 5;  /* store lvalue to get actual memory */
    char* ptr = (char*)&a;
    printf("%p\n", ptr);    /* something like 0x7ffd3cb0084c */
    return 0;
}
