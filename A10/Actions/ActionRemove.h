#pragma once
#include "Action.h"
#include "../Repository/Repository.h"
#include "../Domain/Tutorial.h"

class ActionRemove : public Action
{
private:
    Repository& repo;
    Tutorial removedTutorial;
    int position;
public:
    ActionRemove(Repository& repo, const Tutorial& removedTutorial, int pos);
    void executeUndo() override;
    void executeRedo() override;
};