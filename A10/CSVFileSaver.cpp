#include "CSVFileSaver.h"
void CSVFileSaver::save(vector<Tutorial> &tutorials, string &filename)
{
    ofstream out(filename);
    if (!out.is_open())
    {
        throw runtime_error("Could not open file for writing: " + filename);
    }

    out << "Title,Presenter,Duration (minutes),Duration (seconds),Likes,Link\n";

    for (auto &tutorial : tutorials)
    {
        out << tutorial.get_title() << ","
        << tutorial.get_presenter() << ","
        << tutorial.get_minutes() << ","
        << tutorial.get_seconds() << ","
        << tutorial.get_likes() << ","
        << tutorial.get_link() << endl;
    }
    out.close();
}
