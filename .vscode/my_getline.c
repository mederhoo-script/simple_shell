#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>

#define BUFFER_SIZE 1024

/* Custom getline function that reads characters into a buffer and minimizes the calls to the read system call */
ssize_t custom_getline(char **lineptr, size_t *n, int stream);

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t chars_read;

    while ((chars_read = custom_getline(&line, &len, STDIN_FILENO)) != -1)
    {
        if (chars_read > 0)
        {
            write(STDOUT_FILENO, "You entered: ", 13);
            write(STDOUT_FILENO, line, chars_read);
            write(STDOUT_FILENO, "\n", 1);
        }
    }

    free(line);
    return 0;
}

/* Custom getline function implementation */
ssize_t custom_getline(char **lineptr, size_t *n, int stream)
{
    static char buffer[BUFFER_SIZE];
    static size_t pos = 0;
    static size_t len = 0;
    ssize_t num_read = 0;
    ssize_t total_read = 0;

    char *new_lineptr = NULL;
    size_t new_size = 0;

    if (*n == 0 || *lineptr == NULL)
    {
        new_size = BUFFER_SIZE;
        new_lineptr = (char *)malloc(new_size);
        if (new_lineptr == NULL)
        {
            return -1; /* Memory allocation error */
        }
        *lineptr = new_lineptr;
        *n = new_size;
    }

    while (1)
    {
        if (pos >= len)
        {
            num_read = read(stream, buffer, BUFFER_SIZE);
            if (num_read == 0)
            {
                if (total_read == 0)
                {
                    return 0; /* End of file */
                }
                else
                {
                    break; /* End of line */
                }
            }
            if (num_read < 0)
            {
                return -1; /* Read error */
            }
            pos = 0;
            len = num_read;
        }

        if (buffer[pos] == '\n')
        {
            (*lineptr)[total_read] = '\0';
            pos++;
            total_read++;
            break;
        }
        (*lineptr)[total_read] = buffer[pos];
        pos++;
        total_read++;

        if (total_read >= *n - 1)
        {
            new_size = *n * 2;
            new_lineptr = (char *)realloc(*lineptr, new_size);
            if (new_lineptr == NULL)
            {
                return -1; /* Memory allocation error */
            }
            *lineptr = new_lineptr;
            *n = new_size;
        }
    }

    return (total_read);
}
