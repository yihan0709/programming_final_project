#ifndef ACCOUNTING_H
#define ACCOUNTING_H

#define MAX_RECORDS 100

// 記帳資料結構
struct Record {
    char date[20];
    char category[20];
    float amount;
    char note[50];
};

// 全域資料（宣告，不是定義）
extern struct Record records[MAX_RECORDS];
extern int recordCount;

// 功能宣告
void showTotal(void);
void showAverage(void);
void showStdDev(void);
void editRecord(void);
void showMaxCategory(void);
void showReport(void);
void showMaxDay(void);

#endif
