#include "ActionUpdate.h"

ActionUpdate::ActionUpdate(Repository &repo, const Tutorial &oldTutorial, const Tutorial &newTutorial, int position) : repo(repo), oldTutorial(oldTutorial), newTutorial(newTutorial), position(position) {}

void ActionUpdate::executeUndo()
{
    repo[position] = oldTutorial;
    repo.save_to_file();
}

void ActionUpdate::executeRedo()
{
    repo[position] = newTutorial;
    repo.save_to_file();
}

