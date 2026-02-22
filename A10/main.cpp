#include "GUI.h"
#include "AdminService.h"
#include "UserService.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QFont appFont("Arial", 20);
	app.setFont(appFont);

	Repository admin_repo("database.txt");
	Repository watch_list_repo("watchlist.txt");
	AdminService admin_service(admin_repo);
	UserService user_service(admin_repo, watch_list_repo);

	GUI gui(admin_service, user_service);
	gui.show();

	return app.exec();

}