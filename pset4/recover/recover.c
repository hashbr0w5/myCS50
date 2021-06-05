#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: recover infile");
        return 1;
    }

    FILE *inptr = fopen(argv[1], "r");

    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 1;
    }

    BYTE *buffer = malloc(512 * sizeof(BYTE)); //allocate memory for first '512' B block
    BYTE *tmp1 = buffer; //pointer -> first byte in buffer

    //keep re-reading into the first block in buffer until we get a valid header
    do
    {
        buffer = tmp1; //reset pointer to start of block
        fread(buffer, sizeof(BYTE), 512, inptr); //read next block into buffer

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff) //first 3 bytes follow JPEG header
        {
            if ((buffer[3] & 0xf0) == 0xe0) //first 4 bits (4th byte) match standard, set remaining bits to 0
            {
                break; //valid header found
            }
        }
    }
    while (1);


    char *filename = malloc(7 * sizeof(char)); //filename string
    char *fname_ptr = filename; //pointer -> beginning of filename

    BYTE *bp1, *bp2, *bp3, *bp4; //pointer -> 1st byte, 2nd byte, etc.. in header block - IN BUFFER

    BYTE *tmp_buffer = malloc(512 * sizeof(BYTE)); //tmp buffer stores header block only
    BYTE *tmp_bp = tmp_buffer; //pointer -> start of tmp buffer

    int x = 1; //number of '512' B blocks read (account for first block)
    int j = 0; //jpeg counter


    //read and write JPEGs
    while (1)
    {
        x++; //update block count
        long new_size = x * (512 * sizeof(BYTE)); //calculate new buffer size
        buffer = realloc(tmp1, new_size); //resize buffer
        tmp1 = buffer; //reassign tmp to beginning of buffer
        buffer = buffer + (512 * (x - 1)); //move pointer to start of working block

        bp1 = buffer;
        bp2 = bp1 + 1;
        bp3 = bp2 + 1;
        bp4 = bp3 + 1;

        int n = fread(buffer, sizeof(BYTE), 512, inptr); //return value

        if (n < 512) //fread returns a value less than count
        {
            //EOF is met
            filename = fname_ptr; //reset pointer
            sprintf(filename, "%03i.jpg", j); //create file name
            FILE *outptr = fopen(filename, "w"); //make image file

            int num_byte = (512 * (x - 1)) + n; //calculate total number of bytes in file - count previous blocks read (x - 1)
            //..and n, number of bytes read until EOF

            buffer = tmp1; //reset pointer
            fwrite(buffer, sizeof(BYTE), num_byte, outptr); //write to file
            fclose(outptr); //close file

            break;
        }

        if (*bp1 == 0xff &&  *bp2 == 0xd8 && *bp3 == 0xff) //reached header block
        {
            if ((*bp4 & 0xf0) == 0xe0)
            {
                filename = fname_ptr; //reset pointer
                sprintf(filename, "%03i.jpg", j); //create file name
                FILE *outptr = fopen(filename, "w"); //make image file

                BYTE *hptr = bp1; //pointer -> first byte in header block
                tmp_buffer = tmp_bp; //reset pointer

                //copy header block into tmp buffer
                for (int i = 0; i < 512; i++)
                {
                    *tmp_buffer = *hptr; //copy value

                    hptr = hptr + 1;
                    tmp_buffer = tmp_buffer + 1;
                }

                int num_byte = 512 * (x - 1); //calculate total number of bytes in file
                buffer = tmp1; //reset pointer

                fwrite(buffer, sizeof(BYTE), num_byte, outptr); //write to file
                fclose(outptr); //close file

                free(buffer);

                buffer = malloc(512 * sizeof(BYTE)); //allocate memory for new file
                tmp1 = buffer; //reassign tmp to beginning of buffer

                tmp_buffer = tmp_bp; //reset pointer

                //copy tmp buffer into buffer
                for (int i = 0; i < 512; i++)
                {
                    *buffer = *tmp_buffer; //copy value

                    buffer = buffer + 1;
                    tmp_buffer = tmp_buffer + 1;
                }

                x = 1; //reinitialize block counter
                j++; //update JPEG counter
            }
        }
    }

    fclose(inptr);
    free(tmp1); //free buffer
    free(tmp_bp); //free tmp buffer
    free(fname_ptr); //free filename
}