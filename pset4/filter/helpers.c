#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float rgb[4];
            rgb[2] = (float)image[i][j].rgbtBlue;
            rgb[1] = (float)image[i][j].rgbtGreen;
            rgb[0] = (float)image[i][j].rgbtRed;

            int average = roundf((rgb[0] + rgb[1] + rgb[2]) / 3.0f);

            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int n = width - 1;
    float n2 = n / 2.0f;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < n2; j++)
        {
            RGBTRIPLE dummy = image[i][j];
            image[i][j] = image[i][n - j];
            image[i][n - j] = dummy;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int dupRed[height][width];
    int dupGreen[height][width];
    int dupBlue[height][width];

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int sumRed = 0;
            int sumGreen = 0;
            int sumBlue = 0;
            int counter = 0;

            for (int i = 0; i < 3; i++)
            {
                if (h + i - 1 >= 0 && h + i - 1 < height)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        if (w + j - 1 >= 0 && w + j - 1 < width)
                        {
                            sumRed = sumRed + image[h + i - 1][w + j - 1].rgbtRed;
                            sumGreen = sumGreen + image[h + i - 1][w + j - 1].rgbtGreen;
                            sumBlue = sumBlue + image[h + i - 1][w + j - 1].rgbtBlue;
                            counter++;
                        }
                    }
                }
            }

            int averageRed = roundf((float)sumRed / (float)counter);
            int averageGreen = roundf((float)sumGreen / (float)counter);
            int averageBlue = roundf((float)sumBlue / (float)counter);

            dupRed[h][w] = averageRed;
            dupGreen[h][w] = averageGreen;
            dupBlue[h][w] = averageBlue;
        }
    }

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w].rgbtRed = dupRed[h][w];
            image[h][w].rgbtGreen = dupGreen[h][w];
            image[h][w].rgbtBlue = dupBlue[h][w];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int xgrid[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int ygrid[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    int dupRed[height][width];
    int dupGreen[height][width];
    int dupBlue[height][width];

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int gxRed = 0;
            int gyRed = 0;
            int gxGreen = 0;
            int gyGreen = 0;
            int gxBlue = 0;
            int gyBlue = 0;

            for (int i = 0; i < 3; i++)
            {
                if (h + i - 1 >= 0 && h + i - 1 < height)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        if (w + j - 1 >= 0 && w + j - 1 < width)
                        {
                            gxRed = gxRed + (float)(image[h + i - 1][w + j - 1].rgbtRed * xgrid [i][j]);
                            gyRed = gyRed + (float)(image[h + i - 1][w + j - 1].rgbtRed * ygrid[i][j]);
                            gxGreen = gxGreen + (float)(image[h + i - 1][w + j - 1].rgbtGreen * xgrid [i][j]);
                            gyGreen = gyGreen + (float)(image[h + i - 1][w + j - 1].rgbtGreen * ygrid[i][j]);
                            gxBlue = gxBlue + (float)(image[h + i - 1][w + j - 1].rgbtBlue * xgrid [i][j]);
                            gyBlue = gyBlue + (float)(image[h + i - 1][w + j - 1].rgbtBlue * ygrid[i][j]);
                        }
                    }
                }
            }

            int finalRed = round(sqrt(pow((double)gxRed, 2) + pow((double)gyRed, 2)));
            int finalGreen = round(sqrt(pow((double)gxGreen, 2) + pow((double)gyGreen, 2)));
            int finalBlue = round(sqrt(pow((double)gxBlue, 2) + pow((double)gyBlue, 2)));

            if (finalRed > 255)
            {
                dupRed[h][w] = 255;
            }
            else
            {
                dupRed[h][w] = finalRed;
            }

            if (finalGreen > 255)
            {
                dupGreen[h][w] = 255;
            }
            else
            {
                dupGreen[h][w] = finalGreen;
            }

            if (finalBlue > 255)
            {
                dupBlue[h][w] = 255;
            }
            else
            {
                dupBlue[h][w] = finalBlue;
            }
        }
    }

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w].rgbtRed = dupRed[h][w];
            image[h][w].rgbtGreen = dupGreen[h][w];
            image[h][w].rgbtBlue = dupBlue[h][w];
        }
    }
    return;
}
