#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //TODO
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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //TODO
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int rgb[4];

            float sepiaRed = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
            if (sepiaRed > 255)
            {
                rgb[0] = 255;
            }
            else
            {
                rgb[0] = roundf(sepiaRed);
            }

            float sepiaGreen = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
            if (sepiaGreen > 255)
            {
                rgb[1] = 255;
            }
            else
            {
                rgb[1] = roundf(sepiaGreen);
            }

            float sepiaBlue = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;
            if (sepiaBlue > 255)
            {
                rgb[2] = 255;
            }
            else
            {
                rgb[2] = roundf(sepiaBlue);
            }

            image[i][j].rgbtRed = rgb[0];
            image[i][j].rgbtGreen = rgb[1];
            image[i][j].rgbtBlue = rgb[2];
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //TODO
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
    //TODO
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
}
