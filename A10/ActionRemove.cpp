#include "ActionRemove.h"

ActionRemove::ActionRemove(Repository &repo, const Tutorial &removedTutorial, int pos) : repo(repo), removedTutorial(removedTutorial), position(pos) {}

void ActionRemove::executeUndo()
{
    this->repo.insert_tutorial(this->removedTutorial, this->position);
}

void ActionRemove::executeRedo()
{
    int pos = this->repo.find(this->removedTutorial);
    if (pos != -1)
    {
        this->repo.remove_position(pos);
    }
}

