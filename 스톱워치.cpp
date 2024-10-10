#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <conio.h>

#define MAX_RECORDS 10 // 최대 기록 개수 정의

void time_pass(time_t start);
void display_time(long nhour, long nmin, long nsecond);
void control_watch(void);
void save_record(long nhour, long nmin, long nsecond); // 기록 저장 함수
void display_records(void); // 기록 출력 함수
void reset_records(void); // 기록 초기화 함수

long records[MAX_RECORDS][3]; // 기록을 저장할 배열
int record_count = 0; // 현재 기록 개수

int main(void) {
    display_time(0, 0, 0); // 초기 시간 표시
    getch();
    control_watch(); // 스톱워치 제어 시작
    return 0;
}

void control_watch(void) {
    char key;
    time_t start;
    start = time(NULL);
    time_pass(start); // 시간 경과 표시 시작
    do {
        key = getch(); // 키 입력 대기
        switch (key) {
            case 10: // Enter 키
                time_pass(start); // 현재 경과 시간 표시
                break;
            case 32: // Space 키
                start = time(NULL); // 시간 초기화
                time_pass(start); // 경과 시간 표시
                break;
            case 114: // 'r' 키 - 기록 저장
                if (record_count < MAX_RECORDS) {
                    long nhour, nmin, nsecond;
                    time_pass(start); // 경과 시간 계산
                    nhour = (long)(difftime(time(NULL), start) / 3600); // 시
                    nmin = (long)(fmod(difftime(time(NULL), start), 3600) / 60); // 분
                    nsecond = (long)(fmod(difftime(time(NULL), start), 60)); // 초
                    save_record(nhour, nmin, nsecond); // 기록 저장
                    display_records(); // 저장된 기록 즉시 출력
                } else {
                    printf("기록이 가득 찼습니다. 기록을 초기화하시겠습니까? (y/n): ");
                    char choice = getch(); // 사용자 입력 대기
                    if (choice == 'y' || choice == 'Y') {
                        reset_records(); // 기록 초기화
                        printf("\n기록이 초기화되었습니다.\n");
                    } else {
                        printf("\n기록이 초기화되지 않았습니다.\n");
                    }
                }
                break;
            case 27: // Esc 키
                exit(0); // 종료
                break;
        }
    } while (key != 27);
}

void time_pass(time_t start) {
    double hour, min, second;
    long nhour, nmin, nsecond;
    time_t now;
    while (!kbhit()) { // 키 입력이 없을 때까지 반복
        now = time(NULL);
        second = difftime(now, start);
        nhour = (long)(second / 3600); // 시 계산
        nmin = (long)(fmod(second, 3600) / 60); // 분 계산
        nsecond = (long)(fmod(second, 60)); // 초 계산
        display_time(nhour, nmin, nsecond); // 경과 시간 표시
    }
}

void display_time(long nhour, long nmin, long nsecond) {
    system("cls"); // 화면 지우기
    printf("stopwatch\n\n");
    printf("%.2ld시 %.2ld분 %.2ld초 \n\n", nhour, nmin, nsecond);
    printf("Enter:(시작/정지), SPACE:재시작, 'r':기록 저장, Esc:종료\n");
}

void save_record(long nhour, long nmin, long nsecond) {
    records[record_count][0] = nhour; // 시 저장
    records[record_count][1] = nmin; // 분 저장
    records[record_count][2] = nsecond; // 초 저장
    record_count++; // 기록 개수 증가
    printf("기록이 저장되었습니다: %.2ld시 %.2ld분 %.2ld초\n", nhour, nmin, nsecond); // 저장된 시간 표시
}

void display_records(void) {
    printf("저장된 기록:\n"); // 기록 목록 제목
    for (int i = 0; i < record_count; i++) {
        printf("%d: %.2ld시 %.2ld분 %.2ld초\n", i + 1, records[i][0], records[i][1], records[i][2]); // 저장된 기록 출력
    }
    printf("\n"); // 줄 바꿈
}

void reset_records(void) {
    record_count = 0; // 기록 개수 초기화
    for (int i = 0; i < MAX_RECORDS; i++) {
        records[i][0] = 0;
        records[i][1] = 0;
        records[i][2] = 0;
    }
}

