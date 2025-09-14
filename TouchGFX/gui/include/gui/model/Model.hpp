#ifndef MODEL_HPP
#define MODEL_HPP

#include <stdint.h>

class Model;
extern Model* model_instance;

class ModelListener;

class Model
{
public:
    Model();
    void bind(ModelListener* listener) { modelListener = listener; }

    void tick();
    void sendReactionTimeToGUI(const char* text);
    void addReactionValueToGraph(int value);

protected:
    ModelListener* modelListener;
};

#endif // MODEL_HPP
