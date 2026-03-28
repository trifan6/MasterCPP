#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include "../Actions/Action.h"
#include "../Exceptions/Exceptions.h"
#include "FileSaver.h"
#include "../Domain/Tutorial.h"

class Repository
{
private:
	vector<Tutorial> tutorials;
	string filename;
	vector<Action*> undoStack;
	vector<Action*> redoStack;

public:
	Repository(string filename);
	~Repository();

	void load_from_file();
	void save_to_file();

	int add(const Tutorial& tutorial);
	int remove_position(int position);
	int find(const Tutorial& tutorial);
	int length();
	Tutorial& operator[](int position);
	vector<Tutorial>& get_all_tutorials();
	void undo();
	void redo();
	void clearRedoStack();
	void insert_tutorial(const Tutorial& tutorial, int position);
	void pushUndoAction(Action* action);
	bool canUndo() const;
	bool canRedo() const;
};
