#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //iterate over the rows
    for (int i = 0; i < height; i++)
    {
        //iterate over the coumns
        for (int j = 0; j < width; j++)
        {
            //store the values of each pixel
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;

            // find the average of each rgb pixel
            int avg = round(((float)red + (float)green + (float)blue) / 3);

            //set each rgb of the pixel to the same average value calculated above
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    //iterate over the rows
    for (int i = 0; i < height; i++)
    {
        //iterate over the coumns
        for (int j = 0; j < width; j++)
        {
            //store the values of each pixel
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;

            //calculate sepiaRed, sepiaGreen, SepiaBlue
            int sepiaRed = round(((0.393 * red) + (0.769 * green) + (0.189 * blue)));
            int sepiaGreen = round(((0.349 * red) + (0.686 * green) + (0.168 * blue)));
            int sepiaBlue = round(((0.272 * red) + (0.534 * green) + (0.131 * blue)));

            // sets the pixel to sepia, and if the value is > 255, set 255 as the value

            //checks Red
            if (sepiaRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = sepiaRed;
            }

            //checks Green
            if (sepiaGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }

            //Checks Blue
            if (sepiaBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }
        }
    }


    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //iterate over the rows
    for (int i = 0; i < height; i++)
    {
        //iterate over the coumns
        for (int j = 0; j < (width / 2); j++)
        {
            //store the values of each pixel
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;

            //Store the right half of the image to the original image
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;

            //Store the temp image to the right image
            image[i][width - j - 1].rgbtRed = red;
            image[i][width - j - 1].rgbtGreen = green;
            image[i][width - j - 1].rgbtBlue = blue;
        }
    }


    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //store the image to a new blurred image
    RGBTRIPLE blurred[height][width];

    //iterate over the rows
    for (int i = 0; i < height; i++)
    {
        //iterate over the coumns
        for (int j = 0; j < width; j++)
        {
            int reds = 0, blues = 0, greens = 0;
            float num = 0.00;

            // find the surrounding pixels, by iterating over rows and columns
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    int Xindex = i + x;
                    int Yindex = j + y;

                    //verify the surrounding pixels are valid
                    if ((Xindex < 0) || (Xindex > (height - 1)) || (Yindex < 0) || Yindex > (width - 1))
                    {
                        continue;
                    }

                    //Add up the values
                    reds += image[Xindex][Yindex].rgbtRed;
                    greens += image[Xindex][Yindex].rgbtGreen;
                    blues += image[Xindex][Yindex].rgbtBlue;

                    num++;
                }

                //Calculate the average of the surrounding pixels and save to blurred
                blurred[i][j].rgbtRed = round(reds / num);
                blurred[i][j].rgbtGreen = round(greens / num);
                blurred[i][j].rgbtBlue = round(blues / num);

            }

        }
    }

    //Copy blurred to original
    //iterate over the rows
    for (int i = 0; i < height; i++)
    {
        //iterate over the coumns
        for (int j = 0; j < width; j++)
        {
            //store the values of each pixel
            image[i][j].rgbtRed = blurred[i][j].rgbtRed;
            image[i][j].rgbtGreen = blurred[i][j].rgbtGreen;
            image[i][j].rgbtBlue = blurred[i][j].rgbtBlue;
        }
    }

    return;
}
