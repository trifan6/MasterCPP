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
	Tutorial(const string& title, const string& presenter, int minutes, int seconds, int likes, const string& link);

	const string& get_title() const;
	const string& get_presenter() const;
	int get_minutes() const;
	int get_seconds() const;
	int get_likes() const;
	const string& get_link() const;

	void set_title(const string& new_title);
	void set_presenter(const string& new_presenter);
	void set_minutes(int new_minutes);
	void set_seconds(int new_seconds);
	void set_likes(int new_likes);
	void set_link(const string& new_link);

	bool operator==(const Tutorial& other_tutorial) const;

	friend ostream& operator<<(ostream& out, const Tutorial& tutorial);
	friend istream& operator>>(istream& in, Tutorial& tutorial);
};