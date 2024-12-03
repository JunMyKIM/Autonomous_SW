#include <stdio.h>
#include <windows.h> // Sleep 함수 사용을 위해 추가

// 제한 속도와 단속구간 길이를 상수로 정의
#define LIMIT_SPEED 80.0 // km/h
#define TOTAL_DISTANCE 10.0 // km
#define UPDATE_INTERVAL 1 // seconds

// 함수 선언
void getInput(double* x, double* y);
int validateInput(double y);
double calculateRemainingDistance(double y);
double calculateTimeSpent(double y, double x);
double calculateRemainingTime(double total_time, double time_spent);
double calculateCruiseControlSpeed(double remaining_distance, double remaining_time);

int main() {
    double x = 100.0; // 현재 속도 (km/h) - 임의의 값
    double y = 2.0;  // 주행한 거리 (km) - 임의의 값
    double z;        // 나머지 구간에서의 속도 (km/h)
    double total_time = TOTAL_DISTANCE / LIMIT_SPEED;

    // 사용자 입력 받기 (임의의 값으로 대체)
    // getInput(&x, &y);

    // 입력 검증
    if (validateInput(y)) {
        return 1;
    }

    while (y < TOTAL_DISTANCE) {
        // 남은 거리 계산
        double remaining_distance = calculateRemainingDistance(y);

        // 주행한 시간 계산 (시간 = 거리 / 속도)
        double time_spent = calculateTimeSpent(y, x);

        // 남은 시간 계산 (총 시간 = 총 거리 / 제한 속도)
        double remaining_time = calculateRemainingTime(total_time, time_spent);

        // 남은 시간으로 남은 구간의 속도 계산
        z = calculateCruiseControlSpeed(remaining_distance, remaining_time);
        if (z < 0) {
            printf("이미 제한 속도를 초과했습니다. 속도를 줄이세요.\n");
            return 1;
        }

        // 출력
        if (z <= LIMIT_SPEED) {
            printf("크루즈 컨트롤 속도: %.2f km/h, 남은 거리: %.2f km\n", z, remaining_distance);
        }
        else {
            printf("남은 구간에서 제한 속도 %.2f km/h를 초과하지 못합니다. 속도를 조정하세요.\n", LIMIT_SPEED);
        }

        // 주행 거리 업데이트 (간단히 하기 위해 일정 시간 동안 일정 속도로 주행했다고 가정)
        y += x * UPDATE_INTERVAL / 3600.0; // km

        // 실시간 업데이트를 위해 대기
        Sleep(UPDATE_INTERVAL * 1000); // Sleep 함수는 밀리초 단위로 대기
    }

    return 0;
}

// void getInput(double *x, double *y) {
//     printf("현재 속도(km/h): ");
//     scanf("%lf", x);
//     printf("이미 주행한 거리(km): ");
//     scanf("%lf", y);
// }

int validateInput(double y) {
    if (y > TOTAL_DISTANCE || y < 0) {
        printf("잘못된 거리 입력입니다. 0과 %.2f 사이의 값을 입력하세요.\n", TOTAL_DISTANCE);
        return 1;
    }
    return 0;
}

double calculateRemainingDistance(double y) {
    return TOTAL_DISTANCE - y;
}

double calculateTimeSpent(double y, double x) {
    return y / x;
}

double calculateRemainingTime(double total_time, double time_spent) {
    return total_time - time_spent;
}

double calculateCruiseControlSpeed(double remaining_distance, double remaining_time) {
    if (remaining_time > 0) {
        return remaining_distance / remaining_time;
    }
    else {
        return -1;
    }
}