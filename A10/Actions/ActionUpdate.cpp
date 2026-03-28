#include "ActionUpdate.h"

ActionUpdate::ActionUpdate(Repository &repo, const Tutorial &oldTutorial, const Tutorial &newTutorial, int position)
    : repo(repo), oldTutorial(oldTutorial), newTutorial(newTutorial), position(position) {}

void ActionUpdate::executeUndo()
{
    this->repo.remove_position(this->position);
    this->repo.insert_tutorial(this->oldTutorial, this->position);
}

void ActionUpdate::executeRedo()
{
    this->repo.remove_position(this->position);
    this->repo.insert_tutorial(this->newTutorial, this->position);
}