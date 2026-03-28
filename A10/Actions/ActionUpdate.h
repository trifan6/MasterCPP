#pragma once
#include "Action.h"
#include "../Repository/Repository.h"
#include "../Domain/Tutorial.h"

class ActionUpdate : public Action
{
private:
    Repository& repo;
    Tutorial oldTutorial;
    Tutorial newTutorial;
    int position;
public:
    ActionUpdate(Repository& repo, const Tutorial& oldTutorial, const Tutorial& newTutorial, int position);
    void executeUndo() override;
    void executeRedo() override;
};