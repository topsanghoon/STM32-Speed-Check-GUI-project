#include <gui/reaction_test_screen/Reaction_TestView.hpp>
#include <gui/reaction_test_screen/Reaction_TestPresenter.hpp>

Reaction_TestPresenter* Reaction_TestPresenter::instance = nullptr;

Reaction_TestPresenter::Reaction_TestPresenter(Reaction_TestView& v)
    : view(v)
{
    instance = this;
}

Reaction_TestPresenter* Reaction_TestPresenter::getInstance()
{
    return instance;
}

void Reaction_TestPresenter::activate() { }

void Reaction_TestPresenter::deactivate() { }


void Reaction_TestPresenter::updateGraph(int value)
{
    view.addReactionTime(value);
}
