#include <fcntl.h>
#include <netinet/ip.h>
#include <netinet/ip6.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <netdb.h> 
#include <arpa/inet.h>


int main(){


struct sockaddr_in sin;
struct sockaddr_in din;
int tos_local=IPTOS_DSCP_AF31;
int tos_local1=IPTOS_DSCP_AF23;

const int opt=1;
int sockfd  = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (sockfd< 0) {
	printf("ERROR on sock opening \n");
	return -1;
    }else{
	printf("socfd %d \n",sockfd);
    }

	bzero(&sin, sizeof(sin));
        sin.sin_family = AF_INET;
        sin.sin_addr.s_addr   = inet_addr("192.168.137.236"); 
        sin.sin_port   = htons(0);
        if ((setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int))) < 0) {
          printf("Could not set option SO_REUSEADDR\n");
        }
	if ((setsockopt(sockfd, IPPROTO_IP, IP_TOS, &tos_local, sizeof(tos_local))) < 0) 
	{ 
		printf( "Could not set option IP_TOS\n"); 
	}
        if ((bind(sockfd, (struct sockaddr *)&sin, sizeof(sin))) < 0) {
          printf( "Could not bind IPv4 ");
	  return -1;
        }

int sockfd1  = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockfd1< 0) {
	printf("ERROR on sockfd1 opening \n");
	return -1;
    }else{
	printf("sockfd1 %d \n",sockfd1);
    }
        if ((setsockopt(sockfd1, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int))) < 0) {
          printf("Could not set option SO_REUSEADDR\n");
        }
	if ((setsockopt(sockfd1, IPPROTO_IP, IP_TOS, &tos_local1, sizeof(tos_local))) < 0) 
	{ 
		printf( "Could not set option IP_TOS\n"); 
	}
        if ((bind(sockfd1, (struct sockaddr *)&sin, sizeof(sin))) < 0) {
          printf( "Could not bind IPv4 ");
	  return -1;
        }else{
	  printf("it is ok buddy \n");
	}
      din.sin_family      = AF_INET;
      din.sin_addr.s_addr = inet_addr("8.8.8.8"); 
      din.sin_port        = htons(2152);

	printf("Sending the IPv4 packet\n");
      char packet[4]="123\0";
int counter=0;
while(counter<30){
     if (sendto(sockfd, packet, 4, 0, (struct sockaddr *)&din, sizeof(din)) < 0) {
        printf ("Could not send the packet:");
      }
      printf("Sending the IPv4 packet sockfd1 %d sockfd [%d] \n",sockfd1,sockfd);

      if (sendto(sockfd1, packet, 4, 0, (struct sockaddr *)&din, sizeof(din)) < 0) {
        printf ("Could not send the packet:");
      }
counter++;
sleep(2);
}
	close(sockfd1);
	close(sockfd);
}



