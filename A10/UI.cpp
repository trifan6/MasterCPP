#include "UI.h"

UI::UI(AdminService& admin_service, UserService& user_service) : admin_service(admin_service), user_service(user_service)
{
	
}

void UI::ui_admin_print_all_tutorials()
{
	vector<Tutorial>& tutorials = this->admin_service.get_all_tutorials();

	cout << "All tutorials:" << endl << "-------------------------------------------------------------------" << endl;
	for (int i = 0; i < tutorials.size(); i++)
	{
		Tutorial t = tutorials[i];
		cout << i + 1 << ". " << t.get_title().c_str() << " by " << t.get_presenter().c_str()
		<< "(" << t.get_minutes() << ":" << t.get_seconds() << ") - " << t.get_likes()
		<< " likes" << endl << "Link: " << t.get_link().c_str() << endl;
		cout << "-------------------------------------------------------------------" << endl;
	}
}

void UI::ui_admin_add_tutorial()
{
	string title, presenter, link;
	int minutes, seconds, likes;

	cout << "Title: ";
	getline(cin >> ws, title);

	cout << "Presenter: ";
	getline(cin, presenter);

	cout << "Minutes: ";
	cin >> minutes;

	cout << "Seconds: ";
	cin >> seconds;

	cout << "Likes: ";
	cin >> likes;

	cout << "Link: ";
	cin >> ws;
	getline(cin, link);

	admin_service.add_tutorial(title, presenter, minutes, seconds, likes, link);
	cout << "Added!\n";
}

void UI::ui_admin_remove_tutorial()
{
	int pos;

	cout << "Enter tutorial number to remove: ";
	cin >> pos;

	admin_service.remove_tutorial(pos);
	cout << "Removed!\n";
}

void UI::ui_admin_update_tutorial()
{
	int pos;
	string field, value;

	cout << "Enter tutorial number: ";
	cin >> pos;

	cout << "Field to update (title/presenter/minutes/seconds/likes/link): ";
	cin >> field;

	cout << "New value: ";
	cin >> ws;
	getline(cin, value);

	admin_service.update_tutorial(pos, field, value);
	cout << "Updated!\n";
}

void UI::ui_admin_save_in_format()
{
	string filename = "database";
	this->admin_service.saveDataToFileSaver(this->file_type, filename);
}

void playVideoInBrowser(const string& videoURL) 
{
	string command = "open \"" + videoURL + "\"";
	system(command.c_str());
}

void stopPlaying()
{
	//system("killall Safari");
}

void UI::ui_user_see_tutorials_of_presenter()
{
	string presenter;
	cout << "Which presenter you would like >>> ";
	cin >> ws;
	getline(cin, presenter);

	vector<Tutorial> tutorials = this->user_service.see_tutorials_of_given_presenter(presenter);
	int index = 0;
	while (true)
	{
		if (index == tutorials.size())
		{
			index = 0;
		}

		cout << "Opening video in browser...\n";
		playVideoInBrowser(tutorials[index].get_link());

		Tutorial& t = tutorials[index];
		cout << index + 1 << ". " << t.get_title().c_str() << " by " << t.get_presenter().c_str()
		<< "(" << t.get_minutes() << ":" << t.get_seconds() << ") - " << t.get_likes()
		<< " likes" << endl << "Link: " << t.get_link().c_str() << endl;

		while (true)
		{
			cout << "===== 1. Stop watching\n"
				<< "===== 2. Like Video\n"
				<< "===== 3. Add to watchlist\n"
				<< "===== 4. Next video\n"
				<< "> ";
			int choice;
			cin >> choice;

			if (choice == 1)
			{
				cout << "Closing window...\n";
				//stopPlaying();
				return;
			}
			else if (choice == 2)
			{
				this->user_service.like_tutorial(t);
				cout << "Liked this tutorial!\n";
			}
			else if (choice == 3)
			{
				try
				{
					this->user_service.add_to_watch_list(t);
					cout << "Added to watchlist!\n";
				}
				catch (exception& e)
				{
					cout << "Error: " << e.what() << endl;
				}
				
			}
			else if (choice == 4)
			{
				cout << "Playing next video...\n";
				//stopPlaying();
				break;
			}
			else
			{
				cout << "Invalid choice. Please try again.\n";
			}
		}
		index++;
	}

}

void UI::ui_user_see_watch_list()
{
	vector<Tutorial>& tutorials = this->user_service.see_watch_list();
	cout << "-------------------------------------------------------------------" << endl;
	for (int i = 0; i < tutorials.size(); i++)
	{
		Tutorial t = tutorials[i];
		cout << i + 1 << ". " << t.get_title().c_str() << " by " << t.get_presenter().c_str()
		<< "(" << t.get_minutes() << ":" << t.get_seconds() << ") - " << t.get_likes()
		<< " likes" << endl << "Link: " << t.get_link().c_str() << endl;
		cout << "-------------------------------------------------------------------" << endl;
	}
}

void UI::ui_user_delete_from_watch_list()
{
	vector<Tutorial>& watchlist = this->user_service.see_watch_list();

	this->ui_user_see_watch_list();
	cout << "Which tutorial would you like to delete? (or exit with 0)  >>> ";
	int choice;
	cin >> choice;
	if (choice == 0)
	{
		return;
	}
	if (choice > watchlist.size() || choice < 1)
	{
		throw UIError("Invalid index!");
	}

	Tutorial& selected = watchlist[choice - 1];
	cout << "Would you like to rate the video?\n1. Like\n2. Ignore\n>>> ";
	int likeornot;
	cin >> likeornot;
	if (likeornot == 1)
	{
		this->user_service.like_tutorial(selected);
	}
	this->user_service.remove_from_watch_list(selected);
	cout << "Tutorial processed successufully!\n";
}

void UI::ui_user_display_watch_list()
{
	string command = "open \"watchlist";
	string filename = "watchlist";
	if (this->file_type == "HTML")
	{
		command += ".html\"";
	}
	else if (this->file_type == "CSV")
	{
		command += ".csv\"";
	}
	system(command.c_str());
	cout << "Opening watch list ..." << endl;
}

void UI::ui_user_save_in_format()
{
	string filename = "watchlist";
	this->user_service.saveDataToFileSaver(this->file_type, filename);
}

void print_admin_menu()
{
	cout << "===Menu===\n"
		<< " 1. Print all tutorials\n"
		<< " 2. Add a new tutorial\n"
		<< " 3. Remove a tutorial\n"
		<< " 4. Update a tutorial\n"
		<< " 5. Store data in specified file type" << endl
		<< "\n"
		<< "-1 Back to main mode menu\n"
		<< " 0. Exit\n";

}

int UI::admin_mode()
{
	cout << "Administrator mode\n";
	int choice;
	
	while (1)
	{
		try
		{
			print_admin_menu();
			cout << "\n>>> ";
			cin >> choice;
			if (choice == 0)
			{
				return 0;
			}
			else if (choice == 1)
			{
				this->ui_admin_print_all_tutorials();
			}
			else if (choice == 2)
			{
				this->ui_admin_add_tutorial();
			}
			else if (choice == 3)
			{
				this->ui_admin_remove_tutorial();
			}
			else if (choice == 4)
			{
				this->ui_admin_update_tutorial();
			}
			else if (choice == 5)
			{
				this->ui_admin_save_in_format();
			}
			else if (choice == -1)
			{
				return 1;
			}
			else if (choice == 0)
			{
				return 0;
			}
			else
			{
				throw UIError("Invalid choice!");
			}
		}
		catch (const exception& e)
		{
			cout << "Error: " << e.what() << endl;
		}

	}
}

void print_user_menu()
{
	cout << "===Menu===\n"
		<< " 1. See all the tutorials of a presenter of your choice\n"
		<< " 2. Manage watch list\n"
		<< " 3. See your watch list\n"
		<< " 4. Store data in specified file type" << endl
		<< " 5. Display watch list in right browser" << endl
		<< "\n"
		<< "-1 Back to main mode menu\n"
		<< " 0. Exit\n";
}

int UI::user_mode()
{
	cout << "User mode\n";
	int choice;
	while (1)
	{
		try
		{
			print_user_menu();
			cout << "\n>>> ";
			cin >> choice;
			if (choice == 0)
			{
				return 0;
			}
			else if (choice == 1)
			{
				this->ui_user_see_tutorials_of_presenter();
			}
			else if (choice == 2)
			{
				this->ui_user_delete_from_watch_list();
			}
			else if (choice == 3)
			{
				this->ui_user_see_watch_list();
			}
			else if (choice == 4)
			{
				this->ui_user_save_in_format();
			}
			else if (choice == 5)
			{
				this->ui_user_display_watch_list();
			}
			else if (choice == -1)
			{
				return 1;
			}
			else if (choice == 0)
			{
				return 0;
			}
			else
			{
				throw UIError("Invalid choice!");
			}
		}
		catch (const exception& e)
		{
			cout << "Error: " << e.what() << endl;
		}

	}
}

int UI::start_ui()
{
	while (1)
	{
		cout << "Choose type of file you want the data to be stored in: " << endl
		<< "1. CSV file" << endl
		<< "2. HTML file" << endl << endl
		<< "0. Exit" << endl << endl;
		int choice;
		cin >> choice;
		if (choice == 0)
		{
			return 0;
		}
		else if (choice == 1)
		{
			string fileType = "CSV";
			this->file_type = fileType;
			break;
		}
		else if (choice == 2)
		{
			string fileType = "HTML";
			this->file_type = fileType;
			break;
		}
	}

	int ok = 1;
	while (ok)
	{
		int choice;
		cout << "=== Please choose your activity node ===\n"
			<< "	1. Admin Mode\n" 
			<< "	2. User Mode\n"
			<< "	0. Exit\n"
			<< ">>> ";
		cin >> choice;
	
		if (choice == 1)
			{
				ok = this->admin_mode();
			}
		else if (choice == 2)
			{
				ok = this->user_mode();
			}
		else if (choice == 0)
		{
			return 0;
		}
		else
		{
			cout << "Invalid choice. Please try again.\n";
		}
	}
	
	return 0;
}

