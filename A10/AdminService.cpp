#include "AdminService.h"

#include "ActionAdd.h"
#include "ActionRemove.h"
#include "ActionUpdate.h"
#include "CSVFileSaver.h"
#include "HTMLFileSaver.h"

AdminService::AdminService(Repository& repo) : repo(repo)
{
}

void AdminService::add_tutorial(string title, string presenter, int minutes, int seconds, int likes, string link)
{
	TutorialValidator::validate_info(title,presenter, minutes, seconds, likes, link);
	Tutorial new_tutorial = Tutorial(title, presenter, minutes, seconds, likes, link);
	if (this->repo.find(new_tutorial) != -1)
	{
		throw ServiceError("Tutorial already exists!");
	}
	this->repo.add(new_tutorial);
	this->repo.clearRedoStack();
	this->repo.pushUndoAction(new ActionAdd (repo, new_tutorial));
}

void AdminService::remove_tutorial(int position)
{
	position--;
	if (position < 0 || position >= this->repo.length())
	{
		throw ServiceError("Invalid position");
	}
	Tutorial tutorial = this->repo[position];
	this->repo.remove_position(position);
	this->repo.clearRedoStack();
	this->repo.pushUndoAction(new ActionRemove(repo, tutorial, position));
}

bool is_digits_only(const string& str)
{
	for (char c : str)
	{
		if (c < '0' || c>'9')
		{
			return false;
		}
	}
	return true;
}

void AdminService::update_tutorial(int position, string to_update, string update_info)
{
	int index = position - 1;
	if (index < 0 || index >= this->repo.length())
	{
		throw ServiceError("Invalid position");
	}

	Tutorial oldTutorial = this->repo[index];
	Tutorial newTutorial = oldTutorial;

	if (to_update == "title")
	{
		TutorialValidator::validate_title(to_update);
		newTutorial.set_title(update_info);

	}
	else if (to_update == "presenter")
	{
		TutorialValidator::validate_presenter(to_update);
		newTutorial.set_presenter(update_info);

	}
	else if (to_update == "minutes")
	{
		if (!is_digits_only(update_info))
		{
			throw ServiceError("Please insert only digits for numerical values");
		}
		TutorialValidator::validate_minutes(stoi(update_info));
		newTutorial.set_minutes(stoi(update_info));

	}
	else if (to_update == "seconds")
	{
		if (!is_digits_only(update_info))
		{
			throw ServiceError("Please insert only digits for numerical values");
		}
		TutorialValidator::validate_seconds(stoi(update_info));
		newTutorial.set_seconds(stoi(update_info));

	}
	else if (to_update == "likes")
	{
		if (!is_digits_only(update_info))
		{
			throw ServiceError("Please insert only digits for numerical values");
		}
		TutorialValidator::validate_likes(stoi(update_info));
		newTutorial.set_likes(stoi(update_info));

	}
	else if (to_update == "link")
	{
		TutorialValidator::validate_link(to_update);
		newTutorial.set_link(update_info);

	}
	else
	{
		throw exception();
	}

	this->repo.remove_position(index);
	this->repo.insert_tutorial(newTutorial, index);
	this->repo.save_to_file();
	this->repo.clearRedoStack();
	this->repo.pushUndoAction(new ActionUpdate(repo, oldTutorial, newTutorial, index));
}

vector<Tutorial>& AdminService::get_all_tutorials()
{
	if (this->repo.length() == 0)
	{
		throw ServiceError("No tutorials available!");
	}
	return this->repo.get_all_tutorials();
}

void AdminService::saveDataToFileSaver(string& type, string& filename)
{
	FileSaver* saver = nullptr;
	string extension;
	if (type == "CSV")
	{
		saver = new CSVFileSaver();
		extension = ".csv";
	}
	else if (type == "HTML")
	{
		saver = new HTMLFileSaver();
		extension = ".html";
	}
	else
	{
		throw ServiceError("Invalid file saver type!");
	}

	vector<Tutorial>& tutorials = this->repo.get_all_tutorials();
	string full_filename = filename + extension;
	saver->save(tutorials, full_filename);
	delete saver;
}

void AdminService::undo()
{
	this->repo.undo();
}

void AdminService::redo()
{
	this->repo.redo();
}

bool AdminService::canUndo() const
{
	return this->repo.canUndo();
}

bool AdminService::canRedo() const
{
	return this->repo.canRedo();
}
