#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <unistd.h>  
#include <arpa/inet.h>
#include "inc/Modbus.h"       
                         
#define PORT 		5000       		// The port which is communicate with server
#define BACKLOG 	10

#define LENGTH 512              		// Buffer length                                                                                 
int main ()
{  
	int iR;
	int sockfd;                        // Socket file descriptor
    	int nsockfd;               		// New Socket file descriptor
    	int num;
    	int sin_size;                      	// to store struct size
    	char sdbuf[LENGTH];          	// Send buffer
		uchar revbuf[LENGTH];
    	struct sockaddr_in addr_local; 
    	struct sockaddr_in addr_remote; 
    //	char sendstr[16]= {"123456789 abcde"}; 
	Modbus_Initial();
               
    	/* Get the Socket file descriptor */  
    	if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 )  
    	{   
        	printf ("ERROR: Failed to obtain Socket Despcritor.\n");
        	return (0);
    	} else {
        	printf ("OK: Obtain Socket Despcritor sucessfully.\n");
    	}
    
    	/* Fill the local socket address struct */
    	addr_local.sin_family = AF_INET;           	// Protocol Family
    	addr_local.sin_port = htons (PORT);         	// Port number
    	addr_local.sin_addr.s_addr  = htonl (INADDR_ANY);  // AutoFill local address
    	memset (addr_local.sin_zero,0,8);          		// Flush the rest of struct

    	/*  Blind a special Port */
    	if( bind(sockfd, (struct sockaddr*)&addr_local, sizeof(struct sockaddr)) == -1 )
    	{  
    	  	printf ("ERROR: Failed to bind Port %d.\n",PORT);
        	return (0);
    	} else {
        	printf("OK: Bind the Port %d sucessfully.\n",PORT);
    	}
   
    	/*  Listen remote connect/calling */
    	if(listen(sockfd,BACKLOG) == -1)
    	{
        	printf ("ERROR: Failed to listen Port %d.\n", PORT);
        	return (0);
    	} else {
        	printf ("OK: Listening the Port %d sucessfully.\n", PORT);
    	}
   
    	while(1)
    	{  
        	sin_size = sizeof(struct sockaddr_in);  
        
        	/*  Wait a connection, and obtain a new socket file despriptor for single connection */
        	if ((nsockfd = accept(sockfd, (struct sockaddr *)&addr_remote, (socklen_t *__restrict)&sin_size)) == -1)
        	{  
            	printf ("ERROR: Obtain new Socket Despcritor error.\n");
            	continue;
        	} else {
            	printf ("OK: Server has got connect from %s.\n", inet_ntoa(addr_remote.sin_addr)); 
        	}
			printf("sockfd = %d\n",sockfd);
			printf("nsockfd = %d\n",nsockfd);

        	/* Child process */
        	if(!fork())                    
        	{  
            	printf("You can enter string, and press 'exit' to end the connect.\n");
            	while(strcmp(sdbuf,"exit") != 0)
            	{ 
					iR=(int)scanf("%s", sdbuf);

					if(strcmp(sdbuf,"TCP") == 0)
					{
						TCP_Modbus_Send(3,30000,1,(unsigned char *)&sdbuf);
						printf("sdbuf[0] = %d\n",sdbuf[0]);
						printf("sdbuf[1] = %d\n",sdbuf[1]);
						printf("sdbuf[2] = %d\n",sdbuf[2]);
						printf("sdbuf[3] = %d\n",sdbuf[3]);
						printf("sdbuf[4] = %d\n",sdbuf[4]);
						printf("sdbuf[5] = %d\n",sdbuf[5]);
						printf("sdbuf[6] = %d\n",sdbuf[6]);
						printf("sdbuf[7] = %d\n",sdbuf[7]);
						printf("sdbuf[8] = %d\n",sdbuf[8]);
						printf("sdbuf[9] = %d\n",sdbuf[9]);
					}
					

					if(iR>512) break;
                	if((num = send(nsockfd, sdbuf, strlen(sdbuf), 0)) == -1)
                	{
                    	printf("ERROR: Failed to sent string.\n");
                    	close(nsockfd);
                    	exit(1);
                	}

					if (0 < (recv(nsockfd, revbuf, LENGTH, 0)))
					{
						printf("revbuf[0] = %d\n",revbuf[0]);
						printf("revbuf[1] = %d\n",revbuf[1]);
						printf("revbuf[2] = %d\n",revbuf[2]);
						printf("revbuf[3] = %d\n",revbuf[3]);
						printf("revbuf[4] = %d\n",revbuf[4]);
						printf("revbuf[5] = %d\n",revbuf[5]);
						printf("revbuf[6] = %d\n",revbuf[6]);
						printf("revbuf[7] = %d\n",revbuf[7]);
						printf("revbuf[8] = %d\n",revbuf[8]);
						printf("revbuf[9] = %d\n",revbuf[9]);
						printf("revbuf[10] = %d\n",revbuf[10]);
						printf("revbuf[11] = %d\n",revbuf[11]);
					}

                	printf("OK: Sent %d bytes sucessful, please enter again.\n", num);  
            	}
         	}  
			printf("close\n");
         	close(nsockfd);  
         	while(waitpid(-1, NULL, WNOHANG) > 0);    
     }    
}

