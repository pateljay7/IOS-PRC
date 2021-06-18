#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<dirent.h>
#include<string.h>

char path[]="";
char *p;
void cpy_dir(char *basePath,const int root);
void copy(int old_file,int new_file);

int main(int argc,char*argv[])
{
    if(strcmp(argv[3],"1")==0)
    {
        int old_file,new_file;
        int ac1=access(argv[1],F_OK);
        new_file=creat(argv[2],0666);
        int ac2=access(argv[2],F_OK);

        if(ac1==-1)
        {
            printf("\n\tyou can't access this F1.txt\n");
        }
        else
            printf("\n\tyou can access %s\n",argv[1]);

        if(ac2==-1)
        {
            printf("you can't access this\n");
        }
        else
            printf("\tyou can access %s\n\n",argv[2]);

        old_file=open(argv[1],O_RDONLY);
        if(old_file==-1)
        {
            printf("\nError in file opening\n");
            exit(1);
        }
        new_file=creat(argv[2],0666);
        if(new_file==-1)
        {
            printf("can't open the file\n");
        }

        copy(old_file,new_file);
        exit(0);
    }


    if(strcmp(argv[3],"3")==0)
    {
        int s_file,d_file,c;
        DIR *dest;
        char pathfile[260];
        sprintf(pathfile,"%s/%s",argv[2],argv[1]);
        int ac1=access(argv[1],F_OK);
        dest=opendir(argv[2]);
        if(!dest)
        {
            c=mkdir(argv[2],0777);
            printf("\n\tNew dir created\n");
        }

        d_file=open(pathfile,O_RDWR|O_APPEND|O_CREAT);
        printf("\tPath : %s\n",pathfile);

        int ac2=access(pathfile,F_OK);

        if(ac1==-1)
        {
            printf("you can't access this argv[1]\n");
        }
        else
            printf("\tyou can access %s\n",argv[1]);
        if(ac2==-1)
        {
            printf("you can't access %s \n",pathfile);
        }
        else
            printf("\tyou can access fless %s\n",pathfile);

        s_file=open(argv[1],O_RDONLY);
        if(s_file==-1)
        {
            printf("Error in opening %s\n",argv[1]);
            exit(1);
        }
        if(d_file==-1)
        {
            printf("Error in opening %s\n",argv[2]);
        }

        copy(s_file,d_file);
        exit(0);
    }

    if(strcmp(argv[3],"2")==0)
    {
        p=argv[2];
        copy_dir(argv[1],0);
    }

}

void copy_dir(char *basePath, const int root)
{
    int i,d_dir;
    char path[1000],d_path[1000],s_path[1000];
    struct dirent *dp;
    DIR *dir3 = opendir(basePath);
    sprintf(d_path,"%s/%s",p,basePath);
    int c=mkdir(d_path,0777);
    d_dir=open(d_path,O_RDWR|O_APPEND|O_CREAT);
    if (!dir3)
        return;

    while ((dp = readdir(dir3)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            if(dp->d_type!=DT_DIR)
            {
                sprintf(s_path,"%s/%s",basePath,dp->d_name);
                int s_file=open(s_path,O_RDONLY);
                sprintf(d_path,"%s/%s/%s",p,basePath,dp->d_name);
                int d_file=creat(d_path,0666);

                int ac2=access(d_path,F_OK);
                int ac1=access(basePath,F_OK);

                /*if(ac1==-1){
                	printf("you can't access this S_FILE");}
                else
                	printf("\tyou can access S_FILE\n");
                if(ac2==-1){
                	printf("you can't access D_FILE \n");}
                else
                	printf("\tyou can access fless D_FILE\n");*/

                //--------------------------------------------------

                if(s_file==-1)
                    printf("\tError in s_file\n");
                if(d_file==-1)
                    printf("\tError in d_file\n");

                copy(s_file,d_file);
            }

            if(dp->d_type==DT_DIR)
            {
                strcpy(path, basePath);
                strcat(path, "/");
                strcat(path, dp->d_name);
                copy_dir(path,root + 2);
            }
        }
    }

    closedir(dir3);
}
void copy(int op,int cl)
{
    char buffer[4096];
    int count;
    while((count=read(op,buffer,sizeof(buffer)))>0)
    {
        write(cl,buffer,count);
    }
}
