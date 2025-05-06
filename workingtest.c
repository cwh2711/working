#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TASKS 100

char yes_or_no();
int find_nextday_start(FILE *fp);
void process_tasks(FILE *fp, char *AlreadyOK[], int *i, char *NotOK[], int *j, char *NextDay[], int *l);
void write_results(const char *filename, char *AlreadyOK[], int i, char *NotOK[], int j, char *NextDay[], int l);

int main() {
    FILE *fp = fopen("workingtest.txt", "r");
    if (!fp) {
        perror("Failed to open file");
        return 1;
    }

    char *AlreadyOK[MAX_TASKS];
    char *NotOK[MAX_TASKS];
    char *NextDay[MAX_TASKS];
    int i = 0, j = 0, l = 0;

    if (find_nextday_start(fp)) {
        process_tasks(fp, AlreadyOK, &i, NotOK, &j, NextDay, &l);
    } else {
        printf("No '3.nextday' section found.\n");
    }

    fclose(fp);
    write_results("workingtest.txt", AlreadyOK, i, NotOK, j, NextDay, l);

    return 0;
}

char yes_or_no() {
    char ans;
    // 使用 getchar() 替代 scanf(" %1c")
    while (1) {
        ans = getchar();  // 讀取一個字符
        if (ans == 'y' || ans == 'n') {
            break;  // 如果是 'y' 或 'n'，結束循環
        } else {
            printf("Please answer y or n:\n");
            while (getchar() != '\n');  // 清空緩衝區
        }
    }
    return ans;
}

int find_nextday_start(FILE *fp) {
    char buffer[100];
    while (fgets(buffer, sizeof(buffer), fp)) {
        buffer[strcspn(buffer, "\n")] = '\0';
        if (strcmp(buffer, "3.nextday") == 0) {
            return 1;
        }
    }
    return 0;
}

void process_tasks(FILE *fp, char *AlreadyOK[], int *i, char *NotOK[], int *j, char *NextDay[], int *l) {
    char buffer[100];
    char ans;
    while (fgets(buffer, sizeof(buffer), fp)) {
        buffer[strcspn(buffer, "\n")] = '\0';
        printf("Did you finish: %s? (y/n): ", buffer);
        ans = yes_or_no();

        if (ans == 'y') {
            AlreadyOK[(*i)++] = strdup(buffer);
        } else {
            NotOK[(*j)] = strdup(buffer);
            printf("Add to next day? (y/n): ");
            ans = yes_or_no();
            if (ans == 'y') {
                NextDay[(*l)++] = NotOK[*j];
            }
            (*j)++;
        }
    }
}

void write_results(const char *filename, char *AlreadyOK[], int i, char *NotOK[], int j, char *NextDay[], int l) {
    FILE *fp = fopen(filename, "w");
        // 寫入日期
        time_t t = time(NULL);
        struct tm *now = localtime(&t);
        int date = (now->tm_year + 1900) * 10000 +
                   (now->tm_mon + 1) * 100 +
                   now->tm_mday;
        fprintf(fp, "%d\n", date);
    if (!fp) {
        perror("Failed to write file");
        return;
    }

    fprintf(fp, "1.AlreadyOK\n");
    for (int m = 0; m < i; m++) {
        fprintf(fp, "%s\n", AlreadyOK[m]);
        free(AlreadyOK[m]);
    }

    fprintf(fp, "2.NotOK\n");
    for (int m = 0; m < j; m++) {
        fprintf(fp, "%s\n", NotOK[m]);
        free(NotOK[m]);
    }

    fprintf(fp, "3.nextday\n");
    for (int m = 0; m < l; m++) {
        fprintf(fp, "%s\n", NextDay[m]);
        free(NextDay[m]);
    }



    fclose(fp);
}
