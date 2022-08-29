/* A simple server in the internet domain using TCP
 *    The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
     if (newsockfd < 0) 
          error("ERROR on accept");
     bzero(buffer,256);
     n = read(newsockfd,buffer,255);
     if (n < 0) error("ERROR reading from socket");
     
     int answer = 0; //This will store the answer of the expression given from the client
     int leftHand; //This will store the leftHand number
     int rightHand; //This will store the right hand number
     char *ptr = strtok(buffer, " "); //This pointer will handle the buffer string manipulation
     
     char *sign = ptr; //This character pointer will store the calculator operation

     int i = 0; //This acts as a temporary index for the left and right hand numbers
     while(ptr != NULL) //This while loop loops until the end of the string is found
     {
	ptr = strtok(NULL, " ");
        if(i == 0)
		leftHand = atoi(ptr); //The first, next string is the left hand number
	if(i == 1)
                rightHand = atoi(ptr); //The last string is the right hand number
	i++;
     }

     //These if/else statements perform the correct operations on the two numbers given
     if(strcmp(sign,"*") == 0)
     	answer = leftHand * rightHand;
     else if(strcmp(sign,"/") == 0)
     	answer = leftHand / rightHand;
     else if(strcmp(sign,"+") == 0)
        answer = leftHand + rightHand;
     else if(strcmp(sign,"-") == 0)
        answer = leftHand - rightHand;
     else if(strcmp(sign,"%") == 0)
        answer = leftHand % rightHand;

     char answerstr[99]; //This will store the string version of the answer
	
     snprintf(answerstr,sizeof(answerstr),"%d",answer); //This converts the integer anser into a string answer

     n = write(newsockfd,answerstr,strlen(answerstr));
     if (n < 0) error("ERROR writing to socket");
     close(newsockfd);
     close(sockfd);
     return 0;
}
