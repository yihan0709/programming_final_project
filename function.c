#include <stdio.h>
#include <string.h>
#include "accounting.h"

// 新增記帳功能（已有）
void addRecord() {
    if (recordCount >= MAX_RECORDS) {
        printf("記帳已滿\n");
        return;
    }

    printf("輸入日期 (YYYY-MM-DD): ");
    scanf("%s", records[recordCount].date);

    printf("輸入類別: ");
    scanf("%s", records[recordCount].category);

    printf("輸入金額: ");
    scanf("%f", &records[recordCount].amount);

    printf("備註: ");
    scanf("%s", records[recordCount].note);

    recordCount++;
    printf("新增成功！\n");
}

// 顯示記帳資料（已有）
void showRecords() {
    if (recordCount == 0) {
        printf("目前沒有記帳資料\n");
        return;
    }

    printf("\n=== 記帳資料 ===\n");
    for (int i = 0; i < recordCount; i++) {
        printf("%s | %s | %.2f | %s\n",
               records[i].date,
               records[i].category,
               records[i].amount,
               records[i].note);
    }
}

// ===== 新增功能 =====

// 1. 刪除最後一筆記帳
void deleteLastRecord() {
    if (recordCount == 0) {
        printf("沒有資料可以刪除\n");
        return;
    }
    recordCount--;
    printf("已刪除最後一筆記帳資料\n");
}

// 2. 依類別統計總金額
void totalByCategory() {
    if (recordCount == 0) {
        printf("沒有資料可統計\n");
        return;
    }

    char category[20];
    printf("輸入要統計的類別: ");
    scanf("%s", category);

    float total = 0;
    for (int i = 0; i < recordCount; i++) {
        if (strcmp(records[i].category, category) == 0) {
            total += records[i].amount;
        }
    }

    printf("類別 %s 的總金額：%.2f\n", category, total);
}

// 3. 搜尋特定日期的記帳
void searchByDate() {
    if (recordCount == 0) {
        printf("沒有資料可搜尋\n");
        return;
    }

    char date[20];
    printf("輸入要搜尋的日期 (YYYY-MM-DD): ");
    scanf("%s", date);

    int found = 0;
    printf("\n=== %s 的記帳資料 ===\n", date);
    for (int i = 0; i < recordCount; i++) {
        if (strcmp(records[i].date, date) == 0) {
            printf("%s | %s | %.2f | %s\n",
                   records[i].date,
                   records[i].category,
                   records[i].amount,
                   records[i].note);
            found = 1;
        }
    }

    if (!found) {
        printf("查無資料\n");
    }
}
