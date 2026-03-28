#include "TutorialValidator.h"

void TutorialValidator::validate(Tutorial &tutorial)
{
    validate_title(tutorial.get_title());
    validate_presenter(tutorial.get_presenter());
    validate_minutes(tutorial.get_minutes());
    validate_seconds(tutorial.get_seconds());
    validate_likes(tutorial.get_likes());
    validate_link(tutorial.get_link());
}

void TutorialValidator::validate_title(const string &new_title)
{
    if (new_title.empty()) throw ValidationError("Title cannot be empty");
}

void TutorialValidator::validate_presenter(const string &new_presenter)
{
    if (new_presenter.empty()) throw ValidationError("Presenter cannot be empty");
}

void TutorialValidator::validate_minutes(int new_minutes)
{
    if (new_minutes < 0) throw ValidationError("Minutes cannot be negative");
}

void TutorialValidator::validate_seconds(int new_seconds)
{
    if (new_seconds < 0) throw ValidationError("Seconds cannot be negative");
    if (new_seconds > 59) throw ValidationError("Seconds cannot exceed 59");
}

void TutorialValidator::validate_likes(int new_likes)
{
    if (new_likes < 0) throw ValidationError("Likes cannot be negative");
}

void TutorialValidator::validate_link(const string &new_link)
{
    if (new_link.empty()) throw ValidationError("Link cannot be empty");
}

void TutorialValidator::validate_info(const string &title, const string &presenter, int minutes, int seconds, int likes, const string &link)
{
    validate_title(title);
    validate_presenter(presenter);
    validate_minutes(minutes);
    validate_seconds(seconds);
    validate_likes(likes);
    validate_link(link);
}
