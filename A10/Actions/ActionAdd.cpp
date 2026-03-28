#include "ActionAdd.h"

ActionAdd::ActionAdd(Repository &repo, const Tutorial &addedTutorial) : repo(repo), addedTutorial(addedTutorial) {}

void ActionAdd::executeUndo()
{
    int pos =  repo.find(this->addedTutorial);
    if (pos != -1)
    {
        this->repo.remove_position(pos);
    }
}

void ActionAdd::executeRedo()
{
    this->repo.add(this->addedTutorial);
}

