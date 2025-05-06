#include<stdio.h>
#include<string.h>
#include<time.h>
char yes_or_no();
int main()
{
    FILE* fp;
    char *AlreadyOK[10];
    char *NotOK[10];
    char *NextDay[10];
    char buffer[100];
    char ans,ans2;
    int i=0,j=0,k=0,l=0,start=0;
    fp = fopen("workingtest.txt","r");
    if(fp==NULL)
    {
        printf("failed to open");
        return 1;
    }
    else
    {
        printf("open successfully\n");
        while(fgets(buffer,100,fp)!=NULL)
        {
            buffer[strcspn(buffer, "\n")] = '\0';
            if(strcmp(buffer,"3.nextday")==0)
            {
                start=1;
                break;
            }
        }
    }
    if(start==1)
    {
        while(fgets(buffer,100,fp)!=NULL)
        {
            printf("Did you finished %s?(y/n)\n",buffer);
            ans=yes_or_no();
            if (ans=='y')
            {
                AlreadyOK[i]=strdup(buffer);
                i++;
            }
            else
            {
                NotOK[j]=strdup(buffer);
                printf("add to nest day?(y/n)\n");
                ans2=yes_or_no();
                if (ans2=='y')
                {
                    NextDay[l]=NotOK[j];
                    l++;
                }
                j++;
            }                   
        }
    }
    fclose(fp);
    fp = fopen("workingtest.txt","w");
    time_t t = time(NULL);           // 取得目前時間（秒數）
    struct tm *now = localtime(&t);
    int date = (now->tm_year + 1900) * 10000 +
               (now->tm_mon + 1) * 100 +
               now->tm_mday;
    fprintf(fp,"%d\n",date);
    fprintf(fp,"main:\n");
    fclose(fp);
    return 0;
}
char yes_or_no()                    //判斷輸入y or n
{
    char ans;
    scanf(" %1c",&ans);
    while(ans!='y'&& ans!='n')
    {
        printf("please answer y or n :\n");
        scanf(" %1c",&ans);
    }
    return ans;
}