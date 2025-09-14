#include <gui/reacation_test_screen/Reacation_TestView.hpp>
#include <gui/reacation_test_screen/Reacation_TestPresenter.hpp>
#include <stdio.h>

Reacation_TestPresenter::Reacation_TestPresenter(Reacation_TestView& v)
    : view(v)
{

}

void Reacation_TestPresenter::activate()
{

}

void Reacation_TestPresenter::deactivate()
{

}

void Reacation_TestPresenter::updateReactionTime(const char* text)
{
	printf("Reacation_TestPresenter::updateReactionTime : text: %s\n", text);
    view.updateTextArea(text);
}
