#include "UserService.h"

UserService::UserService(Repository& DataBase, Repository& WatchList) : DataBase(DataBase), WatchList(WatchList)
{
}

vector<Tutorial> UserService::see_tutorials_of_given_presenter(string presenter)
{
	if (this->DataBase.length() == 0)
	{
		throw ServiceError("No tutorials available!");
	}

	vector<Tutorial>& all_tutorials = this->DataBase.get_all_tutorials();
	vector<Tutorial> tutorials_of_presenter;

	for (int i = 0; i < all_tutorials.size(); i++)
	{
		if (all_tutorials[i].get_presenter() == presenter)
		{
			tutorials_of_presenter.push_back(all_tutorials[i]);
		}
	}

	return tutorials_of_presenter;
}

void UserService::add_to_watch_list(Tutorial& tutorial)
{
	if (this->WatchList.find(tutorial) != -1)
	{
		throw ServiceError("Tutorial already saved in watch list!");
	}
	if (this->DataBase.find(tutorial) == -1)
	{
			throw ServiceError("Tutorial inexistent!");
	}
	this->WatchList.add(tutorial);
}

void UserService::remove_from_watch_list(Tutorial& tutorial)
{
	int pos = this->WatchList.find(tutorial);
	if (pos == -1)
	{
		throw ServiceError("Tutorial not saved in the watch list");
	}
	this->WatchList.remove_position(pos);
}

void UserService::like_tutorial(Tutorial& tutorial)
{
	int db_pos = this->DataBase.find(tutorial);
	if (db_pos == -1) {
		throw ServiceError("Tutorial not found in the database. It may have been deleted by an Admin!");
	}

	Tutorial& db_tutorial = this->DataBase[db_pos];
	int current_likes = db_tutorial.get_likes();
	db_tutorial.set_likes(current_likes + 1);

	int wl_pos = this->WatchList.find(tutorial);
	if (wl_pos != -1) {
		Tutorial& wl_tutorial = this->WatchList[wl_pos];
		wl_tutorial.set_likes(current_likes + 1);
	}

	tutorial.set_likes(current_likes + 1);

	this->DataBase.save_to_file();
	this->WatchList.save_to_file();
}

vector<Tutorial>& UserService::see_watch_list()
{
	vector<Tutorial>& watch_list = this->WatchList.get_all_tutorials();
	if (watch_list.size() == 0)
	{
		throw ServiceError("Watch list is empty!");
	}
	return watch_list;
}

void UserService::saveDataToFileSaver(string &type, string &filename)
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

	vector<Tutorial>& tutorials = this->WatchList.get_all_tutorials();
	string full_filename = filename + extension;
	saver->save(tutorials, full_filename);
	delete saver;
}



