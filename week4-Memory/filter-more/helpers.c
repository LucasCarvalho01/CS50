#include "helpers.h"
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterates over each row of pixels of the image
    for (int row = 0; row < height; row++)
    {
        // Iterates over each pixel of each row
        for (int pixel = 0; pixel < width; pixel++)
        {
            // Calculates the avg of amount of red, green and blue, and set them to the avg
            // Making the pixel a shade of gray
            BYTE *red = &image[row][pixel].rgbtRed;
            BYTE *green = &image[row][pixel].rgbtGreen;
            BYTE *blue = &image[row][pixel].rgbtBlue;

            BYTE avg = (BYTE) round((*red + *green + *blue) / 3.0);

            *red = avg;
            *green = avg;
            *blue = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE *left, *right;
    for (int row = 0; row < height; row++)
    {
        for (int pixel = 0; pixel < width; pixel++)
        {
            // If left pointer points to the same as right pointer, break
            if (pixel >= (width - 1) - pixel)
            {
                break;
            }

            left = &image[row][pixel];
            // if (left == right)
            // {
            //     break;
            // }

            right = &image[row][(width - 1) - pixel];
            // if (right == left)
            // {
            //     break;
            // }

            RGBTRIPLE aux;
            aux = *left;
            *left = *right;
            *right = aux;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE *upperPointer = NULL;
    RGBTRIPLE *lowerPointer = NULL;
    RGBTRIPLE *computing = NULL;
    int avgRed = 0;
    int avgGreen = 0;
    int avgBlue = 0;

    for (int row = 0; row < height; row++)
    {
        if (row != 0)
        {
            upperPointer = &image[row - 1][0];
        }

        if (row != height - 1)
        {
            lowerPointer = &image[row + 1][0];
        }

        for (int pixel = 0; pixel < width; pixel++)
        {
            BYTE sumRed = 0;
            BYTE sumGreen = 0;
            BYTE sumBlue = 0;

            computing = &image[row][pixel];
             RGBTRIPLE teste = *(computing);
             BYTE teste2 = teste.rgbtBlue;

            if (pixel != 0)
            {
                // computing--;
                // sumRed += *(computing->rgbtRed);
                // sumGreen += *computing->rgbtGreen;
                // sumBlue += *computing->rgbtBlue;
            }


        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}


