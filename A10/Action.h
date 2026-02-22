#pragma once

class Repository;
class Tutorial;

class Action
{
    public:
    virtual ~Action() {}
    virtual void executeUndo() = 0;
    virtual void executeRedo() = 0;
};