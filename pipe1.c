#include  <stdio.h>
#include <stdlib.h>
#include  <string.h>
#include  <sys/types.h>
#include  <unistd.h>


#define   BUF_SIZE   256

int main(){
	
	 int pfd1[2]; 
	 int pfd2[2];
	 int pfd3[2]; 	 

	pid_t child1,child2,child3;

	int i;
	ssize_t numRead = -1;
	const char* messageOne = "Hello from child ONE.\n";
    	const char* messageTwo = "Hello from child TWO.\n";
	const char* messageThree = "Hello from child THR.\n";

    	const unsigned int commLen = strlen(messageOne) + 1;
	
	char   buf[BUF_SIZE];
	//char   buf2[BUF_SIZE];

	
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

    	printf("Piped opened with success. Forking ...\n");

	//CHILD 1
	
	child1=fork();
	if (child1==-1){
	
	perror("fork");
	exit(1);
	}

	else if (child1==0){

	//sprintf(buf, "\nThis line is from child %d, value = %d\n\n", getpid(),i);
 	 //write(1, buf, strlen(buf));

	printf("\nChild 1 executing id %d...\n",getpid());

	/* close reading end of first pipe */
	   if (close(pfd1[0]) == -1)
            {
                printf("Error closing reading end of pipe 1.\n");
                exit(1);
            }
            /* close writing end of second pipe */
            if (close(pfd2[1]) == -1)
            {
                printf("Error closing writing end of pipe 2.\n");
                exit(1);
            }
	/* write to pipe 1 */
            if (write(pfd1[1], messageOne, commLen) != commLen)
            {
                printf("Error writing to pipe 1.\n");
                exit(1);
            }

            if (close(pfd1[1]) == -1)
            {
                printf("Error closing writing end of pipe 1.\n");
                exit(1);
            }

            /* reading from pipe 2 */
            numRead = read(pfd2[0], buf, commLen);
            if (numRead == -1)
            {
                printf("Error reading from pipe 2.\n");
                exit(1);
            }

            if (close(pfd2[0]) == -1)
            {
                printf("Error closing reading end of pipe 2.\n");
                exit(1);
            }
	    
 	   // write(1, buf, strlen(buf));

            printf("Message received child ONE: %s", buf);
            printf("Exiting child 1...\n");

		exit (0); 
	}
	
	
	child2=fork();
	if (child2==-1){
	
	perror("fork");
	exit(1);
	}



	else if (child2==0){

	//sprintf(buf, "\nThis line is from child %d, value = %d\n\n", getpid(),i);
 	 //write(1, buf, strlen(buf));
	
	printf("\nChild 2 executing id %d...\n",getpid());
            /* close reading end of third pipe */
            if (close(pfd3[0]) == -1)
            {
                printf("Error closing reading end of pipe 3.\n");
                exit(1);
            }
            /* close writing end of first pipe */
            if (close(pfd1[1]) == -1)
            {
                printf("Error closing writing end of pipe 1.\n");
                exit(1);
            }

            /* read from the first pipe */
            if (read(pfd1[0], buf, commLen) == -1)
            {
                printf("Error reading from pipe 1.\n");
                exit(1);
            }

            if (close(pfd1[0]) == -1)
            {
                printf("Error closing reading end of pipe 1.\n");
                exit(1);
            }

            /* write to the third pipe */
            if (write(pfd3[1], messageTwo, commLen) != commLen)
            {
                printf("Error writing to the pipe 3.");
                exit(1);
            }

            if (close(pfd3[1]) == -1)
            {
                printf("Error closing writing end of pipe 3.");
                exit(1);
            }
	    //write(1, buf, strlen(buf));

            printf("Message received child TWO: %s", buf);
            printf("Exiting child 2...\n");
            exit(0);
	    //exit (0); 
	}
	

	child3=fork();
	if (child3==-1){
	
	perror("fork");
	exit(1);
	}



	else if (child3==0){

	//sprintf(buf, "\nThis line is from child %d, value = %d\n\n", getpid(),i);
 	 //write(1, buf, strlen(buf));
	printf("\nChild 3 executing id %d...\n",getpid());
	/* close reading end of second pipe */
	   if (close(pfd2[0]) == -1)
            {
                printf("Error closing reading end of pipe 2.\n");
                exit(1);
            }
            /* close writing end of third pipe */
            if (close(pfd3[1]) == -1)
            {
                printf("Error closing writing end of pipe 3.\n");
                exit(1);
            }
	/* write to pipe 2 */
            if (write(pfd2[1], messageThree, commLen) != commLen)
            {
                printf("Error writing to pipe 2.\n");
                exit(1);
            }

            if (close(pfd2[1]) == -1)
            {
                printf("Error closing writing end of pipe 2.\n");
                exit(1);
            }

            /* reading from pipe 3 */
            numRead = read(pfd3[0], buf, commLen);
            if (numRead == -1)
            {
                printf("Error reading from pipe 3.\n");
                exit(1);
            }

            if (close(pfd3[0]) == -1)
            {
                printf("Error closing reading end of pipe 3.\n");
                exit(1);
            }
	    
 	    //write(1, buf, strlen(buf));

            printf("Message received child THREE: %s", buf);
            printf("Exiting child 3...\n");

		exit (0); 
		//exit (0); 
	}
	
      
      int status;
      (void)waitpid(child1, &status, 0);

      (void)waitpid(child2, &status, 0);
 
      (void)waitpid(child3, &status, 0);

	

return EXIT_SUCCESS;

	
}







