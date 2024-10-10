#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <conio.h>

#define MAX_RECORDS 10 // �ִ� ��� ���� ����

void time_pass(time_t start);
void display_time(long nhour, long nmin, long nsecond);
void control_watch(void);
void save_record(long nhour, long nmin, long nsecond); // ��� ���� �Լ�
void display_records(void); // ��� ��� �Լ�
void reset_records(void); // ��� �ʱ�ȭ �Լ�

long records[MAX_RECORDS][3]; // ����� ������ �迭
int record_count = 0; // ���� ��� ����

int main(void) {
    display_time(0, 0, 0); // �ʱ� �ð� ǥ��
    getch();
    control_watch(); // �����ġ ���� ����
    return 0;
}

void control_watch(void) {
    char key;
    time_t start;
    start = time(NULL);
    time_pass(start); // �ð� ��� ǥ�� ����
    do {
        key = getch(); // Ű �Է� ���
        switch (key) {
            case 10: // Enter Ű
                time_pass(start); // ���� ��� �ð� ǥ��
                break;
            case 32: // Space Ű
                start = time(NULL); // �ð� �ʱ�ȭ
                time_pass(start); // ��� �ð� ǥ��
                break;
            case 114: // 'r' Ű - ��� ����
                if (record_count < MAX_RECORDS) {
                    long nhour, nmin, nsecond;
                    time_pass(start); // ��� �ð� ���
                    nhour = (long)(difftime(time(NULL), start) / 3600); // ��
                    nmin = (long)(fmod(difftime(time(NULL), start), 3600) / 60); // ��
                    nsecond = (long)(fmod(difftime(time(NULL), start), 60)); // ��
                    save_record(nhour, nmin, nsecond); // ��� ����
                    display_records(); // ����� ��� ��� ���
                } else {
                    printf("����� ���� á���ϴ�. ����� �ʱ�ȭ�Ͻðڽ��ϱ�? (y/n): ");
                    char choice = getch(); // ����� �Է� ���
                    if (choice == 'y' || choice == 'Y') {
                        reset_records(); // ��� �ʱ�ȭ
                        printf("\n����� �ʱ�ȭ�Ǿ����ϴ�.\n");
                    } else {
                        printf("\n����� �ʱ�ȭ���� �ʾҽ��ϴ�.\n");
                    }
                }
                break;
            case 27: // Esc Ű
                exit(0); // ����
                break;
        }
    } while (key != 27);
}

void time_pass(time_t start) {
    double hour, min, second;
    long nhour, nmin, nsecond;
    time_t now;
    while (!kbhit()) { // Ű �Է��� ���� ������ �ݺ�
        now = time(NULL);
        second = difftime(now, start);
        nhour = (long)(second / 3600); // �� ���
        nmin = (long)(fmod(second, 3600) / 60); // �� ���
        nsecond = (long)(fmod(second, 60)); // �� ���
        display_time(nhour, nmin, nsecond); // ��� �ð� ǥ��
    }
}

void display_time(long nhour, long nmin, long nsecond) {
    system("cls"); // ȭ�� �����
    printf("stopwatch\n\n");
    printf("%.2ld�� %.2ld�� %.2ld�� \n\n", nhour, nmin, nsecond);
    printf("Enter:(����/����), SPACE:�����, 'r':��� ����, Esc:����\n");
}

void save_record(long nhour, long nmin, long nsecond) {
    records[record_count][0] = nhour; // �� ����
    records[record_count][1] = nmin; // �� ����
    records[record_count][2] = nsecond; // �� ����
    record_count++; // ��� ���� ����
    printf("����� ����Ǿ����ϴ�: %.2ld�� %.2ld�� %.2ld��\n", nhour, nmin, nsecond); // ����� �ð� ǥ��
}

void display_records(void) {
    printf("����� ���:\n"); // ��� ��� ����
    for (int i = 0; i < record_count; i++) {
        printf("%d: %.2ld�� %.2ld�� %.2ld��\n", i + 1, records[i][0], records[i][1], records[i][2]); // ����� ��� ���
    }
    printf("\n"); // �� �ٲ�
}

void reset_records(void) {
    record_count = 0; // ��� ���� �ʱ�ȭ
    for (int i = 0; i < MAX_RECORDS; i++) {
        records[i][0] = 0;
        records[i][1] = 0;
        records[i][2] = 0;
    }
}

