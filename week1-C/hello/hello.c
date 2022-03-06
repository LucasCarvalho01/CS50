#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // gets the user name and stores it in a variable
    string userName = get_string("What's your name? ");

    // then, prints hello X, where X is the name got in the previous step
    printf("hello, %s\n", userName);
}