#include <gui/reacation_test_screen/Reacation_TestView.hpp>

extern "C" {
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "task.h"
}

extern TaskHandle_t xHandleReact;

Reaction_TestView::Reaction_TestView()
{
    textArea1.setWildcard(textArea1Buffer);
    Unicode::strncpy(textArea1Buffer, "대기 중...", TEXTAREA1_SIZE - 1);
    textArea1Buffer[TEXTAREA1_SIZE - 1] = '\0';
    textArea1.invalidate();
}

void Reaction_TestView::setupScreen()
{
    Reaction_TestViewBase::setupScreen();

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

void Reaction_TestView::updateTextArea(const char* text)
{
    printf("Reaction_TestView::updateTextArea : text: %s\n", text);
    Unicode::strncpy(textArea1Buffer, text, TEXTAREA1_SIZE - 1);
    textArea1Buffer[TEXTAREA1_SIZE - 1] = '\0';
    textArea1.invalidate();
}


