#pragma once
#include <string>
#include <iostream>
using namespace std;

class Tutorial
{
private:
	string title;
	string presenter;
	struct 
	{
		int minutes;
		int seconds;
	}duration;
	int likes;
	string link;

public:
	Tutorial();
	Tutorial(string& title, string& presenter, int minutes, int seconds, int likes, string& link);

	string& get_title();
	string& get_presenter();
	int get_minutes();
	int get_seconds();
	int get_likes();
	string& get_link();
	void set_title(string& new_title);
	void set_presenter(string& new_presenter);
	void set_minutes(int new_minutes);
	void set_seconds(int new_seconds);
	void set_likes(int new_likes);
	void set_link(string& new_link);
	bool operator==(const Tutorial& other_tutorial);

	friend ostream& operator<<(ostream& out, const Tutorial& tutorial);
	friend istream& operator>>(istream& in, Tutorial& tutorial);
};