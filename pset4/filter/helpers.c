#include <math.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) //look at rows
    {
        for (int j = 0; j < width; j++) //look at pixels
        {
            RGBTRIPLE test = image[i][j];

            float pixel_1 = image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed; //sum of pixel RGB values

            float avg = round(pixel_1 / 3); //calculate average

            image[i][j].rgbtBlue = avg; //update pixel values
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) //look at rows
    {
        for (int j = 0; j < width / 2; j++) //look at pixels
        {
            //swap right and left pixels
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = tmp;
        }
    }
    return;
}

// Blur image
double average(double sum, int x);
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp_image[height][width]; //temp array
    double blue_sum, green_sum, red_sum;

    if (height == 1 && width == 1) //1 x 1 image
    {
        //no changes made
        return;
    }

    else if (height == 1) //image has a height of 1
    {
        for (int i = 0; i < width; i++)
        {
            if (i == 0) //left edge
            {
                blue_sum = image[0][i].rgbtBlue + image[0][i + 1].rgbtBlue;
                green_sum = image[0][i].rgbtGreen + image[0][i + 1].rgbtGreen;
                red_sum = image[0][i].rgbtRed + image[0][i + 1].rgbtRed;

                tmp_image[0][i].rgbtBlue = average(blue_sum, 2);
                tmp_image[0][i].rgbtGreen = average(green_sum, 2);
                tmp_image[0][i].rgbtRed = average(red_sum, 2);
            }

            else if (i == width - 1) //right edge
            {
                blue_sum = image[0][i].rgbtBlue + image[0][i - 1].rgbtBlue;
                green_sum = image[0][i].rgbtGreen + image[0][i - 1].rgbtGreen;
                red_sum = image[0][i].rgbtRed + image[0][i - 1].rgbtRed;

                tmp_image[0][i].rgbtBlue = average(blue_sum, 2);
                tmp_image[0][i].rgbtGreen = average(green_sum, 2);
                tmp_image[0][i].rgbtRed = average(red_sum, 2);
            }

            else //middle pixels
            {
                blue_sum = image[0][i].rgbtBlue + image[0][i - 1].rgbtBlue + image[0][i + 1].rgbtBlue;
                green_sum = image[0][i].rgbtGreen + image[0][i - 1].rgbtGreen + image[0][i + 1].rgbtGreen;
                red_sum = image[0][i].rgbtRed + image[0][i - 1].rgbtRed + image[0][i + 1].rgbtRed;

                tmp_image[0][i].rgbtBlue = average(blue_sum, 3);
                tmp_image[0][i].rgbtGreen = average(green_sum, 3);
                tmp_image[0][i].rgbtRed = average(red_sum, 3);
            }
        }

        //copy tmp into work array
        for (int i = 0; i < width; i++)
        {
            image[0][i].rgbtBlue = tmp_image[0][i].rgbtBlue;
            image[0][i].rgbtGreen = tmp_image[0][i].rgbtGreen;
            image[0][i].rgbtRed = tmp_image[0][i].rgbtRed;
        }

        return; //exit
    }

    else if (width == 1) //image has a width of 1
    {
        for (int i = 0; i < height; i++)
        {
            if (i == 0) //top edge
            {
                blue_sum = image[i][0].rgbtBlue + image[i + 1][0].rgbtBlue;
                green_sum = image[i][0].rgbtGreen + image[i + 1][0].rgbtGreen;
                red_sum = image[i][0].rgbtRed + image[i + 1][0].rgbtRed;

                tmp_image[i][0].rgbtBlue = average(blue_sum, 2);
                tmp_image[i][0].rgbtGreen = average(green_sum, 2);
                tmp_image[i][0].rgbtRed = average(red_sum, 2);
            }

            else if (i == height - 1) //bottom edge
            {
                blue_sum = image[i][0].rgbtBlue + image[i - 1][0].rgbtBlue;
                green_sum = image[i][0].rgbtGreen + image[i - 1][0].rgbtGreen;
                red_sum = image[i][0].rgbtRed + image[i - 1][0].rgbtRed;

                tmp_image[i][0].rgbtBlue = average(blue_sum, 2);
                tmp_image[i][0].rgbtGreen = average(green_sum, 2);
                tmp_image[i][0].rgbtRed = average(red_sum, 2);
            }

            else //middle pixels
            {
                blue_sum = image[i][0].rgbtBlue + image[i - 1][0].rgbtBlue + image[i + 1][0].rgbtBlue;
                green_sum = image[i][0].rgbtGreen + image[i - 1][0].rgbtGreen + image[i + 1][0].rgbtGreen;
                red_sum = image[i][0].rgbtRed + image[i - 1][0].rgbtRed + image[i + 1][0].rgbtRed;

                tmp_image[i][0].rgbtBlue = average(blue_sum, 3);
                tmp_image[i][0].rgbtGreen = average(green_sum, 3);
                tmp_image[i][0].rgbtRed = average(red_sum, 3);
            }
        }

        //copy tmp into work array
        for (int i = 0; i < height; i++)
        {
            image[i][0].rgbtBlue = tmp_image[i][0].rgbtBlue;
            image[i][0].rgbtGreen = tmp_image[i][0].rgbtGreen;
            image[i][0].rgbtRed = tmp_image[i][0].rgbtRed;
        }

        return; //exit
    }

    else if (height == 2 && width >= 2) //image has a height of 2 - no middle row
    {
        for (int j = 0; j < height; j++) //repeat process twice - top and bottom rows share the same 'boxed' grid
            //..(order doesn't matter because you're taking the average of the SAME grid)
        {
            for (int i = 0; i < width; i++)
            {
                if (i == 0) //top/bottom left corner
                {
                    blue_sum = image[0][i].rgbtBlue + image[0][i + 1].rgbtBlue + image[1][i].rgbtBlue + image[1][i + 1].rgbtBlue;
                    green_sum = image[0][i].rgbtGreen + image[0][i + 1].rgbtGreen + image[1][i].rgbtGreen + image[1][i + 1].rgbtGreen;
                    red_sum = image[0][i].rgbtRed + image[0][i + 1].rgbtRed + image[1][i].rgbtRed + image[1][i + 1].rgbtRed;

                    tmp_image[j][i].rgbtBlue = average(blue_sum, 4);
                    tmp_image[j][i].rgbtGreen = average(green_sum, 4);
                    tmp_image[j][i].rgbtRed = average(red_sum, 4);
                }

                else if (i == width - 1) //top/bottom right corner
                {
                    blue_sum = image[0][i].rgbtBlue + image[0][i - 1].rgbtBlue + image[1][i].rgbtBlue + image[1][i - 1].rgbtBlue;
                    green_sum = image[0][i].rgbtGreen + image[0][i - 1].rgbtGreen + image[1][i].rgbtGreen + image[1][i - 1].rgbtGreen;
                    red_sum = image[0][i].rgbtRed + image[0][i - 1].rgbtRed + image[1][i].rgbtRed + image[1][i - 1].rgbtRed;

                    tmp_image[j][i].rgbtBlue = average(blue_sum, 4);
                    tmp_image[j][i].rgbtGreen = average(green_sum, 4);
                    tmp_image[j][i].rgbtRed = average(red_sum, 4);
                }

                else //top/bottom edge
                {
                    blue_sum = image[0][i].rgbtBlue + image[0][i - 1].rgbtBlue + image[0][i + 1].rgbtBlue + image[1][i].rgbtBlue +
                               image[1][i - 1].rgbtBlue + image[1][i + 1].rgbtBlue;
                    green_sum = image[0][i].rgbtGreen + image[0][i - 1].rgbtGreen + image[0][i + 1].rgbtGreen + image[1][i].rgbtGreen +
                                image[1][i - 1].rgbtGreen + image[1][i + 1].rgbtGreen;
                    red_sum = image[0][i].rgbtRed + image[0][i - 1].rgbtRed + image[0][i + 1].rgbtRed + image[1][i].rgbtRed +
                              image[1][i - 1].rgbtRed + image[1][i + 1].rgbtRed;

                    tmp_image[j][i].rgbtBlue = average(blue_sum, 6);
                    tmp_image[j][i].rgbtGreen = average(green_sum, 6);
                    tmp_image[j][i].rgbtRed = average(red_sum, 6);
                }
            }
        }

        //copy tmp into work array
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                image[i][j].rgbtBlue = tmp_image[i][j].rgbtBlue;
                image[i][j].rgbtGreen = tmp_image[i][j].rgbtGreen;
                image[i][j].rgbtRed = tmp_image[i][j].rgbtRed;
            }
        }

        return; //exit
    }

    //**if you've made it this far, the image size is larger than a 3 x 2/ 3 x 3**

    int h = 0; //height counter

    //top edge, at height = 0
    for (int i = 0; i < width; i++)
    {
        if (i == 0) //top left corner
        {
            //calculate B, G, R averages of surrounding pixels
            blue_sum = image[h][i].rgbtBlue + image[h][i + 1].rgbtBlue + image[h + 1][i].rgbtBlue + image[h + 1][i + 1].rgbtBlue;
            green_sum = image[h][i].rgbtGreen + image[h][i + 1].rgbtGreen + image[h + 1][i].rgbtGreen + image[h + 1][i + 1].rgbtGreen;
            red_sum = image[h][i].rgbtRed + image[h][i + 1].rgbtRed + image[h + 1][i].rgbtRed + image[h + 1][i + 1].rgbtRed;

            //store updated pixel in temp array
            tmp_image[h][i].rgbtBlue = average(blue_sum, 4);
            tmp_image[h][i].rgbtGreen = average(green_sum, 4);
            tmp_image[h][i].rgbtRed = average(red_sum, 4);
        }

        else if (i == width - 1) //top right corner
        {
            blue_sum = image[h][i].rgbtBlue + image[h][i - 1].rgbtBlue + image[h + 1][i - 1].rgbtBlue + image[h + 1][i].rgbtBlue;
            green_sum = image[h][i].rgbtGreen + image[h][i - 1].rgbtGreen + image[h + 1][i - 1].rgbtGreen + image[h + 1][i].rgbtGreen;
            red_sum = image[h][i].rgbtRed + image[h][i - 1].rgbtRed + image[h + 1][i - 1].rgbtRed + image[h + 1][i].rgbtRed;

            tmp_image[h][i].rgbtBlue = average(blue_sum, 4);
            tmp_image[h][i].rgbtGreen = average(green_sum, 4);
            tmp_image[h][i].rgbtRed = average(red_sum, 4);
        }

        else //top edge
        {
            blue_sum = image[h][i].rgbtBlue + image[h][i - 1].rgbtBlue + image[h][i + 1].rgbtBlue + image[h + 1][i - 1].rgbtBlue +
                       image[h + 1][i].rgbtBlue + image[h + 1][i + 1].rgbtBlue;
            green_sum = image[h][i].rgbtGreen + image[h][i - 1].rgbtGreen + image[h][i + 1].rgbtGreen + image[h + 1][i - 1].rgbtGreen +
                        image[h + 1][i].rgbtGreen + image[h + 1][i + 1].rgbtGreen;
            red_sum = image[h][i].rgbtRed + image[h][i - 1].rgbtRed + image[h][i + 1].rgbtRed + image[h + 1][i - 1].rgbtRed +
                      image[h + 1][i].rgbtRed + image[h + 1][i + 1].rgbtRed;

            tmp_image[h][i].rgbtBlue = average(blue_sum, 6);
            tmp_image[h][i].rgbtGreen = average(green_sum, 6);
            tmp_image[h][i].rgbtRed = average(red_sum, 6);
        }
    }

    h++; //update height
    int tmp_h = h;

    //middle rows
    for (int i = tmp_h; i < height - 1; i++) //look at middle rows
    {
        for (int j = 0; j < width; j++) //look at pixels
        {
            if (j == 0) //left edge
            {
                blue_sum = image[h][j].rgbtBlue + image[h][j + 1].rgbtBlue + image[h - 1][j].rgbtBlue + image[h - 1][j + 1].rgbtBlue +
                           image[h + 1][j].rgbtBlue + image[h + 1][j + 1].rgbtBlue;
                green_sum = image[h][j].rgbtGreen + image[h][j + 1].rgbtGreen + image[h - 1][j].rgbtGreen + image[h - 1][j + 1].rgbtGreen +
                            image[h + 1][j].rgbtGreen + image[h + 1][j + 1].rgbtGreen;
                red_sum = image[h][j].rgbtRed + image[h][j + 1].rgbtRed + image[h - 1][j].rgbtRed + image[h - 1][j + 1].rgbtRed +
                          image[h + 1][j].rgbtRed + image[h + 1][j + 1].rgbtRed;

                tmp_image[h][j].rgbtBlue = average(blue_sum, 6);
                tmp_image[h][j].rgbtGreen = average(green_sum, 6);
                tmp_image[h][j].rgbtRed = average(red_sum, 6);
            }

            else if (j == width - 1) //right edge
            {
                blue_sum = image[h][j].rgbtBlue + image[h][j - 1].rgbtBlue + image[h - 1][j].rgbtBlue + image[h - 1][j - 1].rgbtBlue +
                           image[h + 1][j].rgbtBlue + image[h + 1][j - 1].rgbtBlue;
                green_sum = image[h][j].rgbtGreen + image[h][j - 1].rgbtGreen + image[h - 1][j].rgbtGreen + image[h - 1][j - 1].rgbtGreen +
                            image[h + 1][j].rgbtGreen + image[h + 1][j - 1].rgbtGreen;
                red_sum = image[h][j].rgbtRed + image[h][j - 1].rgbtRed + image[h - 1][j].rgbtRed + image[h - 1][j - 1].rgbtRed +
                          image[h + 1][j].rgbtRed + image[h + 1][j - 1].rgbtRed;

                tmp_image[h][j].rgbtBlue = average(blue_sum, 6);
                tmp_image[h][j].rgbtGreen = average(green_sum, 6);
                tmp_image[h][j].rgbtRed = average(red_sum, 6);
            }

            else //middle pixels
            {
                blue_sum = image[h][j].rgbtBlue + image[h][ j - 1].rgbtBlue + image[h][j + 1].rgbtBlue + image[h - 1][j - 1].rgbtBlue +
                           image[h - 1][j].rgbtBlue + image[h - 1][j + 1].rgbtBlue + image[h + 1][j - 1].rgbtBlue + image[h + 1][j].rgbtBlue
                           + image[h + 1][j + 1].rgbtBlue;
                green_sum = image[h][j].rgbtGreen + image[h][j - 1].rgbtGreen + image[h][j + 1].rgbtGreen + image[h - 1][j - 1].rgbtGreen +
                            image[h - 1][j].rgbtGreen + image[h - 1][j + 1].rgbtGreen + image[h + 1][j - 1].rgbtGreen + image[h + 1][j].rgbtGreen
                            + image[h + 1][j + 1].rgbtGreen;
                red_sum = image[h][j].rgbtRed + image[h][j - 1].rgbtRed + image[h][j + 1].rgbtRed + image[h - 1][j - 1].rgbtRed +
                          image[h - 1][j].rgbtRed + image[h - 1][j + 1].rgbtRed + image[h + 1][j - 1].rgbtRed + image[h + 1][j].rgbtRed
                          + image[h + 1][j + 1].rgbtRed;

                tmp_image[h][j].rgbtBlue = average(blue_sum, 9);
                tmp_image[h][j].rgbtGreen = average(green_sum, 9);
                tmp_image[h][j].rgbtRed = average(red_sum, 9);
            }
        }

        h++; //update height
    }

    //bottom edge, at height = max height
    for (int i = 0; i < width; i++)
    {
        if (i == 0) //bottom left corner
        {
            blue_sum = image[h][i].rgbtBlue + image[h][i + 1].rgbtBlue + image[h - 1][i].rgbtBlue + image[h - 1][i + 1].rgbtBlue;
            green_sum = image[h][i].rgbtGreen + image[h][i + 1].rgbtGreen + image[h - 1][i].rgbtGreen + image[h - 1][i + 1].rgbtGreen;
            red_sum = image[h][i].rgbtRed + image[h][i + 1].rgbtRed + image[h - 1][i].rgbtRed + image[h - 1][i + 1].rgbtRed;

            tmp_image[h][i].rgbtBlue = average(blue_sum, 4);
            tmp_image[h][i].rgbtGreen = average(green_sum, 4);
            tmp_image[h][i].rgbtRed = average(red_sum, 4);
        }

        else if (i == width - 1) //bottom right corner
        {
            blue_sum = image[h][i].rgbtBlue + image[h][i - 1].rgbtBlue + image[h - 1][i].rgbtBlue + image[h - 1][i - 1].rgbtBlue;
            green_sum = image[h][i].rgbtGreen + image[h][i - 1].rgbtGreen + image[h - 1][i].rgbtGreen + image[h - 1][i - 1].rgbtGreen;
            red_sum = image[h][i].rgbtRed + image[h][i - 1].rgbtRed + image[h - 1][i].rgbtRed + image[h - 1][i - 1].rgbtRed;

            tmp_image[h][i].rgbtBlue = average(blue_sum, 4);
            tmp_image[h][i].rgbtGreen = average(green_sum, 4);
            tmp_image[h][i].rgbtRed = average(red_sum, 4);
        }

        else //bottom edge
        {
            blue_sum = image[h][i].rgbtBlue + image[h][i - 1].rgbtBlue + image[h][i + 1].rgbtBlue + image[h - 1][i - 1].rgbtBlue +
                       image[h - 1][i].rgbtBlue + image[h - 1][i + 1].rgbtBlue;
            green_sum = image[h][i].rgbtGreen + image[h][i - 1].rgbtGreen + image[h][i + 1].rgbtGreen + image[h - 1][i - 1].rgbtGreen +
                        image[h - 1][i].rgbtGreen + image[h - 1][i + 1].rgbtGreen;
            red_sum = image[h][i].rgbtRed + image[h][i - 1].rgbtRed + image[h][i + 1].rgbtRed + image[h - 1][i - 1].rgbtRed +
                      image[h - 1][i].rgbtRed + image[h - 1][i + 1].rgbtRed;

            tmp_image[h][i].rgbtBlue = average(blue_sum, 6);
            tmp_image[h][i].rgbtGreen = average(green_sum, 6);
            tmp_image[h][i].rgbtRed = average(red_sum, 6);
        }
    }

    //copy tmp into work array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = tmp_image[i][j].rgbtBlue;
            image[i][j].rgbtGreen = tmp_image[i][j].rgbtGreen;
            image[i][j].rgbtRed = tmp_image[i][j].rgbtRed;
        }
    }

    return;
}

double average(double sum, int x)
{
    double avg = round(sum / x); //round average
    return avg;
}

// Detect edges
double final_val(long x, long y);
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp_image[height][width]; //temp array
    long B_Gx, G_Gx, R_Gx, B_Gy, G_Gy, R_Gy;

    if (height == 1 && width == 1) //1 x 1 image
    {
        //no changes made
        return;
    }

    else if (height == 1) //image has a height of 1
    {
        for (int i = 0; i < width; i++)
        {
            if (i == 0) //left edge
            {
                //Gx

                B_Gx = (image[0][i + 1].rgbtBlue * 2);

                G_Gx = (image[0][i + 1].rgbtGreen * 2);

                R_Gx = (image[0][i + 1].rgbtRed * 2);

                //Gy

                B_Gy = 0;

                G_Gy = 0;

                R_Gy = 0;

                tmp_image[0][i].rgbtBlue = final_val(B_Gx, B_Gy); //update temp array
                tmp_image[0][i].rgbtGreen = final_val(G_Gx, G_Gy);
                tmp_image[0][i].rgbtRed = final_val(R_Gx, R_Gy);
            }

            else if (i == width - 1) //right edge
            {
                //Gx

                B_Gx = (image[0][i - 1].rgbtBlue * -2);

                G_Gx = (image[0][i - 1].rgbtGreen * -2);

                R_Gx = (image[0][i - 1].rgbtRed * -2);

                //Gy

                B_Gy = 0;

                G_Gy = 0;

                R_Gy = 0;

                tmp_image[0][i].rgbtBlue = final_val(B_Gx, B_Gy); //update temp array
                tmp_image[0][i].rgbtGreen = final_val(G_Gx, G_Gy);
                tmp_image[0][i].rgbtRed = final_val(R_Gx, R_Gy);
            }

            else //middle pixels
            {
                //Gx

                B_Gx = (image[0][i - 1].rgbtBlue * -2) + (image[0][i + 1].rgbtBlue * 2);

                G_Gx = (image[0][i - 1].rgbtGreen * -2) + (image[0][i + 1].rgbtGreen * 2);

                R_Gx = (image[0][i - 1].rgbtRed * -2) + (image[0][i + 1].rgbtRed * 2);

                //Gy

                B_Gy = 0;

                G_Gy = 0;

                R_Gy = 0;

                tmp_image[0][i].rgbtBlue = final_val(B_Gx, B_Gy); //update temp array
                tmp_image[0][i].rgbtGreen = final_val(G_Gx, G_Gy);
                tmp_image[0][i].rgbtRed = final_val(R_Gx, R_Gy);
            }
        }

        //copy tmp into work array
        for (int i = 0; i < width; i++)
        {
            image[0][i].rgbtBlue = tmp_image[0][i].rgbtBlue;
            image[0][i].rgbtGreen = tmp_image[0][i].rgbtGreen;
            image[0][i].rgbtRed = tmp_image[0][i].rgbtRed;
        }

        return; //exit
    }

    else if (width == 1) //image has a width of 1
    {
        for (int i = 0; i < height; i++)
        {
            if (i == 0) //top edge
            {
                //Gx

                B_Gx = 0;

                G_Gx = 0;

                R_Gx = 0;

                //Gy

                B_Gy = (image[i + 1][0].rgbtBlue * 2);

                G_Gy = (image[i + 1][0].rgbtGreen * 2);

                R_Gy = (image[i + 1][0].rgbtRed * 2);

                tmp_image[i][0].rgbtBlue = final_val(B_Gx, B_Gy); //update temp array
                tmp_image[i][0].rgbtGreen = final_val(G_Gx, G_Gy);
                tmp_image[i][0].rgbtRed = final_val(R_Gx, R_Gy);
            }

            else if (i == height - 1) //bottom edge
            {
                //Gx

                B_Gx = 0;

                G_Gx = 0;

                R_Gx = 0;

                //Gy

                B_Gy = (image[i - 1][0].rgbtBlue * -2);

                G_Gy = (image[i - 1][0].rgbtGreen * -2);

                R_Gy = (image[i - 1][0].rgbtRed * -2);

                tmp_image[i][0].rgbtBlue = final_val(B_Gx, B_Gy); //update temp array
                tmp_image[i][0].rgbtGreen = final_val(G_Gx, G_Gy);
                tmp_image[i][0].rgbtRed = final_val(R_Gx, R_Gy);
            }

            else //middle pixels
            {
                //Gx

                B_Gx = 0;

                G_Gx = 0;

                R_Gx = 0;

                //Gy

                B_Gy = (image[i - 1][0].rgbtBlue * -2) + (image[i + 1][0].rgbtBlue * 2);

                G_Gy = (image[i - 1][0].rgbtGreen * -2) + (image[i + 1][0].rgbtGreen * 2);

                R_Gy = (image[i - 1][0].rgbtRed * -2) + (image[i + 1][0].rgbtRed * 2);

                tmp_image[i][0].rgbtBlue = final_val(B_Gx, B_Gy); //update temp array
                tmp_image[i][0].rgbtGreen = final_val(G_Gx, G_Gy);
                tmp_image[i][0].rgbtRed = final_val(R_Gx, R_Gy);
            }
        }

        //copy tmp into work array
        for (int i = 0; i < height; i++)
        {
            image[i][0].rgbtBlue = tmp_image[i][0].rgbtBlue;
            image[i][0].rgbtGreen = tmp_image[i][0].rgbtGreen;
            image[i][0].rgbtRed = tmp_image[i][0].rgbtRed;
        }

        return; //exit
    }

    else if (height == 2 && width >= 2) //image has a height of 2 - no middle row
    {
        //top row, at height = 0
        for (int i = 0; i < width; i++)
        {
            if (i == 0) //top left corner
            {
                //Gx

                B_Gx = (image[0][i + 1].rgbtBlue * 2) + image[1][i + 1].rgbtBlue;

                G_Gx = (image[0][i + 1].rgbtGreen * 2) + image[1][i + 1].rgbtGreen;

                R_Gx = (image[0][i + 1].rgbtRed * 2) + image[1][i + 1].rgbtRed;

                //Gy

                B_Gy = (image[1][i].rgbtBlue * 2) + image[1][i + 1].rgbtBlue;

                G_Gy = (image[1][i].rgbtGreen * 2) + image[1][i + 1].rgbtGreen;

                R_Gy = (image[1][i].rgbtRed * 2) + image[1][i + 1].rgbtRed;

                tmp_image[0][i].rgbtBlue = final_val(B_Gx, B_Gy); //update temp array
                tmp_image[0][i].rgbtGreen = final_val(G_Gx, G_Gy);
                tmp_image[0][i].rgbtRed = final_val(R_Gx, R_Gy);
            }

            else if (i == width - 1) //top right corner
            {
                //Gx

                B_Gx = (image[0][i - 1].rgbtBlue * -2) + (image[1][i - 1].rgbtBlue * -1);

                G_Gx = (image[0][i - 1].rgbtGreen * -2) + (image[1][i - 1].rgbtGreen * -1);

                R_Gx = (image[0][i - 1].rgbtRed * -2) + (image[1][i - 1].rgbtRed * -1);

                //Gy

                B_Gy = (image[1][i].rgbtBlue * 2) + image[1][i - 1].rgbtBlue;

                G_Gy = (image[1][i].rgbtGreen * 2) + image[1][i - 1].rgbtGreen;

                R_Gy = (image[1][i].rgbtRed * 2) + image[1][i - 1].rgbtRed;

                tmp_image[0][i].rgbtBlue = final_val(B_Gx, B_Gy); //update temp array
                tmp_image[0][i].rgbtGreen = final_val(G_Gx, G_Gy);
                tmp_image[0][i].rgbtRed = final_val(R_Gx, R_Gy);
            }

            else //top edge
            {
                //Gx

                B_Gx = (image[0][i - 1].rgbtBlue * -2) + (image[1][i - 1].rgbtBlue * -1) + (image[0][i + 1].rgbtBlue * 2)
                       + image[1][i + 1].rgbtBlue;

                G_Gx = (image[0][i - 1].rgbtGreen * -2) + (image[1][i - 1].rgbtGreen * -1) + (image[0][i + 1].rgbtGreen * 2)
                       + image[1][i + 1].rgbtGreen;

                R_Gx = (image[0][i - 1].rgbtRed * -2) + (image[1][i - 1].rgbtRed * -1) + (image[0][i + 1].rgbtRed * 2)
                       + image[1][i + 1].rgbtRed;

                //Gy

                B_Gy = (image[1][i].rgbtBlue * 2) + image[1][i - 1].rgbtBlue + image[1][i + 1].rgbtBlue;

                G_Gy = (image[1][i].rgbtGreen * 2) + image[1][i - 1].rgbtGreen + image[1][i + 1].rgbtGreen;

                R_Gy = (image[1][i].rgbtRed * 2) + image[1][i - 1].rgbtRed + image[1][i + 1].rgbtRed;

                tmp_image[0][i].rgbtBlue = final_val(B_Gx, B_Gy); //update temp array
                tmp_image[0][i].rgbtGreen = final_val(G_Gx, G_Gy);
                tmp_image[0][i].rgbtRed = final_val(R_Gx, R_Gy);
            }
        }

        //bottom row, at height = 1
        for (int i = 0; i < width; i++)
        {
            if (i == 0) //bottom left corner
            {
                //Gx

                B_Gx = (image[1][i + 1].rgbtBlue * 2) + image[0][i + 1].rgbtBlue;

                G_Gx = (image[1][i + 1].rgbtGreen * 2) + image[0][i + 1].rgbtGreen;

                R_Gx = (image[1][i + 1].rgbtRed * 2) + image[0][i + 1].rgbtRed;

                //Gy

                B_Gy = (image[0][i].rgbtBlue * -2) + (image[0][i + 1].rgbtBlue * -1);

                G_Gy = (image[0][i].rgbtGreen * -2) + (image[0][i + 1].rgbtGreen * -1);

                R_Gy = (image[0][i].rgbtRed * -2) + (image[0][i + 1].rgbtRed * -1);

                tmp_image[1][i].rgbtBlue = final_val(B_Gx, B_Gy); //update temp array
                tmp_image[1][i].rgbtGreen = final_val(G_Gx, G_Gy);
                tmp_image[1][i].rgbtRed = final_val(R_Gx, R_Gy);
            }

            else if (i == width - 1) //bottom right corner
            {
                //Gx

                B_Gx = (image[1][i - 1].rgbtBlue * -2) + (image[0][i - 1].rgbtBlue * -1);

                G_Gx = (image[1][i - 1].rgbtGreen * -2) + (image[0][i - 1].rgbtGreen * -1);

                R_Gx = (image[1][i - 1].rgbtRed * -2) + (image[0][i - 1].rgbtRed * -1);

                //Gy

                B_Gy = (image[0][i].rgbtBlue * -2) + (image[0][i - 1].rgbtBlue * -1);

                G_Gy = (image[0][i].rgbtGreen * -2) + (image[0][i - 1].rgbtGreen * -1);

                R_Gy = (image[0][i].rgbtRed * -2) + (image[0][i - 1].rgbtRed * -1);

                tmp_image[1][i].rgbtBlue = final_val(B_Gx, B_Gy); //update temp array
                tmp_image[1][i].rgbtGreen = final_val(G_Gx, G_Gy);
                tmp_image[1][i].rgbtRed = final_val(R_Gx, R_Gy);
            }

            else //bottom edge
            {
                //Gx

                B_Gx = (image[1][i - 1].rgbtBlue * -2) + (image[0][i - 1].rgbtBlue * -1) + (image[1][i + 1].rgbtBlue * 2)
                       + image[0][i + 1].rgbtBlue;

                G_Gx = (image[1][i - 1].rgbtGreen * -2) + (image[0][i - 1].rgbtGreen * -1) + (image[1][i + 1].rgbtGreen * 2)
                       + image[0][i + 1].rgbtGreen;

                R_Gx = (image[1][i - 1].rgbtRed * -2) + (image[0][i - 1].rgbtRed * -1) + (image[1][i + 1].rgbtRed * 2)
                       + image[0][i + 1].rgbtRed;

                //Gy

                B_Gy = (image[0][i - 1].rgbtBlue * -1) + (image[0][i].rgbtBlue * -2) + (image[0][i + 1].rgbtBlue * -1);

                G_Gy = (image[0][i - 1].rgbtGreen * -1) + (image[0][i].rgbtGreen * -2) + (image[0][i + 1].rgbtGreen * -1);

                R_Gy = (image[0][i - 1].rgbtRed * -1) + (image[0][i].rgbtRed * -2) + (image[0][i + 1].rgbtRed * -1);

                tmp_image[1][i].rgbtBlue = final_val(B_Gx, B_Gy); //update temp array
                tmp_image[1][i].rgbtGreen = final_val(G_Gx, G_Gy);
                tmp_image[1][i].rgbtRed = final_val(R_Gx, R_Gy);
            }
        }

        //copy tmp into work array
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                image[i][j].rgbtBlue = tmp_image[i][j].rgbtBlue;
                image[i][j].rgbtGreen = tmp_image[i][j].rgbtGreen;
                image[i][j].rgbtRed = tmp_image[i][j].rgbtRed;
            }
        }

        return; //exit
    }

    //**if you've made it this far, the image size is larger than a 3 x 2/ 3 x 3**

    int h = 0; //height counter

    for (int i = 0; i < width; i++)
    {
        if (i == 0) //top left corner
        {
            //Gx

            B_Gx = (image[h][i + 1].rgbtBlue * 2) + image[h + 1][i + 1].rgbtBlue;

            G_Gx = (image[h][i + 1].rgbtGreen * 2) + image[h + 1][i + 1].rgbtGreen;

            R_Gx = (image[h][i + 1].rgbtRed * 2) + image[h + 1][i + 1].rgbtRed;

            //Gy

            B_Gy = (image[h + 1][i].rgbtBlue * 2) + image[h + 1][i + 1].rgbtBlue;

            G_Gy = (image[h + 1][i].rgbtGreen * 2) + image[h + 1][i + 1].rgbtGreen;

            R_Gy = (image[h + 1][i].rgbtRed * 2) + image[h + 1][i + 1].rgbtRed;

            tmp_image[h][i].rgbtBlue = final_val(B_Gx, B_Gy); //update temp array
            tmp_image[h][i].rgbtGreen = final_val(G_Gx, G_Gy);
            tmp_image[h][i].rgbtRed = final_val(R_Gx, R_Gy);
        }

        else if (i == width - 1) //top right corner
        {
            //Gx

            B_Gx = (image[h][i - 1].rgbtBlue * -2) + (image[h + 1][i - 1].rgbtBlue * -1);

            G_Gx = (image[h][i - 1].rgbtGreen * -2) + (image[h + 1][i - 1].rgbtGreen * -1);

            R_Gx = (image[h][i - 1].rgbtRed * -2) + (image[h + 1][i - 1].rgbtRed * -1);

            //Gy

            B_Gy = (image[h + 1][i].rgbtBlue * 2) + image[h + 1][i - 1].rgbtBlue;

            G_Gy = (image[h + 1][i].rgbtGreen * 2) + image[h + 1][i - 1].rgbtGreen;

            R_Gy = (image[h + 1][i].rgbtRed * 2) + image[h + 1][i - 1].rgbtRed;

            tmp_image[h][i].rgbtBlue = final_val(B_Gx, B_Gy); //update temp array
            tmp_image[h][i].rgbtGreen = final_val(G_Gx, G_Gy);
            tmp_image[h][i].rgbtRed = final_val(R_Gx, R_Gy);
        }

        else //top edge
        {
            //Gx

            B_Gx = (image[h][i - 1].rgbtBlue * -2) + (image[h + 1][i - 1].rgbtBlue * -1) + (image[h][i + 1].rgbtBlue * 2)
                   + image[h + 1][i + 1].rgbtBlue;

            G_Gx = (image[h][i - 1].rgbtGreen * -2) + (image[h + 1][i - 1].rgbtGreen * -1) + (image[h][i + 1].rgbtGreen * 2)
                   + image[h + 1][i + 1].rgbtGreen;

            R_Gx = (image[h][i - 1].rgbtRed * -2) + (image[h + 1][i - 1].rgbtRed * -1) + (image[h][i + 1].rgbtRed * 2)
                   + image[h + 1][i + 1].rgbtRed;

            //Gy

            B_Gy = (image[h + 1][i].rgbtBlue * 2) + image[h + 1][i - 1].rgbtBlue + image[h + 1][i + 1].rgbtBlue;

            G_Gy = (image[h + 1][i].rgbtGreen * 2) + image[h + 1][i - 1].rgbtGreen + image[h + 1][i + 1].rgbtGreen;

            R_Gy = (image[h + 1][i].rgbtRed * 2) + image[h + 1][i - 1].rgbtRed + image[h + 1][i + 1].rgbtRed;

            tmp_image[h][i].rgbtBlue = final_val(B_Gx, B_Gy); //update temp array
            tmp_image[h][i].rgbtGreen = final_val(G_Gx, G_Gy);
            tmp_image[h][i].rgbtRed = final_val(R_Gx, R_Gy);
        }
    }

    h++; //update height
    int tmp_h = h;

    //middle rows
    for (int i = tmp_h; i < height - 1; i++) //look at rows
    {
        for (int j = 0; j < width; j++) //look at pixels
        {
            if (j == 0) //left edge
            {
                //Gx

                B_Gx = (image[h][j + 1].rgbtBlue * 2) + image[h - 1][j + 1].rgbtBlue + image[h + 1][j + 1].rgbtBlue;

                G_Gx = (image[h][j + 1].rgbtGreen * 2) + image[h - 1][j + 1].rgbtGreen + image[h + 1][j + 1].rgbtGreen;

                R_Gx = (image[h][j + 1].rgbtRed * 2) + image[h - 1][j + 1].rgbtRed + image[h + 1][j + 1].rgbtRed;

                //Gy

                B_Gy = (image[h - 1][j].rgbtBlue * -2) + (image[h - 1][j + 1].rgbtBlue * -1) + (image[h + 1][j].rgbtBlue * 2)
                       + image[h + 1][j + 1].rgbtBlue;

                G_Gy = (image[h - 1][j].rgbtGreen * -2) + (image[h - 1][j + 1].rgbtGreen * -1) + (image[h + 1][j].rgbtGreen * 2)
                       + image[h + 1][j + 1].rgbtGreen;

                R_Gy = (image[h - 1][j].rgbtRed * -2) + (image[h - 1][j + 1].rgbtRed * -1) + (image[h + 1][j].rgbtRed * 2)
                       + image[h + 1][j + 1].rgbtRed;

                tmp_image[h][j].rgbtBlue = final_val(B_Gx, B_Gy); //update temp array
                tmp_image[h][j].rgbtGreen = final_val(G_Gx, G_Gy);
                tmp_image[h][j].rgbtRed = final_val(R_Gx, R_Gy);
            }

            else if (j == width - 1) //right edge
            {
                //Gx

                B_Gx = (image[h][j - 1].rgbtBlue * -2) + (image[h - 1][j - 1].rgbtBlue * -1) + (image[h + 1][j - 1].rgbtBlue * -1);

                G_Gx = (image[h][j - 1].rgbtGreen * -2) + (image[h - 1][j - 1].rgbtGreen * -1) + (image[h + 1][j - 1].rgbtGreen * -1);

                R_Gx = (image[h][j - 1].rgbtRed * -2) + (image[h - 1][j - 1].rgbtRed * -1) + (image[h + 1][j - 1].rgbtRed * -1);

                //Gy

                B_Gy = (image[h - 1][j].rgbtBlue * -2) + (image[h - 1][j - 1].rgbtBlue * -1) + (image[h + 1][j].rgbtBlue * 2)
                       + image[h + 1][j - 1].rgbtBlue;

                G_Gy = (image[h - 1][j].rgbtGreen * -2) + (image[h - 1][j - 1].rgbtGreen * -1) + (image[h + 1][j].rgbtGreen * 2)
                       + image[h + 1][j - 1].rgbtGreen;

                R_Gy = (image[h - 1][j].rgbtRed * -2) + (image[h - 1][j - 1].rgbtRed * -1) + (image[h + 1][j].rgbtRed * 2)
                       + image[h + 1][j - 1].rgbtRed;

                tmp_image[h][j].rgbtBlue = final_val(B_Gx, B_Gy); //update temp array
                tmp_image[h][j].rgbtGreen = final_val(G_Gx, G_Gy);
                tmp_image[h][j].rgbtRed = final_val(R_Gx, R_Gy);
            }

            else //middle pixels
            {
                //Gx

                B_Gx = (image[h][j + 1].rgbtBlue * 2) + image[h - 1][j + 1].rgbtBlue + image[h + 1][j + 1].rgbtBlue
                       + (image[h][j - 1].rgbtBlue * -2) + (image[h - 1][j - 1].rgbtBlue * -1)
                       + (image[h + 1][j - 1].rgbtBlue * -1);

                G_Gx = (image[h][j + 1].rgbtGreen * 2) + image[h - 1][j + 1].rgbtGreen + image[h + 1][j + 1].rgbtGreen
                       + (image[h][j - 1].rgbtGreen * -2) + (image[h - 1][j - 1].rgbtGreen * -1)
                       + (image[h + 1][j - 1].rgbtGreen * -1);

                R_Gx = (image[h][j + 1].rgbtRed * 2) + image[h - 1][j + 1].rgbtRed + image[h + 1][j + 1].rgbtRed
                       + (image[h][j - 1].rgbtRed * -2) + (image[h - 1][j - 1].rgbtRed * -1)
                       + (image[h + 1][j - 1].rgbtRed * -1);

                //Gy

                B_Gy = (image[h - 1][j].rgbtBlue * -2) + (image[h - 1][j - 1].rgbtBlue * -1) + (image[h - 1][j + 1].rgbtBlue * -1)
                       + (image[h + 1][j].rgbtBlue * 2) + image[h + 1][j - 1].rgbtBlue + image[h + 1][j + 1].rgbtBlue;

                G_Gy = (image[h - 1][j].rgbtGreen * -2) + (image[h - 1][j - 1].rgbtGreen * -1) + (image[h - 1][j + 1].rgbtGreen * -1)
                       + (image[h + 1][j].rgbtGreen * 2) + image[h + 1][j - 1].rgbtGreen + image[h + 1][j + 1].rgbtGreen;

                R_Gy = (image[h - 1][j].rgbtRed * -2) + (image[h - 1][j - 1].rgbtRed * -1) + (image[h - 1][j + 1].rgbtRed * -1)
                       + (image[h + 1][j].rgbtRed * 2) + image[h + 1][j - 1].rgbtRed + image[h + 1][j + 1].rgbtRed;

                tmp_image[h][j].rgbtBlue = final_val(B_Gx, B_Gy); //update temp array
                tmp_image[h][j].rgbtGreen = final_val(G_Gx, G_Gy);
                tmp_image[h][j].rgbtRed = final_val(R_Gx, R_Gy);
            }
        }

        h++; //update height
    }

    //bottom row
    for (int i = 0; i < width; i++)
    {
        if (i == 0) //bottom left corner
        {
            //Gx

            B_Gx = (image[h][i + 1].rgbtBlue * 2) + image[h - 1][i + 1].rgbtBlue;

            G_Gx = (image[h][i + 1].rgbtGreen * 2) + image[h - 1][i + 1].rgbtGreen;

            R_Gx = (image[h][i + 1].rgbtRed * 2) + image[h - 1][i + 1].rgbtRed;

            //Gy

            B_Gy = (image[h - 1][i].rgbtBlue * -2) + (image[h - 1][i + 1].rgbtBlue * -1);

            G_Gy = (image[h - 1][i].rgbtGreen * -2) + (image[h - 1][i + 1].rgbtGreen * -1);

            R_Gy = (image[h - 1][i].rgbtRed * -2) + (image[h - 1][i + 1].rgbtRed * -1);

            tmp_image[h][i].rgbtBlue = final_val(B_Gx, B_Gy); //update temp array
            tmp_image[h][i].rgbtGreen = final_val(G_Gx, G_Gy);
            tmp_image[h][i].rgbtRed = final_val(R_Gx, R_Gy);
        }

        else if (i == width - 1) //bottom right corner
        {
            //Gx

            B_Gx = (image[h][i - 1].rgbtBlue * -2) + (image[h - 1][i - 1].rgbtBlue * -1);

            G_Gx = (image[h][i - 1].rgbtGreen * -2) + (image[h - 1][i - 1].rgbtGreen * -1);

            R_Gx = (image[h][i - 1].rgbtRed * -2) + (image[h - 1][i - 1].rgbtRed * -1);

            //Gy

            B_Gy = (image[h - 1][i].rgbtBlue * -2) + (image[h - 1][i - 1].rgbtBlue * -1);

            G_Gy = (image[h - 1][i].rgbtGreen * -2) + (image[h - 1][i - 1].rgbtGreen * -1);

            R_Gy = (image[h - 1][i].rgbtRed * -2) + (image[h - 1][i - 1].rgbtRed * -1);

            tmp_image[h][i].rgbtBlue = final_val(B_Gx, B_Gy); //update temp array
            tmp_image[h][i].rgbtGreen = final_val(G_Gx, G_Gy);
            tmp_image[h][i].rgbtRed = final_val(R_Gx, R_Gy);
        }

        else //bottom edge
        {
            //Gx

            B_Gx = (image[h][i - 1].rgbtBlue * -2) + (image[h - 1][i - 1].rgbtBlue * -1) + (image[h][i + 1].rgbtBlue * 2)
                   + image[h - 1][i + 1].rgbtBlue;

            G_Gx = (image[h][i - 1].rgbtGreen * -2) + (image[h - 1][i - 1].rgbtGreen * -1) + (image[h][i + 1].rgbtGreen * 2)
                   + image[h - 1][i + 1].rgbtGreen;

            R_Gx = (image[h][i - 1].rgbtRed * -2) + (image[h - 1][i - 1].rgbtRed * -1) + (image[h][i + 1].rgbtRed * 2)
                   + image[h - 1][i + 1].rgbtRed;

            //Gy

            B_Gy = (image[h - 1][i - 1].rgbtBlue * -1) + (image[h - 1][i].rgbtBlue * -2) + (image[h - 1][i + 1].rgbtBlue * -1);

            G_Gy = (image[h - 1][i - 1].rgbtGreen * -1) + (image[h - 1][i].rgbtGreen * -2) + (image[h - 1][i + 1].rgbtGreen * -1);

            R_Gy = (image[h - 1][i - 1].rgbtRed * -1) + (image[h - 1][i].rgbtRed * -2) + (image[h - 1][i + 1].rgbtRed * -1);

            tmp_image[h][i].rgbtBlue = final_val(B_Gx, B_Gy); //update temp array
            tmp_image[h][i].rgbtGreen = final_val(G_Gx, G_Gy);
            tmp_image[h][i].rgbtRed = final_val(R_Gx, R_Gy);
        }
    }

    //copy tmp into work array

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = tmp_image[i][j].rgbtBlue;
            image[i][j].rgbtGreen = tmp_image[i][j].rgbtGreen;
            image[i][j].rgbtRed = tmp_image[i][j].rgbtRed;
        }
    }

    return;
}

double final_val(long x, long y)
{
    double sum = pow(x, 2) + pow(y, 2);
    double root = sqrt(sum);
    double final = round(root);

    if (final > 255)
    {
        final = 255; //cap at 255
    }

    return final;
}