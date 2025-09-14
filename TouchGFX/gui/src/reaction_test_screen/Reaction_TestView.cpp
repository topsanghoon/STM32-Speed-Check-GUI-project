#include <gui/reaction_test_screen/Reaction_TestView.hpp>
#include <texts/TextKeysAndLanguages.hpp>

#include <stdio.h>
extern "C" {
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "task.h"
}

extern TaskHandle_t xHandleReact;

Reaction_TestView::Reaction_TestView() {}

void Reaction_TestView::setupScreen()
{
    Reaction_TestViewBase::setupScreen();

    Unicode::fromUTF8((const uint8_t*)"Hello", textArea1Buffer, TEXTAREA1_SIZE);
    Reaction_TestViewBase::textArea1.setWildcard(textArea1Buffer);

    // 그래프 초기화
    graph.clear();
    graph.setGraphRangeY(0, 1000);  // 최대 1000ms
    graph.setGraphRangeX(1, 5);     // 최대 5개만 표시
    graph.invalidate();

    if (xHandleReact != NULL && eTaskGetState(xHandleReact) == eSuspended)
    {
        printf("[TouchGFX] Reaction_TestView 화면 진입 -> Task resume\n");
        vTaskResume(xHandleReact);
    }
}

void Reaction_TestView::tearDownScreen()
{
    Reaction_TestViewBase::tearDownScreen();
}


void Reaction_TestView::addReactionTime(int value)
{
    graph.addDataPoint(value);  // xIndex 등 추가적으로 필요하면 조정
}
