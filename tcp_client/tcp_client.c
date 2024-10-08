#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 		5000         		// The port which is communicate with server
#define LENGTH 	256          		// Buffer length

typedef struct  {
    unsigned short usSerialNum;
    unsigned short usRes;
    unsigned short usLength;
    unsigned char  unit_id;
}Modbus_TCP;
Modbus_TCP stModbus_TCPHead;

int main(int argc, char *argv[])
{
    	int sockfd;                        	// Socket file descriptor
    	int num;                    		// Counter of received bytes  
    	char revbuf[LENGTH];       		// Receive buffer
		unsigned char sendbuf[LENGTH];       		// Receive buffer
		stModbus_TCPHead.usSerialNum = 0;
		stModbus_TCPHead.usRes = 0;
		stModbus_TCPHead.usLength = 10;
		stModbus_TCPHead.unit_id = 1;
		
		sendbuf[7] = 0x03;
		sendbuf[8] = 3;
		sendbuf[9] = 0;
		sendbuf[10] = 12;
		sendbuf[11] = 3;
		memcpy(&sendbuf, (unsigned char*)&stModbus_TCPHead,7);
    	
		
		struct sockaddr_in remote_addr;    	// Host address information

    	/* Check parameters number */
    	if (argc != 2)                     
    	{   argv[1] = "192.168.1.136";
        	printf ("Using: default HOST IP (192.168.x.136).\n");
    	}

    	/* Get the Socket file descriptor */
    	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    	{
        	printf("ERROR: Failed to obtain Socket Descriptor!\n");
        	return (0);
    	}
    
    	/* Fill the socket address struct */
    	remote_addr.sin_family = AF_INET;              	// Protocol Family
    	remote_addr.sin_port = htons(PORT);           		// Port number
    	inet_pton(AF_INET, argv[1], &remote_addr.sin_addr); 	// Net Address
    	memset (remote_addr.sin_zero,0,8);                 	// Flush the rest of struct

    	/* Try to connect the remote */
    	if (connect(sockfd, (struct sockaddr *)&remote_addr,  sizeof(struct sockaddr)) == -1) 
    	{
			argv[1] = "192.168.2.136";
			if(connect(sockfd, (struct sockaddr *)&remote_addr,  sizeof(struct sockaddr)) == -1)
			{
              printf ("ERROR: Failed to connect to the host!\n");
        	  return (0);
			}
        	
    	} else {
        	printf ("OK: Have connected to the %s\n",argv[1]);
    	}

    	/* Try to connect the server */
    	while (strcmp(revbuf,"exit") != 0)     // Check remoter command
    	{      
        	memset (revbuf,0,LENGTH);
        	num = recv(sockfd, revbuf, LENGTH, 0);

        	switch(num)
        	{
            	case -1:
        			printf("ERROR: Receive string error!\n");
                	close(sockfd);
                	return (0);
                
            	case  0:
                	break;
              
            	default:
                	printf ("OK: Receviced numbytes = %d\n", num);
					stModbus_TCPHead.usSerialNum++;
					memcpy(&sendbuf, (unsigned char*)&stModbus_TCPHead,7);
					send(sockfd, sendbuf, 12, 0);
                	break;
        	}
            revbuf[num] = '\0';
        	printf ("OK: Receviced string is: %s\n", revbuf);
        	
    	}

    	close (sockfd);
    	return (0);
}

