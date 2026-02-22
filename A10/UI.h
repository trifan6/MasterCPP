#pragma once
#include "AdminService.h"
#include "UserService.h"
#include <iostream>
#include <cstdlib>
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

class UI
{
private:
	AdminService& admin_service;
	UserService& user_service;
	string file_type;

public:
	UI(AdminService& admin_service, UserService& user_service);
	int start_ui();
	int admin_mode();
	int user_mode();
	void ui_admin_print_all_tutorials();
	void ui_admin_add_tutorial();
	void ui_admin_remove_tutorial();
	void ui_admin_update_tutorial();
	void ui_admin_save_in_format();
	void ui_user_see_tutorials_of_presenter();
	void ui_user_see_watch_list();
	void ui_user_delete_from_watch_list();
	void ui_user_display_watch_list();
	void ui_user_save_in_format();
};