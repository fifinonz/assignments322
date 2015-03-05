#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

/* max  receiving buffer size*/

#define BUF_SIZE 256

int main()
{
/* Create pipe file descriptors*/
    int pfd1[2];
    int pfd2[2];
    int pfd3[3];

    ssize_t numRead = -1; //blocks to read

    const char* messageOne = "Hello I am child 1.\n";
    const char* messageTwo = "Hello I am child 2.\n";
    const char* messageThree="Hello I am child 3.\n";

    /* Working with messageThree as the longest */
    const unsigned int commLen = strlen(messageThree) + 1;

    char buf[BUF_SIZE];
 
/* Call pipe thrice to create the 3 pipes. Using simple error checking*/

    if (pipe(pfd1) == -1)
    {
        printf("Error opening pipe 1!\n");
        exit(1);
    }

    if (pipe(pfd2) == -1)
    {
        printf("Error opening pipe 2!\n");
        exit(1);
    }
 if (pipe(pfd3) == -1)
    {
        printf("Error opening pipe 3!\n");
        exit(1);
    }
    printf("Pipes opened. Forking ...\n");

    /* Define the behaviour of each child process created using fork */

/* Child 1 */
    switch (fork())
    {
        case -1:
            printf("Error forking child 1!\n");
            exit(1);

        case 0:
            printf("\nCreated Child 1 ID: %d\n", getpid());
            /* close reading end of first pipe */
            if (close(pfd1[0]) == -1)
            {
                printf("Error closing reading end of pipe 1.\n");
                _exit(1);
            }
            /* close writing end of second pipe */
            if (close(pfd2[1]) == -1)
            {
                printf("Error closing writing end of pipe 2.\n");
                _exit(1);
            }
	/* close writing end of third pipe */
            if (close(pfd3[1]) == -1)
            {
                printf("Error closing writing end of pipe 3.\n");
                _exit(1);
            }

            /* write to pipe 1 */
            if (write(pfd1[1], messageOne, commLen) != commLen)
            {
                printf("Error writing to pipe 1.\n");
                _exit(1);
            }

            if (close(pfd1[1]) == -1)
            {
                printf("Error closing writing end of pipe 1.\n");
                _exit(1);
            }
  /* reading from pipe 3 */
            numRead = read(pfd3[0], buf, commLen);
            if (numRead == -1)
            {
                printf("Error reading from pipe 3.\n");
                _exit(1);
            }
	    else 
	    {
		 printf("To Child 1:  %s", buf);
	    }

            if (close(pfd3[0]) == -1)
            {
                printf("Error closing reading end of pipe 3.\n");
                _exit(1);
            }
 /* reading from pipe 2 */
            numRead = read(pfd2[0], buf, commLen);
            if (numRead == -1)
            {
                printf("Error reading from pipe 2.\n");
                _exit(1);
            }
	    else 
	    {
		 printf("To Child 1:  %s", buf);
	    }

            if (close(pfd2[0]) == -1)
            {
                printf("Error closing reding end of pipe 2.\n");
                _exit(1);
            }

            
          printf("\nChild 1 ID: %d exiting...\n", getpid());
            _exit(0);

        default:
            break;
    } // end child 1

    /* Child 2 */
    switch (fork())
    {
        case -1:
            printf("Error forking child 2!\n");
            exit(1);
        case 0:
            printf("\nCreated Child 2 ID: %d\n", getpid());
            /* close reading end of second pipe */
            if (close(pfd2[0]) == -1)
            {
                printf("Error closing reading end of pipe 2.\n");
                _exit(1);
            }
            /* close writing end of first pipe */
            if (close(pfd1[1]) == -1)
            {
                printf("Error closing writing end of pipe 1.\n");
                _exit(1);
            }
              /* close writing end of the third pipe */

            if (close(pfd3[1]) == -1)
            {
                printf("Error closing writing end of pipe 3.\n");
                _exit(1);
            }
 /* write to the second pipe */
            if (write(pfd2[1], messageTwo, commLen) != commLen)
            {
                printf("Error writing to the pipe.");
                _exit(EXIT_FAILURE);
            }

            if (close(pfd2[1]) == -1)
            {
                printf("Error closing writing end of pipe 2.");
                _exit(EXIT_FAILURE);
            }
/* read from the third pipe */
            if (read(pfd3[0], buf, commLen) == -1)
            {
                printf("Error reading from pipe 3.\n");
                _exit(EXIT_FAILURE);
            }
           else 
	    {
		 printf("To Child 2:  %s", buf);
	    }
            if (close(pfd3[0]) == -1)
            {
                printf("Error closing reading end of pipe 3.\n");
                _exit(EXIT_FAILURE);
            }
            

/* read from the first pipe */
            if (read(pfd1[0], buf, commLen) == -1)
            {
                printf("Error reading from pipe 1.\n");
                _exit(EXIT_FAILURE);
            }
	    else 
	    {
		 printf("To Child 2:  %s", buf);
	    }
            if (close(pfd1[0]) == -1)
            {
                printf("Error closing reading end of pipe 1.\n");
                _exit(EXIT_FAILURE);
            }
 
            printf("\nChild 2 ID: %d exiting...\n", getpid());
            _exit(EXIT_SUCCESS);

        default:
            break;
    } // end children

     /*child 3 */
    switch (fork())
    {
        case -1:
            printf("Error forking child 3!\n");
            exit(1);
        case 0:
            printf("\nCreated Child 3 ID: %d\n", getpid());
            /* close reading end of third pipe */
            if (close(pfd3[0]) == -1)
            {
                printf("Error closing reading end of pipe 3.\n");
                _exit(1);
            }
            /* close writing end of first pipe */
            if (close(pfd1[1]) == -1)
            {
                printf("Error closing writing end of pipe 1.\n");
                _exit(1);
            }
              /* close writing end of the second pipe */

            if (close(pfd2[1]) == -1)
            {
                printf("Error closing writing end of pipe 2\n");
                _exit(1);
            }
 /* write to the third pipe */
            if (write(pfd3[1], messageThree, commLen) != commLen)
            {
                printf("Error writing to the pipe.");
                _exit(EXIT_FAILURE);
            }

            if (close(pfd3[1]) == -1)
            {
                printf("Error closing writing end of pipe 3.");
                _exit(EXIT_FAILURE);
            }

/* read from the first pipe */
            if (read(pfd1[0], buf, commLen) == -1)
            {
                printf("Error reading from pipe 1.\n");
                _exit(EXIT_FAILURE);
            }
		 else 
	    {
		 printf("To Child 3:  %s", buf);
	    }
            if (close(pfd1[0]) == -1)
            {
                printf("Error closing reading end of pipe 1.\n");
                _exit(EXIT_FAILURE);
            }
           
  /* read from the second pipe */
            if (read(pfd2[0], buf, commLen) == -1)
            {
                printf("Error reading from pipe 2.\n");
                _exit(EXIT_FAILURE);
            }
		 else 
	    {
		 printf("To Child 3:  %s", buf);
	    }
            if (close(pfd2[0]) == -1)
            {
                printf("Error closing reading end of pipe 2.\n");
                _exit(EXIT_FAILURE);
            }

 
           
            printf("\nChild 3 ID: %d exiting...\n", getpid());
            _exit(EXIT_SUCCESS);

        default:
            break;
    } // end child 3

  /* if (close(pfd1[0]) == -1)
    {
        printf("Error closing reading end of the pipe.\n");
        exit(EXIT_FAILURE);
    }

    if (close(pfd2[1]) == -1)
    {
        printf("Error closing writing end of the pipe.\n");
        exit(EXIT_FAILURE);
    }

    if (close(pfd2[0]) == -1)
    {
        printf("Error closing reading end of the pipe.\n");
        exit(EXIT_FAILURE);
    }

    if (close(pfd1[1]) == -1)
    {
        printf("Error closing writing end of the pipe.\n");
        exit(EXIT_FAILURE);
    }
 if (close(pfd3[1]) == -1)
    {
        printf("Error closing writing end of the pipe.\n");
        exit(EXIT_FAILURE);
    }

    if (close(pfd3[0]) == -1)
    {
        printf("Error closing reading end of the pipe.\n");
        exit(EXIT_FAILURE);
    }
*/
   
    if (wait(NULL) == -1)
    {
        printf("Error waiting.\n");
        exit(EXIT_FAILURE);
    }
	
    exit(EXIT_SUCCESS);

} // end main
