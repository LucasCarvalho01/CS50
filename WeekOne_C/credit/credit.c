#include <cs50.h>
#include <stdio.h>
#include <math.h>

/*
    Point to improve the code:
    solving the porblme without the need of arrays.
    Do the modulo on each digit, from left to right, and do the multiplication by 2 if necessary,
    and split the digits, sum and add to the final result.
    If not necessary to double the number, just add it to the final result.
    
    The implementation chosen in the version below was a (unecessary) more complex solution.
*/

int main(void)
{
    long card = get_long("Number: ");

    //declaring constants to help to compare the card number
    const long MAX_NUMBER_13DIG = pow(10, 13);
    const long MIN_NUMBER_13DIG = pow(10, 12) - 1;

    const long MAX_NUMBER_15DIG = pow(10, 15);
    const long MIN_NUMBER_15DIG = pow(10, 14) - 1;

    const long MAX_NUMBER_16DIG = pow(10, 16);
    const long MIN_NUMBER_16DIG = pow(10, 15) - 1;

    //13-digit-card
    if (card < MAX_NUMBER_13DIG && card > MIN_NUMBER_13DIG)
    {
        long digits[13];                //array to store the digits
        long aux = 1000000000000;       //number to help to get the correct digits

        for (int i = 12; i >= 0; i--)   //storing each digit
        {
            digits[i] = card / aux;
            card = card % aux;
            aux /= 10;
        }

        //multiply every other digit by 2, starting with the number's second-to-last digit
        //and then add each digit from those multiplications
        int numbers = 0;
        for (int j = 1; j < 13; j += 2)
        {
            //if greater than 4, need to split the result into digits
            if (digits[j] > 4)
            {
                int dezena = 1;
                int unidade = ((int)digits[j] * 2) % 10;
                numbers += dezena + unidade;
            }
            else
            {
                numbers += (int)digits[j] * 2;
            }
        }

        //getting the sum of the other numbers, added to the previous result
        int totalSum = numbers;
        for (int k = 0; k < 13; k += 2)
        {
            totalSum += (int)digits[k];
        }


        //all Visa's card starts with 4, and if totalSum modulo 10 is congruent
        //to 0, it is a valid card
        if (digits[12] == 4 && (totalSum % 10 == 0))
        {
            printf("VISA\n");
        }

        else
        {
            printf("INVALID\n");
        }

    }

    //15-digit-card
    else if (card < MAX_NUMBER_15DIG && card > MIN_NUMBER_15DIG)
    {
        long digits[15];
        long aux = 100000000000000;     //number to help to get the correct digits

        for (int i = 14; i >= 0; i--)   //storing each digit
        {
            digits[i] = card / aux;
            card = card % aux;
            aux /= 10;
        }

        //multiply every other digit by 2, starting with the number's second-to-last digit
        //and then add each digit from those multiplications
        int numbers = 0;
        for (int j = 1; j < 15; j += 2)
        {
            //if greater than 4, need to split the result into digits
            if (digits[j] > 4)
            {
                int dezena = 1;
                int unidade = ((int)digits[j] * 2) % 10;
                numbers += dezena + unidade;
            }

            else
            {
                numbers += (int)digits[j] * 2;
            }
        }

        //getting the sum of the other numbers, added to the previous result
        int totalSum = numbers;
        for (int k = 0; k < 15; k += 2)
        {
            totalSum += (int)digits[k];
        }


        //AMEX cards uses 15-digit numbers, and all starts with 34 or 37.
        //if totalSum modulo 10 is congruent to 0, it is a valid card
        if ((digits[14] == 3 && (digits[13] == 4 || digits[13] == 7)) && (totalSum % 10 == 0))
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }

    }

    //16-digit-card
    else if (card < MAX_NUMBER_16DIG && card > MIN_NUMBER_16DIG)
    {
        long digits[16];
        long aux = 1000000000000000;     //number to help to get the correct digits

        for (int i = 15; i >= 0; i--)   //storing each digit
        {
            digits[i] = card / aux;
            card = card % aux;
            aux /= 10;
        }

        //multiply every other digit by 2, starting with the number's second-to-last digit
        //and then add each digit from those multiplications
        int numbers = 0;
        for (int j = 1; j < 16; j += 2)
        {
            //if greater than 4, need to split the result into digits
            if (digits[j] > 4)
            {
                int dezena = 1;
                int unidade = ((int)digits[j] * 2) % 10;
                numbers += dezena + unidade;
            }

            else
            {
                numbers += (int)digits[j] * 2;
            }
        }

        //getting the sum of the other numbers, added to the previous result
        int totalSum = numbers;
        for (int k = 0; k < 16; k += 2)
        {
            totalSum += (int)digits[k];
        }

        //MASTERCARD cards use 16-digit numbers and most of them starts with 51, 52, 53, 54 or 55
        //Some VISA cards use 16-digit numbers aswell, and starts with 4
        //In all cases, if totalSum modulo 10 is congruent to 0, it is a valid card
        if ((digits[15] == 5 && digits[14] >= 1 && digits[14] <= 5) && (totalSum % 10 == 0))
        {
            printf("MASTERCARD\n");
        }

        else if ((digits[15] == 4) && (totalSum % 10 == 0))
        {
            printf("VISA\n");
        }

        else
        {
            printf("INVALID\n");
        }

    }

    else
    {
        printf("INVALID\n");
    }

}