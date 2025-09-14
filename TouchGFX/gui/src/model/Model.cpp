#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

Model* model_instance = nullptr;
Model::Model() : modelListener(0)
{
	model_instance = this;  // 전역 포인터 등록
}

void Model::tick()
{

}

void Model::sendReactionTimeToGUI(const char* text)
{
    if (modelListener != nullptr)
    {
        modelListener->updateReactionTime(text);
    }
}

void Model::addReactionValueToGraph(int value)
{
    if (modelListener != nullptr)
        modelListener->addReactionValueToGraph(value);
}
