#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "accounting.h"

// 全域資料（真正定義一次）
struct Record records[MAX_RECORDS];
int recordCount = 0;

// 顯示總金額
void showTotal(void) {
    if (recordCount == 0) {
        printf("目前沒有記帳資料，無法計算總金額\n");
        return;
    }

    float total = 0.0f;
    for (int i = 0; i < recordCount; i++) {
        total += records[i].amount;
    }

    printf("目前總金額為：%.2f\n", total);
}

// 顯示平均金額
void showAverage(void) {
    if (recordCount == 0) {
        printf("目前沒有記帳資料，無法計算平均金額\n");
        return;
    }

    double sum = 0.0;
    for (int i = 0; i < recordCount; i++) {
        sum += records[i].amount;
    }

    double avg = sum / recordCount;
    avg = round(avg * 100.0) / 100.0;

    printf("平均每筆金額為：%.2f\n", avg);
}

// 顯示消費波動(標準差)
void showStdDev(void) {
    if (recordCount == 0) {
        printf("目前沒有記帳資料，無法計算標準差\n");
        return;
    }
    if (recordCount == 1) {
        printf("只有 1 筆資料，標準差為 0.00（無法形成波動）\n");
        return;
    }

    double sum = 0.0;
    for (int i = 0; i < recordCount; i++) {
        sum += records[i].amount;
    }
    double avg = sum / recordCount;

    double varianceSum = 0.0;
    for (int i = 0; i < recordCount; i++) {
        double diff = records[i].amount - avg;
        varianceSum += diff * diff;
    }

    double variance = varianceSum / recordCount; // 母體變異數
    double stddev = sqrt(variance);

    stddev = round(stddev * 100.0) / 100.0;

    printf("消費波動（標準差）：%.2f\n", stddev);
    printf("（數值越大代表每筆金額差異越大，花費越不穩定）\n");
}

//編輯既有記帳：修改日期 / 類別 / 金額 / 備註
void editRecord(void) {
    if (recordCount == 0) {
        printf("目前沒有記帳資料，無法編輯\n");
        return;
    }

    printf("\n--- 目前記帳列表 ---\n");
    for (int i = 0; i < recordCount; i++) {
        printf("[%d] %s | %s | %.2f | %s\n",
               i, records[i].date, records[i].category, records[i].amount, records[i].note);
    }

    int idx;
    printf("輸入要編輯的編號：");
    if (scanf("%d", &idx) != 1 || idx < 0 || idx >= recordCount) {
        printf("編號無效\n");
        // 清掉錯誤輸入
        while (getchar() != '\n');
        return;
    }

    int choice;
    printf("\n要修改哪一項？\n");
    printf("1. 日期\n");
    printf("2. 類別\n");
    printf("3. 金額\n");
    printf("4. 備註\n");
    printf("選擇：");
    if (scanf("%d", &choice) != 1) {
        while (getchar() != '\n');
        printf("輸入無效\n");
        return;
    }

    if (choice == 1) {
        printf("新日期 (YYYY-MM-DD)：");
        scanf("%19s", records[idx].date);
    } else if (choice == 2) {
        printf("新類別：");
        scanf("%19s", records[idx].category);
    } else if (choice == 3) {
        printf("新金額：");
        scanf("%f", &records[idx].amount);
    } else if (choice == 4) {
        printf("新備註：");
        scanf("%49s", records[idx].note); // 若你原本 note 不支援空白，這樣就一致
    } else {
        printf("選項無效\n");
        return;
    }

    printf("編輯完成：[%d] %s | %s | %.2f | %s\n",
           idx, records[idx].date, records[idx].category, records[idx].amount, records[idx].note);
}

//統計花費金額最大的領域（類別加總後找最大）
void showMaxCategory(void) {
    if (recordCount == 0) {
        printf("目前沒有記帳資料，無法統計\n");
        return;
    }

    char cats[MAX_RECORDS][20];
    float sums[MAX_RECORDS];
    int catCount = 0;

    for (int i = 0; i < recordCount; i++) {
        int found = -1;
        for (int j = 0; j < catCount; j++) {
            if (strcmp(cats[j], records[i].category) == 0) {
                found = j;
                break;
            }
        }

        if (found == -1) {
            strcpy(cats[catCount], records[i].category);
            sums[catCount] = records[i].amount;
            catCount++;
        } else {
            sums[found] += records[i].amount;
        }
    }

    int maxIdx = 0;
    for (int i = 1; i < catCount; i++) {
        if (sums[i] > sums[maxIdx]) maxIdx = i;
    }

    printf("花費最多的領域是：%s（總計 %.2f）\n", cats[maxIdx], sums[maxIdx]);
}

//產生簡易消費報表
void showSimpleReport(void) {
    if (recordCount == 0) {
        printf("目前沒有記帳資料，無法產生報表\n");
        return;
    }

    float total = 0.0f;
    int maxIdx = 0;

    for (int i = 0; i < recordCount; i++) {
        total += records[i].amount;
        if (records[i].amount > records[maxIdx].amount) maxIdx = i;
    }

    double avg = total / recordCount;
    avg = round(avg * 100.0) / 100.0;

    printf("\n=== 簡易消費報表 ===\n");
    printf("總筆數：%d\n", recordCount);
    printf("總金額：%.2f\n", total);
    printf("平均：%.2f\n", avg);
    printf("最大消費：%s %.2f（%s）\n",
           records[maxIdx].category, records[maxIdx].amount, records[maxIdx].date);
}

//單日最高消費日：哪一天花最多（依 date 加總）
void showMaxSpendingDay(void) {
    if (recordCount == 0) {
        printf("目前沒有記帳資料，無法統計\n");
        return;
    }

    char dates[MAX_RECORDS][20];
    float sums[MAX_RECORDS];
    int dayCount = 0;

    for (int i = 0; i < recordCount; i++) {
        int found = -1;
        for (int j = 0; j < dayCount; j++) {
            if (strcmp(dates[j], records[i].date) == 0) {
                found = j;
                break;
            }
        }

        if (found == -1) {
            strcpy(dates[dayCount], records[i].date);
            sums[dayCount] = records[i].amount;
            dayCount++;
        } else {
            sums[found] += records[i].amount;
        }
    }

    int maxIdx = 0;
    for (int i = 1; i < dayCount; i++) {
        if (sums[i] > sums[maxIdx]) maxIdx = i;
    }

    printf("單日花最多的是：%s（總計 %.2f）\n", dates[maxIdx], sums[maxIdx]);
}

