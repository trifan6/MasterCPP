#pragma once
#include "../Repository/Repository.h"
#include "../Domain/Tutorial.h"
#include "../Domain/TutorialValidator.h"
#include "../Repository/CSVFileSaver.h"
#include "../Repository/HTMLFileSaver.h"
using namespace std;

class AdminService
{
private:
	friend class UserService;
	Repository& repo;

public:
	AdminService(Repository& repo);
	void add_tutorial(string title, string presenter, int minutes, int seconds, int likes, string link);
	void remove_tutorial(int position);
	void update_tutorial(int position, string to_update, string update_info);
	vector<Tutorial>& get_all_tutorials();
	void saveDataToFileSaver(string& type, string& filename);
	void undo();
	void redo();
	bool canUndo() const;
	bool canRedo() const;

};