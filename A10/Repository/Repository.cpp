#include "Repository.h"

Repository::Repository(string filename)
{
	this->filename = filename;
	try {
		this->load_from_file();
	} catch (const RepositoryError& e) {
		ofstream file(this->filename);
		file.close();
	}
}

Repository::~Repository()
{
	for (Action* action : undoStack)
	{
		delete action;
	}

	for (Action* action : redoStack)
	{
		delete action;
	}
}


void Repository::load_from_file()
{
	ifstream file(this->filename);

	if (!file.is_open())
	{
		throw RepositoryError("Could not open file!");
	}

	Tutorial temp;
	while (file >> temp)
	{
		this->tutorials.push_back(temp);
	}

	file.close();
}

void Repository::save_to_file()
{
	ofstream file(this->filename);

	if (!file.is_open())
	{
		throw RepositoryError("Could not open file!");
	}

	for (const Tutorial& tutorial : this->tutorials)
	{
		file << tutorial << "\n";
	}

	file.close();
}

int Repository::add(const Tutorial& tutorial)
{
	this->tutorials.push_back(tutorial);
	this->save_to_file();
	return 1;
}

int Repository::remove_position(int position)
{
	this->tutorials.erase(this->tutorials.begin() + position);
	this->save_to_file();
	return 1;
}

int Repository::find(const Tutorial& tutorial)
{
	auto it = std::find(tutorials.begin(), tutorials.end(), tutorial);
	return (it != tutorials.end()) ? std::distance(tutorials.begin(), it) : -1;
}

int Repository::length()
{
	return this->tutorials.size();
}

Tutorial& Repository::operator[](int position)
{
	return this->tutorials[position];
}

vector<Tutorial>& Repository::get_all_tutorials()
{
	return this->tutorials;
}

void Repository::undo()
{
	if (!this->undoStack.empty())
	{
		Action* action = this->undoStack.back();
		this->undoStack.pop_back();
		action->executeUndo();
		this->redoStack.push_back(action);
		this->save_to_file();
	}
}

void Repository::redo()
{
	if (!this->redoStack.empty())
	{
		Action* action = this->redoStack.back();
		this->redoStack.pop_back();
		action->executeRedo();
		this->undoStack.push_back(action);
		this->save_to_file();
	}
}

void Repository::clearRedoStack()
{
	for (Action* action : this->redoStack)
	{
		delete action;
	}
	this->redoStack.clear();
}

void Repository::insert_tutorial(const Tutorial &tutorial, int position)
{
	this->tutorials.insert(this->tutorials.begin() + position, tutorial);
	this->save_to_file();
}

void Repository::pushUndoAction(Action* action)
{
	this->undoStack.push_back(action);
	this->clearRedoStack();
}

bool Repository::canUndo() const
{
	return !this->undoStack.empty();
}

bool Repository::canRedo() const
{
	return !this->redoStack.empty();
}
