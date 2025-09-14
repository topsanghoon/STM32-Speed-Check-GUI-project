#include <gui/main_screen/MainView.hpp>
#include <math.h>
#include <stdlib.h>

static uint16_t randomish(int32_t seed)
{
    static uint16_t last = 0;
    const uint16_t num = (seed * (1337 + last)) % 0xFFFF;
    last = num;
    return num;
}

MainView::MainView()
{
}

void MainView::setupScreen()
{
    MainViewBase::setupScreen();

}

void MainView::tearDownScreen()
{
    MainViewBase::tearDownScreen();
}

void MainView::handleTickEvent()
{
}

void MainView::sliderValueChanged(int value)
{
}
