#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<unistd.h>
#include<limits.h>
#include<string.h>

int main(int argc,char* argv[])
{
	struct dirent *dp,*dp2;
	DIR *dir,*dir2;
	char cwd[PATH_MAX];
	if(getcwd(cwd,sizeof(cwd))!=NULL)
	{
		printf("Current working directory : %s",cwd);
	}

	if(strcmp(argv[1],"a")==0)
	{

		dir=opendir(cwd);
		if(dir==NULL)
		{
			printf("Invalid directory..\n");
			exit(1);
		}
		else
		{
			printf("\nls -a command:\n");
			while((dp=readdir(dir))!=NULL)
				printf("\t%s\n",dp->d_name);
		}
		closedir(dir);
	}
	else if(strcmp(argv[1],"A")==0)
	{
	 	dir2=opendir(cwd);
		if(dir2==NULL)
		{
		printf("Invalid directory..\n");
		exit(1);
		}
		else
		{
			printf("ls -A command:\n");
			while((dp=readdir(dir2))!=NULL)
			{
	if((strcmp(dp->d_name,"..")!=0)&&(strcmp(dp->d_name,".")!=0))
				printf("\t%s\n",dp->d_name);
			}
		}
       		closedir(dir2);
	}

	else if(strcmp(argv[1],"R")==0)
	{
		 tree(cwd, 0);
	}
	return 0;
}

void tree(char *basePath, const int root)
{
    int i;
    char path[1000];
    struct dirent *dp;
    DIR *dir3 = opendir(basePath);

    if (!dir3)
        return;

    while ((dp = readdir(dir3)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            for (i=0; i<root; i++)
            {
                if (i%2 == 0 || i == 0){
                    //printf("%c", 179);
                printf("\t");}
                else
                    printf(" ");

            }

            //printf("%c%c%s\n", 195, 196, dp->d_name);
            printf("\t%s\n", dp->d_name);

            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);
            tree(path, root + 2);
        }
    }

    closedir(dir3);
}

