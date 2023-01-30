#include <stdio.h>
#include <stdlib.h>
#include "include/main.h"
#include "include/pylists.h"
/*declarations*/
void strip_non_num(char * string);

/*other*/
int fis_in_str(char *str1, char * str2)
{
	int match=0;
	int temp=0;
	int j=0;
	for(int i=0; str1[i]!='\0'; i++)
	{
		if(str1[i] == str2[j])
		{	
			match =1;
			temp=i;
			while(str2[j]!='\0')
			{
				if(str1[temp]!=str2[j])
				{
					match =0;
					break;
				}
				temp +=1;
				j+=1;
			}
		if(match==1)
			return 1;
		j=0;
		}
	
	}
	return 0;
}


/*formating*/
void remove_nl(char * str)
{
	
	int len = strlen(str);
	if(str[len -1] == '\n')
		str[len -1] ='\0';
	else
		return;
}


void strip_non_num(char * string)
{
	int i,j, len;	
	int t = 0;	
	len = strlen(string);
	for(i=0; i<len; i++)
	{
		if(t==1)
		{
			i-=1;
			t=0;
		}
		if(string[i] <= 47 || string[i] >= 58)
		{
			for(j=i; j< len-1; j++)
			{
				string[j] = string[j+1];
			}
			len--;
			string[len] = '\0';
			i = 0;
			t = 1;
		}
	}	
}


int str_to_int(char * str)
{
	char buf[400];
	strcpy(buf,str);
	strip_non_num(buf);	
	int len = strlen(buf) -1;
	int temp,off;
	int num=0;
	unsigned int i;
	for(i=0; buf[i] !='\0'; i++)
	{
		off= len - i; 
		temp = buf[i];	
		if(temp < 48 ||temp > 57)
			continue;
		else
		{
			temp -= 48;
			for(int j =0; j<off; j++)
			temp = temp * 10;
			num += temp; 
		}	
	}		
	return num;
}

void convert_list(pylist * list)
{
	unsigned int i=0;
	for(i=0; i < list->count; i++)
	list->items[i].intiger =str_to_int(list->items[i].string);
}



/*sorting functions*/
void sort_list_num(pylist * list)
{
	pyobject last;
	int i;
	int done = 1;
	while(done == 1)
	{
		done = 0;
		last = list->items[0];
		for(i=0; i < list->count; i++)
		{
			if(list->items[i].intiger < last.intiger)
			{
				done = 1;
				list->items[i-1] = list->items[i];
				list->items[i] = last;
			}	
			last = list->items[i];	
		}
	}
}


void sort_list_alpha(pylist * list)
{
	pyobject last;
	int done=1,i,j=0;
	while(done==1)
	{
		last = list->items[0];
		done =0;
		for(i=0; i < list->count; i++)	
		{
			if(list->items[i].string[j] < last.string[j])
			{
				done = 1;
				list->items[i-1] = list->items[i];
				list->items[i] = last;
			}	
			else if(list->items[i].string[j] == last.string[j])
			{
				while(list->items[i].string[j] == last.string[j] && list->items[i].string[j] !='\0' && last.string[j] !='\0')
				{
					j++;
				}
				if(list->items[i].string[j] < last.string[j])
				{
					done = 1;
					list->items[i-1] = list->items[i];
					list->items[i] = last;
				}	
				j=0;
			}	
			last = list->items[i];	
		}	
	}
}






/*input*/
void read_stdin(pylist * list)
{
	char c;	
	int i=0;
	char buf[400];
	while((c=fgetc(stdin))!=EOF)
	{
		if(c=='\n')
		{
			buf[i]='\0';
			list_append_str(list,buf);
			i=0;
		}
		else
		{
			buf[i]=c;
			i++;
		}
	}
}




int main(int argc, char *argv[])
{
	pylist * list=NULL;	
	list = init_list();		
	
	if(argc > 1)
	{
		if(fis_in_str(argv[1], "-n"))
		{	
			read_stdin(list);
			convert_list(list);
			sort_list_num(list);
			print_pylist_clean(list);
		}	
		else if(fis_in_str(argv[1], "-help"))
		{	
			printf("options:\n-help: help\n-n: numarical sort\n");
		}
	}
	else
	{
		read_stdin(list);
		sort_list_alpha(list);
		print_pylist_clean(list);
	}	

	end_pylist(list);	
	return 0;
}
