#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include <time.h>
#include <stdlib.h>

#define MAXBUF 1024

void generate_str(char *str);

int main()
{
	int maxfd, ret;
	char str[MAXBUF], input[MAXBUF];
	fd_set rset;
	struct timeval tv;

	srand(time(0));
	system("clear");
	printf("**********随机码练习游戏**********\n");
	while(1) {
		generate_str(str);
		printf("%s: ", str);
		fflush(stdout);  //note!

		FD_ZERO(&rset);
		FD_SET(fileno(stdin), &rset);
		maxfd = fileno(stdin);
		tv.tv_sec = 3;
		tv.tv_usec = 0;
		ret = select(maxfd + 1, &rset, NULL, NULL, &tv);

		if(ret == -1) {
			perror("select 出错");
			exit(-1);
		}
		else if(ret == 0) {
			printf("\t\t时间到\n");
			bzero(input, MAXBUF);  //note!
			continue;
		}
		else {
			if(FD_ISSET(fileno(stdin), &rset)) {
				fgets(input, MAXBUF, stdin);
				if((input[0] == 'q' || input[0] == 'Q') && 
						input[1] == '\n') {
					printf("谢谢使用，再见!\n");
					exit(0);
				}
				if(strncasecmp(str, input, strlen(str))) {
					printf("\t\t输入错误\n");
				}
				continue;
			}
		}
	}

	return 0;
}

void generate_str(char *str)
{
	int i, j, k;
	for(i = 0; i < 4; i++) {
		j = rand() % 2;
		if(j == 0)
			str[i] = rand() % 10 + '0';
		if(j == 1) {
			k = rand() % 2;
			if(k == 0)
				str[i] = rand() % 26 + 'a';
			if(k == 1)
				str[i] = rand() % 26 + 'A';
		}
	}
}
