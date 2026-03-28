#include "Tutorial.h"

Tutorial::Tutorial()
{
	this->title = "";
	this->presenter = "";
	this->duration.minutes = 0;
	this->duration.seconds = 0;
	this->likes = 0;
	this->link = "";
}

Tutorial::Tutorial(const string& title, const string& presenter, int minutes, int seconds, int likes, const string& link)
{
	this->title = title;
	this->presenter = presenter;
	this->duration.minutes = minutes;
	this->duration.seconds = seconds;
	this->likes = likes;
	this->link = link;
}

const string& Tutorial::get_title() const { return this->title; }
const string& Tutorial::get_presenter() const { return this->presenter; }
int Tutorial::get_minutes() const { return this->duration.minutes; }
int Tutorial::get_seconds() const { return this->duration.seconds; }
int Tutorial::get_likes() const { return this->likes; }
const string& Tutorial::get_link() const { return this->link; }

void Tutorial::set_title(const string& new_title) { this->title = new_title; }
void Tutorial::set_presenter(const string& new_presenter) { this->presenter = new_presenter; }
void Tutorial::set_minutes(int new_minutes) { this->duration.minutes = new_minutes; }
void Tutorial::set_seconds(int new_seconds) { this->duration.seconds = new_seconds; }
void Tutorial::set_likes(int new_likes) { this->likes = new_likes; }
void Tutorial::set_link(const string& new_link) { this->link = new_link; }

bool Tutorial::operator==(const Tutorial& other_tutorial) const
{
	return this->title == other_tutorial.title && this->presenter == other_tutorial.presenter;
}

ostream& operator<<(ostream& out, const Tutorial& tutorial)
{
	out << tutorial.title << "\n"
		<< tutorial.presenter << "\n"
		<< tutorial.duration.minutes << "\n"
		<< tutorial.duration.seconds << "\n"
		<< tutorial.likes << "\n"
		<< tutorial.link;
	return out;
}

istream& operator>>(istream& in, Tutorial& tutorial)
{
	getline(in, tutorial.title);
	getline(in, tutorial.presenter);
	in >> tutorial.duration.minutes;
	in >> tutorial.duration.seconds;
	in >> tutorial.likes;
	in.ignore();
	getline(in, tutorial.link);
	return in;
}