#pragma once
#include "../Repository/Repository.h"
#include "../Domain/Tutorial.h"
#include "../Repository/CSVFileSaver.h"
#include "../Repository/HTMLFileSaver.h"
using namespace std;

class UserService
{
private:
	friend class AdminService;
	Repository& DataBase;
	Repository& WatchList;

public:
	UserService(Repository& DataBase, Repository& WatchList);
	vector<Tutorial> see_tutorials_of_given_presenter(string presenter);
	void add_to_watch_list(Tutorial& tutorial);
	void remove_from_watch_list(Tutorial& tutorial);
	void like_tutorial(Tutorial& tutorial);
	vector<Tutorial>& see_watch_list();
	void saveDataToFileSaver(string& type, string& filename);

};

