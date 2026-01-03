#include <stdio.h>
#include <stdlib.h>
#include "accounting.h"

void addRecord();
void showRecords();
void deleteLastRecord();
void totalByCategory();
void searchByDate();
void searchByAmountRange();
void topNRecords();

int main(void) {
    int choice;

    while (1) {
        printf("\n=== 記帳系統 ===\n");
        printf("1. 新增記帳\n");
        printf("2. 查看記帳\n");
        printf("3. 查看總金額\n");
        printf("4. 查看平均金額\n");
        printf("5. 查看消費波動(標準差)\n");
        printf("6. 編輯記帳\n");
        printf("7. 刪除最後一筆\n");
        printf("8. 類別總金額\n");
        printf("9. 搜尋特定日期\n");
        printf("10. 搜尋金額範圍\n");
        printf("11. 顯示前 N 筆最大消費\n");
        printf("12. 顯示花費最多的類別\n");
        printf("13. 簡易消費報表\n");
        printf("14. 單日最高消費日\n");
        printf("15. 離開\n");
        printf("選擇：");
        scanf("%d", &choice);

         if (choice == 1) addRecord();
        else if (choice == 2) showRecords();
        else if (choice == 3) showTotal();
        else if (choice == 4) showAverage();
        else if (choice == 5) showStdDev();
        else if (choice == 6) editRecord();
        else if (choice == 7) deleteLastRecord();
        else if (choice == 8) totalByCategory();
        else if (choice == 9) searchByDate();
        else if (choice == 10) searchByAmountRange();
        else if (choice == 11) topNRecords();
        else if (choice == 12) showMaxCategory();
        else if (choice == 13) showSimpleReport();
        else if (choice == 14) showMaxSpendingDay();
        else if (choice == 15) exit(0);
        else printf("無效輸入\n");
    }
}
