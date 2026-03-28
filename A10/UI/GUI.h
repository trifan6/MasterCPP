#pragma once
#include <QMainWindow>
#include <QPushButton>
#include <QTableWidget>
#include <QComboBox>
#include <QStringList>
#include <QStackedWidget>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFileDialog>
#include <QDesktopServices>
#include <QUrl>
#include <QFormLayout>
#include <QShortcut>
#include "../Services/AdminService.h"
#include "../Services/UserService.h"
#include "../Services/WatchlistTableView.h"

class GUI : public QMainWindow
{
    Q_OBJECT
private:
    AdminService& adminService;
    UserService& userService;
    QString fileType;

    QWidget* mainWidget;
    QWidget* adminWidget;
    QWidget* userWidget;

    QStackedWidget* stackedWidget;

    QComboBox* formatComboBox;
    QString currentFormat;

    //QTableWidget* adminTable;
    //QTableWidget* userTable;

public:
    GUI(AdminService& adminService, UserService& userService, QWidget *parent = nullptr);
    ~GUI();

private slots:
    void switchToAdminMode();
    void switchToUserMode();
    void switchToMainMode();
    void showAdminTutorials();
    void addTutorial();
    void removeTutorial();
    void updateTutorial();
    void showUserTutorials();
    void manageWatchlist();
    void displayWatchlist_original();
    void displayWatchlist();
    void selectFileFormat();
    void displayCurrentData();
    void saveAdminData();
    void saveUserData();
    void playVideoInBrowser(const string& url);
    void undo();
    void redo();

private:
    void setupAdminUI();
    void setupUserUI();
    void setupMainUI();
    void setupShortcuts();


};