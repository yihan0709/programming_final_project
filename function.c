#include <stdio.h>
#include <string.h>

#define MAX_RECORDS 100

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

// 顯示記帳
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