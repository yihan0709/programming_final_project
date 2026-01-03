#include <stdio.h>
#include <string.h>
#include "accounting.h"

// ===== 基本功能 =====

// 新增記帳
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

// 顯示所有記帳
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


// 刪除最後一筆記帳
void deleteLastRecord() {
    if (recordCount == 0) {
        printf("沒有資料可以刪除\n");
        return;
    }
    recordCount--;
    printf("已刪除最後一筆記帳資料\n");
}

// 依類別統計總金額
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

// 搜尋特定日期
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

// 依金額範圍搜尋
void searchByAmountRange() {
    if (recordCount == 0) {
        printf("沒有資料可搜尋\n");
        return;
    }

    float minAmount, maxAmount;
    printf("輸入最小金額: ");
    scanf("%f", &minAmount);
    printf("輸入最大金額: ");
    scanf("%f", &maxAmount);

    int found = 0;
    printf("\n=== 金額介於 %.2f ~ %.2f 的記帳資料 ===\n", minAmount, maxAmount);
    for (int i = 0; i < recordCount; i++) {
        if (records[i].amount >= minAmount && records[i].amount <= maxAmount) {
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

// 顯示前 N 筆最大消費
void topNRecords() {
    if (recordCount == 0) {
        printf("沒有資料可顯示\n");
        return;
    }

    int N;
    printf("輸入要顯示的筆數 N: ");
    scanf("%d", &N);

    if (N > recordCount) N = recordCount;

    struct Record temp[MAX_RECORDS];
    memcpy(temp, records, recordCount * sizeof(struct Record));

    for (int i = 0; i < recordCount - 1; i++) {
        for (int j = 0; j < recordCount - i - 1; j++) {
            if (temp[j].amount < temp[j + 1].amount) {
                struct Record t = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = t;
            }
        }
    }

    printf("\n=== 前 %d 筆最大消費 ===\n", N);
    for (int i = 0; i < N; i++) {
        printf("%s | %s | %.2f | %s\n",
               temp[i].date,
               temp[i].category,
               temp[i].amount,
               temp[i].note);
    }
}
