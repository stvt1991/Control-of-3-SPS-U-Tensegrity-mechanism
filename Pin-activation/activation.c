  
#include "activation.h"

void active_pwm(const char * dev, unsigned int val)
{
	static int fd, len;
	static char buff[64];
	static char file[64];
	sprintf(file,"%s",dev);
	fd = open(file,O_WRONLY);
	len = sprintf(buff,"%d",val);
	write(fd,buff,len);
	close(fd);
}

void set_gpio(const char * dev1, unsigned int val1)
{
	static int fd1, len1;
	static char buff1[64];
	static char file1[64];
	sprintf(file1,"%s",dev1);
	fd1 = open(file1,O_WRONLY);
	len1 = sprintf(buff1,"%d",val1);
	write(fd1,buff1,len1);
	close(fd1);
}

void set_pwm(const char *dev2, const char * reg2)
{
	static int fd2, len2;
	static char buff2[64];
	static char file2[64];
	sprintf(file2,"%s",dev2);
	fd2 = open(file2,O_WRONLY);
	len2 = sprintf(buff2,"%s",reg2);
	write(fd2,buff2,len2);
	close(fd2);
}

void set_activ(const char * dev3, const char * reg3, const char * val3)
{
	static int fd3, len3;
	static char buff3[64];
	static char file3[64];
	sprintf(file3,"%s/%s",dev3,reg3);
	fd3 = open(file3,O_RDWR);
	len3 = sprintf(buff3,"%s",val3);
	write(fd3,buff3,len3);
	close(fd3);
}

void set_eqep(const char *dev4, const char * reg4)
{
	static int fd4, len4;
	static char buff4[64];
	static char file4[64];
	sprintf(file4,"%s",dev4);
	fd4 = open(file4,O_WRONLY);
	len4 = sprintf(buff4,"%s",reg4);
	write(fd4,buff4,len4);
	close(fd4);
}

char *get_info1(const char * file_name)
{
	static char val5[64];
	FILE* fp5;
	fp5 = fopen(file_name, "r");
	fscanf(fp5, "%s", val5);
	fclose (fp5);
	return val5;
}

int get_pwm(const char * dev6, const char * reg6)
{
	int val6;
	FILE* fp6;
	static char file6[64];
	sprintf(file6,"%s/%s",dev6,reg6);
	fp6 = fopen(file6, "r");
	fscanf(fp6, "%d", &val6);
	fclose (fp6);
	return val6;
}


// int get_info1(const char * dev5)
// {
	// char val5[3];
	// FILE* fp5;
	// static char file5[64];
	// sprintf(file5,"%s",dev5);
	// fp5 = fopen(file5, "r");
	// fscanf(fp5, "%s", val5);
	// fclose (fp5);
	// return val5;
// }
