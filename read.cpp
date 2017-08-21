#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>


#define P_FIFO "/tmp/p_fifo"

int main()
{
	char cache[100];
	int fd;
	memset(cache, 0, sizeof(cache));

	if (access(P_FIFO,F_OK)==0)//�ܵ��ļ�����
	{
		//execlp("rm","-f",P_FIFO,NULL);//ɾ��
		/*char* tmp = "rm -f ";
		strcat(tmp,"/tmp/p_fifo");
		system(tmp);*/
		remove(P_FIFO);
		perror(NULL);
		printf("access.\n");
	}

	//���mkfifo�ĵ�һ��������һ���Ѿ����ڵ�·����ʱ���᷵��EEXIST����
	if (mkfifo(P_FIFO,0777)<0)//�����ܵ���mkfifo����
	{
		perror(NULL);
		printf("createnamed pipe failed.\n");
	}
	fd = open(P_FIFO,O_RDONLY|O_NONBLOCK);//�������ķ�ʽ�򿪣�ֻ��
	while (1)
	{
		memset(cache, 0, sizeof(cache));
		if (read(fd,cache,100)==0)
		{
			printf("nodata:\n");
		}
		else
		{
			printf("getdata:%s\n", cache);
		}
		sleep(1);
	}
	close(fd);
	return 0;
}