#ifndef REACTION_TESTPRESENTER_HPP
#define REACTION_TESTPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;



class Reaction_TestView;

class Reaction_TestPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    Reaction_TestPresenter(Reaction_TestView& v);

    virtual void activate();
    virtual void deactivate();

    void updateGraph(int value);

    virtual ~Reaction_TestPresenter() {}

    static Reaction_TestPresenter* instance;
    static Reaction_TestPresenter* getInstance();

private:
    Reaction_TestPresenter(); // prevent default construction
    Reaction_TestView& view;
};

#endif // REACTION_TESTPRESENTER_HPP
