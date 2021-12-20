#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
//TODO: make sure input is valid and validate arguments
    if (argc != 2)
    {
        printf("Usage: ./recover <source data>");
        return 1;
    }


    FILE *f_in = fopen(argv[1], "r");
    //checks is inpoutfile fails to open
    if (f_in == NULL)
    {
        printf("Could not open file.\n");
        return 2;
    }

//TODO: Open memory card
    //read 512 bytes into buffer
    unsigned char buffer[512];
    //Counter for the filename,001, 002...
    int jpg_num = 0;

    //file pointing to nothing
    FILE *f_out = NULL;

    //Declare the string for the file name using malloc
    char *file = malloc(8 * sizeof(char));

    //Read in 512 byt chunks from f (file input) and write to buffer
    while (fread(buffer, sizeof(char), 512, f_in))
    {
        //test the buffer  see if jpeg header is found, indicates new jpeg
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && (buffer[3] & 0xf0) == 0xe0)
        {
            //write the output file in format 001.jpg, 002.jpg...
            sprintf(file, "%03i.jpg", jpg_num);

            //open new JPEG file
            f_out = fopen(file, "w");
            jpg_num++;
        }
        //test if out has been filled with some data, not NULL
        if (f_out != NULL)
        {
            //write the file
            fwrite(buffer, sizeof(char), 512, f_out);
        }

    }
    free(file);
    fclose(f_in);
    fclose(f_out);
//TODO: Look for beginning of JPEG (JPEG HEADER)
//
//
//
//(


//TODO: Open a new JPEG file



//TODO: Write 512 bytes until a new JPG is found
//fwrite(data,size, number, outptr);


//Stop at the end of the file

    return 0;
}