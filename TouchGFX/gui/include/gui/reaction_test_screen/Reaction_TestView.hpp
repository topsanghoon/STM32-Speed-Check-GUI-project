#ifndef REACTION_TESTVIEW_HPP
#define REACTION_TESTVIEW_HPP

#include <gui_generated/reaction_test_screen/Reaction_TestViewBase.hpp>
#include <gui/reaction_test_screen/Reaction_TestPresenter.hpp>

class Reaction_TestView : public Reaction_TestViewBase
{
public:
    Reaction_TestView();
    virtual ~Reaction_TestView() {}

    virtual void setupScreen();
    virtual void tearDownScreen();

    void addReactionTime(int value);

protected:

};

#endif // REACTION_TESTVIEW_HPP
