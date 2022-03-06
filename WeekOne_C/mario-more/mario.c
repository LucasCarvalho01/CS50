#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int pyHeight;

    //get the pyramid's height from the user
    //will keeping ask until a valid number, between 1 and 8 (inclusives)
    do
    {
        pyHeight = get_int("How tall is the pyramid? ");
    }
    while (pyHeight < 1 || pyHeight > 8);

    //for each row
    for (int i = 1; i <= pyHeight; i++)
    {
        int aux = i;

        //if it's not the last row, add blank spaces to the left
        while ((pyHeight - aux) > 0)
        {
            printf(" ");
            aux++;
        }

        //each column
        //left half
        for (int j = i; j > 0; j--)
        {
            printf("#");
        }

        //spaces to separate halves
        printf("  ");

        //right half
        for (int k = i; k > 0; k--)
        {
            printf("#");
        }

        //jump to new row
        printf("\n");
    }
}