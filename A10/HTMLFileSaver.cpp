#include "HTMLFileSaver.h"

void HTMLFileSaver::save(vector<Tutorial> &tutorials, string &filename)
{
    ofstream out(filename);
    out << R"(<!DOCTYPE html>
<html>
<head>
    <title>Tutorial Watchlist</title>
</head>
<body>
<table border="1">
    <tr>
        <td>Presenter</td>
        <td>Title</td>
        <td>Duration</td>
        <td>Likes</td>
        <td>Youtube link</td>
    </tr>
)";

    for (auto &tutorial : tutorials)
    {
        out << "    <tr>" << endl
        << "        <td>" << tutorial.get_presenter() << "</td>" << endl
        << "        <td>" << tutorial.get_title() << "</td>" << endl
        << "        <td>" << tutorial.get_minutes() << ":"
        << (tutorial.get_seconds() < 10 ? "0" : "") << tutorial.get_seconds() << "</td>" << endl
        << "        <td>" << tutorial.get_likes() << "</td>" << endl
        << "        <td><a href=\"" << tutorial.get_link() << "\">link</a></td>" << endl
        << "    </tr>" << endl;
    }

    out << R"(</table>
</body>
</html>)";
}
