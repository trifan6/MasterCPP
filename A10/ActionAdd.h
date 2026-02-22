#pragma once
#include "Action.h"
#include "Repository.h"
#include "Tutorial.h"

class ActionAdd : public Action
{
private:
    Repository& repo;
    Tutorial addedTutorial;
public:
    ActionAdd(Repository& repo, const Tutorial& addedTutorial);
    void executeUndo() override;
    void executeRedo() override;
};