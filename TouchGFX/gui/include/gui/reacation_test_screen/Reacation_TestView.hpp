#ifndef REACATION_TESTVIEW_HPP
#define REACATION_TESTVIEW_HPP

#include <gui_generated/reacation_test_screen/Reacation_TestViewBase.hpp>
#include <gui/reacation_test_screen/Reacation_TestPresenter.hpp>

class Reacation_TestView : public Reacation_TestViewBase
{
public:
    Reacation_TestView();
    virtual ~Reacation_TestView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void updateTextArea(const char* text);
protected:
};

#endif // REACATION_TESTVIEW_HPP
