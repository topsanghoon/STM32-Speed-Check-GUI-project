#include "main.h"
#include "cmsis_os.h"
#include "semphr.h"
#include <stdio.h>
#include <cstdlib>
#include <gui/model/Model.hpp>

// GUI 전달용 인스턴스
extern Model* model_instance;

// 핀 정의 (CubeMX에서 설정된 핀 이름 사용)
const uint16_t ledPins[2] = {LED1_Pin, LED2_Pin};         // PB12, PB13
const uint16_t buttonPins[2] = {BUTTON1_Pin, BUTTON2_Pin}; // PC10, PC11

#ifdef __cplusplus
extern "C" {
#endif

void USER_THREADS(void);

#ifdef __cplusplus
}
#endif

// 우선순위
#define TASK_MAIN_PRIO  20
#define TASK_REACT_PRIO 10

// 핸들 정의
TaskHandle_t xHandleMain, xHandleReact;
QueueHandle_t xButtonQueue;  // 버튼 큐

// 라운드 수
#define NUM_ROUNDS 5
volatile uint32_t reactionTimes[NUM_ROUNDS];

// 난수 생성기
static unsigned int seed = 1234;
int fast_rand() {
    seed = seed * 1103515245 + 12345;
    return (seed / 65536) % 32768;
}

// 함수 선언
void TaskMain(void *pvParameters);
void ReactionTestTask(void *argument);


/*-----------------------------------------------------------
 * USER_THREADS - 시작점
 -----------------------------------------------------------*/
void USER_THREADS(void)
{
    printf("USER_THREADS()\n");

    // 버튼 큐 생성
    xButtonQueue = xQueueCreate(10, sizeof(uint16_t));

    // 메인 테스크 생성
    xTaskCreate(TaskMain, "TaskMain", 256, NULL, TASK_MAIN_PRIO, &xHandleMain);
}


/*-----------------------------------------------------------
 * 메인 테스크 - Reaction Test Task를 생성하고 종료
 -----------------------------------------------------------*/
void TaskMain(void *pvParameters)
{
    printf("TaskMain is running\n");

    xTaskCreate(ReactionTestTask, "ReactionTestTask", 512, NULL, TASK_REACT_PRIO, &xHandleReact);
    vTaskSuspend(xHandleReact);  // 처음엔 중지 상태

    printf("TaskMain is deleted\n");
    vTaskDelete(NULL);
}


/*-----------------------------------------------------------
 * ReactionTestTask - 본 게임 루프
 -----------------------------------------------------------*/
void ReactionTestTask(void *argument)
{
    char buffer[32];
    uint16_t expectedButtonPins[2] = {GPIO_PIN_10, GPIO_PIN_11}; // LED0↔BTN0, LED1↔BTN1

    printf("GameStart\n");
    vTaskDelay(pdMS_TO_TICKS(1000));
    printf("3\n"); vTaskDelay(pdMS_TO_TICKS(1000));
    printf("2\n"); vTaskDelay(pdMS_TO_TICKS(1000));
    printf("1\n"); vTaskDelay(pdMS_TO_TICKS(1000));

    for (int i = 0; i < NUM_ROUNDS; i++)
    {
        int ledIndex = fast_rand() % 2; // 0 또는 1
        vTaskDelay(pdMS_TO_TICKS(1500));

        // false start 체크
        if (uxQueueMessagesWaiting(xButtonQueue) > 0) {
            uint16_t dummy;
            xQueueReceive(xButtonQueue, &dummy, 0); // 소진
            printf("잘못된 입력! LED가 켜지기 전에 눌렀습니다\n");
            i--;
            vTaskDelay(pdMS_TO_TICKS(1000));
            continue;
        }

        // LED 켜기
        HAL_GPIO_WritePin(GPIOB, ledPins[ledIndex], GPIO_PIN_SET);
        printf("LED %d ON (PB%d)\n", ledIndex, 12 + ledIndex);

        uint32_t startTick = HAL_GetTick();

        // 버튼 입력 기다림
        uint16_t receivedPin = 0;
        while (1)
        {
            if (xQueueReceive(xButtonQueue, &receivedPin, portMAX_DELAY) == pdTRUE)
            {
                if (receivedPin == expectedButtonPins[ledIndex]) {
                    break; // 정답 버튼
                } else {
                    printf("잘못된 버튼 누름: PC%d\n", (receivedPin == GPIO_PIN_10) ? 10 : 11);
                    // 무시
                }
            }
        }

        // 반응 시간 기록
        uint32_t reactTick = HAL_GetTick();
        uint32_t reactionTime = reactTick - startTick;
        reactionTimes[i] = reactionTime;

        printf("반응 속도: %lu ms\n", reactionTime);
        sprintf(buffer, "%lu ms", reactionTime);

        if (model_instance)
        {
        	presenter->updateGraph(reactionTime);
        }
        HAL_GPIO_WritePin(GPIOB, ledPins[ledIndex], GPIO_PIN_RESET);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    // 평균 계산
    uint32_t sum = 0;
    for (int i = 0; i < NUM_ROUNDS; i++)
        sum += reactionTimes[i];

    printf("평균 반응 시간: %lu ms\n", sum / NUM_ROUNDS);

    char result[32];
    sprintf(result, "평균: %lu ms", sum / NUM_ROUNDS);
    if (model_instance)
        model_instance->sendReactionTimeToGUI(result);

    vTaskSuspend(NULL);
}


/*-----------------------------------------------------------
 * Idle Hook
 -----------------------------------------------------------*/
void vApplicationIdleHook(void)
{
    printf("."); fflush(stdout);
}


/*-----------------------------------------------------------
 * EXTI 인터럽트 콜백 - 버튼 누르면 큐에 핀 전달
 -----------------------------------------------------------*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    if (GPIO_Pin == GPIO_PIN_10 || GPIO_Pin == GPIO_PIN_11)
    {
        printf("버튼 입력 감지 (PC%d)\n", (GPIO_Pin == GPIO_PIN_10) ? 10 : 11);
        xQueueSendFromISR(xButtonQueue, &GPIO_Pin, &xHigherPriorityTaskWoken);
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}
