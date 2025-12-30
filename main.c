#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_RECORDS 100

void addRecord();
void showRecords();
void showTotal();

int main() {
    int choice;
    while (1) {
        printf("\n=== 記帳系統（C） ===\n");
        printf("1. 新增記帳\n");
        printf("2. 查看記帳\n");
        printf("3. 查看總金額\n");
        printf("4. 離開\n");
        printf("選擇：");
        scanf("%d", &choice);

        if (choice == 1) addRecord();
        else if (choice == 2) showRecords();
        else if (choice == 3) showTotal();
        else if (choice == 4) exit(0);
        else printf("無效輸入\n");
    }
}

// 記帳資料結構
struct Record {
    char date[20];
    char category[20];
    float amount;
    char note[50];
};

// 全域資料（只存在程式執行期間）
struct Record records[MAX_RECORDS];
int recordCount = 0;

// 顯示總金額
void showTotal() {
    if (recordCount == 0) {
        printf("目前沒有記帳資料，無法計算總金額\n");
        return;
    }

    float total = 0.0;
    for (int i = 0; i < recordCount; i++) {
        total += records[i].amount;
    }

    printf("目前總金額為：%.2f\n", total);
}