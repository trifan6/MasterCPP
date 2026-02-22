#pragma once
#include "Tutorial.h"
#include "Exceptions.h"

class TutorialValidator
{
public:
    void static validate(Tutorial& tutorial);
    void static validate_title(string& new_title);
    void static validate_presenter(string& new_presenter);
    void static validate_minutes(int new_minutes);
    void static validate_seconds(int new_seconds);
    void static validate_likes(int new_likes);
    void static validate_link(string& new_link);
    void static validate_info(string& title, string& presenter, int minutes, int seconds, int likes, string& link);
};