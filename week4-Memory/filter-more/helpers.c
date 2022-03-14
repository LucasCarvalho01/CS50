#include "helpers.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

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

            right = &image[row][(width - 1) - pixel];

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
    RGBTRIPLE upperAux;
    RGBTRIPLE lowerAux;
    RGBTRIPLE aux;
    int avgRed = 0;
    int avgGreen = 0;
    int avgBlue = 0;
    float counter = 0.0;

    for (int row = 0; row < height; row++)
    {
        for (int pixel = 0; pixel < width; pixel++)
        {
            avgRed = 0;
            avgGreen = 0;
            avgBlue = 0;
            counter = 0.0;

            for (int i = (pixel - 1); i <= (pixel + 1); i++)
            {
                // If the pixel is on the left edge, ignore pixels on the left column
                if (i < 0)
                {
                    continue;
                }
                // If pixel is on the right edge, ignore pixels on the right column
                if (i == width)
                {
                    break;
                }

                // If the pixel is on the first row, there's no pixels above it
                if (row != 0)
                {
                    upperAux = image[row - 1][i];

                    avgRed += upperAux.rgbtRed;
                    avgGreen += upperAux.rgbtGreen;
                    avgBlue += upperAux.rgbtBlue;

                    counter++;
                }

                aux = image[row][i];

                avgRed += aux.rgbtRed;
                avgGreen += aux.rgbtGreen;
                avgBlue += aux.rgbtBlue;

                counter++;

                // If the pixel is on the last row, there's no pixels below it
                if (row != height - 1)
                {
                    lowerAux = image[row + 1][i];

                    avgRed += lowerAux.rgbtRed;
                    avgGreen += lowerAux.rgbtGreen;
                    avgBlue += lowerAux.rgbtBlue;

                    counter++;
                }
            }

            avgRed = round(avgRed / counter);
            avgGreen = round(avgGreen / counter);
            avgBlue = round(avgBlue / counter);

            image[row][pixel].rgbtRed = avgRed;
            image[row][pixel].rgbtGreen = avgGreen;
            image[row][pixel].rgbtBlue = avgBlue;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE upperAux;
    RGBTRIPLE lowerAux;
    RGBTRIPLE aux;
    int gxValues[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    int gyValues[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };
    int sumRedX, sumRedY;
    int sumGreenX, sumGreenY;
    int sumBlueX, sumBlueY;

    for (int row = 0; row < height; row++)
    {
        for (int pixel = 0; pixel < width; pixel++)
        {
            sumRedX = 0;
            sumRedY = 0;
            sumGreenX = 0;
            sumGreenY = 0;
            sumBlueX = 0;
            sumBlueY = 0;

            for (int i = (pixel - 1); i <= pixel + 1; i++)
            {
                // If the pixel is on the left edge, ignores pixels on the left column,
                // since they're considered as solid black pixels
                if (i < 0)
                {
                    continue;
                }

                // If the pixel is on the right edge, ignores pixels on the right column
                if (i == width)
                {
                    break;
                }

                // If the pixel is on the first row, ignores pixels above it
                if (row != 0)
                {
                    upperAux = image[row - 1][i];
                    sumRedX += upperAux.rgbtRed * gxValues[0][i];
                    sumRedY += upperAux.rgbtRed * gyValues[0][i];
                    sumGreenX += upperAux.rgbtGreen * gxValues[0][i];
                    sumGreenY += upperAux.rgbtGreen * gyValues[0][i];
                    sumBlueX += upperAux.rgbtBlue * gxValues[0][i];
                    sumBlueY += upperAux.rgbtBlue * gyValues[0][i];
                }

                aux = image[row][i];
                sumRedX += aux.rgbtRed * gxValues[1][i];
                sumRedY += aux.rgbtRed * gyValues[1][i];
                sumGreenX += aux.rgbtGreen * gxValues[1][i];
                sumGreenY += aux.rgbtGreen * gyValues[1][i];
                sumBlueX += aux.rgbtBlue * gxValues[1][i];
                sumBlueY += aux.rgbtBlue * gyValues[1][i];

                if (row != height - 1)
                {
                    lowerAux = image[row + 1][i];
                    sumRedX += lowerAux.rgbtRed * gxValues[2][i];
                    sumRedY += lowerAux.rgbtRed * gyValues[2][i];
                    sumGreenX += lowerAux.rgbtGreen * gxValues[2][i];
                    sumGreenY += lowerAux.rgbtGreen * gyValues[2][i];
                    sumBlueX += lowerAux.rgbtBlue * gxValues[2][i];
                    sumBlueY += lowerAux.rgbtBlue * gyValues[2][i];
                }
            }

            image[row][pixel].rgbtRed = round(sqrt(pow(sumRedX, 2) + pow(sumRedY, 2)));
            image[row][pixel].rgbtGreen = round(sqrt(pow(sumGreenX, 2) + pow(sumGreenY, 2)));
            image[row][pixel].rgbtBlue = round(sqrt(pow(sumBlueX, 2) + pow(sumBlueY, 2)));
        }
    }
    return;
}


