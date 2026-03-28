#include "GUI.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QInputDialog>
#include <QHeaderView>
#include <QTableWidget>


GUI::GUI(AdminService &adminService, UserService &userService, QWidget *parent) :adminService(adminService), userService(userService)
{
    setWindowTitle("Tutorial Manager");
    resize(800, 600);

    this->fileType = "CSV";

    this->mainWidget = new QWidget(this);
    this->userWidget = new QWidget(this);
    this->adminWidget = new QWidget(this);

    this->formatComboBox = new QComboBox();
    this->currentFormat = "CSV";

    this->setupMainUI();
    this->setupAdminUI();
    this->setupUserUI();

    this->stackedWidget = new QStackedWidget(this);
    this->stackedWidget->addWidget(this->mainWidget);
    this->stackedWidget->addWidget(this->adminWidget);
    this->stackedWidget->addWidget(this->userWidget);

    setCentralWidget(this->stackedWidget);

    this->setupShortcuts();
}

GUI::~GUI()
{

}

void GUI::setupMainUI()
{
    QVBoxLayout* layout = new QVBoxLayout(this->mainWidget);

    QLabel* titleLabel = new QLabel("Tutorial Manager", this->mainWidget);
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(40);
    titleLabel->setFont(titleFont);
    layout->addWidget(titleLabel);

    QLabel* formatLabel = new QLabel("Select file format", this->mainWidget);
    this->formatComboBox->addItems({"CSV", "HTML"});
    this->formatComboBox->setCurrentText(this->currentFormat);

    QPushButton* formatButton = new QPushButton("Confirm format", this->mainWidget);
    connect(formatButton, &QPushButton::clicked, this, &GUI::selectFileFormat);

    QHBoxLayout* formatLayout = new QHBoxLayout();
    formatLayout->addWidget(formatLabel);
    formatLayout->addWidget(formatComboBox);
    formatLayout->addWidget(formatButton);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* adminButton = new QPushButton("Admin Mode", this->mainWidget);
    QPushButton* userButton = new QPushButton("User Mode", this->mainWidget);
    buttonLayout->addWidget(adminButton);
    buttonLayout->addWidget(userButton);

    layout->addLayout(formatLayout);
    layout->addLayout(buttonLayout);

    connect(adminButton, &QPushButton::clicked, this, &GUI::switchToAdminMode);
    connect(userButton, &QPushButton::clicked, this, &GUI::switchToUserMode);

    QPalette palette = this->mainWidget->palette();
    QLinearGradient gradient(0, 0, 0, this->mainWidget->height());
    gradient.setColorAt(0, QColor(135, 206, 250));  // LightSkyBlue
    gradient.setColorAt(1, QColor(25, 25, 112));    // MidnightBlue
    palette.setBrush(QPalette::Window, gradient);
    this->mainWidget->setAutoFillBackground(true);
    this->mainWidget->setPalette(palette);
}

void GUI::setupAdminUI()
{
    QVBoxLayout* layout = new QVBoxLayout(this->adminWidget);

    QPushButton* showAllButton = new QPushButton("Show All Tutorials", this->adminWidget);
    QPushButton* addButton = new QPushButton("Add Tutorial", this->adminWidget);
    QPushButton* removeButton = new QPushButton("Remove Tutorial", this->adminWidget);
    QPushButton* updateButton = new QPushButton("Update Tutorial", this->adminWidget);
    QPushButton* saveButton = new QPushButton("Save Data", this->adminWidget);
    QPushButton* backButton = new QPushButton("Back to Main", this->adminWidget);
    QPushButton* displayButton = new QPushButton("Display Data in respective app", this->adminWidget);
    QPushButton* undoButton = new QPushButton("Undo", this->adminWidget);
    QPushButton* redoButton = new QPushButton("Redo", this->adminWidget);

    QVBoxLayout* buttonLayout = new QVBoxLayout();
    buttonLayout->addWidget(showAllButton);
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(removeButton);
    buttonLayout->addWidget(updateButton);
    buttonLayout->addWidget(displayButton);
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(backButton);
    buttonLayout->addWidget(undoButton);
    buttonLayout->addWidget(redoButton);

    layout->addLayout(buttonLayout);

    connect(showAllButton, &QPushButton::clicked, this, &GUI::showAdminTutorials);
    connect(addButton, &QPushButton::clicked, this, &GUI::addTutorial);
    connect(removeButton, &QPushButton::clicked, this, &GUI::removeTutorial);
    connect(updateButton, &QPushButton::clicked, this, &GUI::updateTutorial);
    connect(saveButton, &QPushButton::clicked, this, &GUI::saveAdminData);
    connect(backButton, &QPushButton::clicked, this, &GUI::switchToMainMode);
    connect(displayButton, &QPushButton::clicked, this, &GUI::displayCurrentData);
    connect(undoButton, &QPushButton::clicked, this, &GUI::undo);
    connect(redoButton, &QPushButton::clicked, this, &GUI::redo);

}

void GUI::setupUserUI()
{
    QVBoxLayout* layout = new QVBoxLayout(this->userWidget);

    QPushButton* showTutorialsButton = new QPushButton("Show Tutorials by presenter", this->userWidget);
    QPushButton* manageWatchlistButton = new QPushButton("Manage Watchlist", this->userWidget);
    QPushButton* seeWatchlistButton = new QPushButton("See Watchlist", this->userWidget);
    QPushButton* backButton = new QPushButton("Back to Main", this->userWidget);
    QPushButton* saveButton = new QPushButton("Save Watchlist", this->userWidget);
    QPushButton* displayButton = new QPushButton("Display Watchlist in respective app", this->userWidget);

    QVBoxLayout* buttonLayout = new QVBoxLayout();
    buttonLayout->addWidget(showTutorialsButton);
    buttonLayout->addWidget(manageWatchlistButton);
    buttonLayout->addWidget(seeWatchlistButton);
    buttonLayout->addWidget(displayButton);
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(backButton);

    layout->addLayout(buttonLayout);

    connect(showTutorialsButton, &QPushButton::clicked, this, &GUI::showUserTutorials);
    connect(manageWatchlistButton, &QPushButton::clicked, this, &GUI::manageWatchlist);
    connect(seeWatchlistButton, &QPushButton::clicked, this, &GUI::displayWatchlist);
    connect(backButton, &QPushButton::clicked, this, &GUI::switchToMainMode);
    connect(displayButton, &QPushButton::clicked, this, &GUI::displayCurrentData);
    connect(saveButton, &QPushButton::clicked, this, &GUI::saveUserData);
}

void GUI::switchToMainMode()
{
    this->stackedWidget->setCurrentWidget(this->mainWidget);
}


void GUI::switchToAdminMode()
{
    this->stackedWidget->setCurrentWidget(this->adminWidget);
}

void GUI::switchToUserMode()
{
    this->stackedWidget->setCurrentWidget(this->userWidget);
}

void GUI::showAdminTutorials()
{
    try {
        vector<Tutorial> tutorials = adminService.get_all_tutorials();

        QDialog* tutorialDialog = new QDialog(this);
        tutorialDialog->setWindowTitle("All Tutorials");
        tutorialDialog->resize(800, 600);

        QTableWidget* table = new QTableWidget(tutorialDialog);
        table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        table->setColumnCount(5);
        table->setHorizontalHeaderLabels({"Title", "Presenter", "Duration", "Likes", "Link"});
        table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
        table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
        table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
        table->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
        table->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);

        table->setRowCount(tutorials.size());
        table->setMinimumWidth(1000);
        for (int i = 0; i < tutorials.size(); i++)
        {
            Tutorial& t = tutorials[i];
            table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(t.get_title())));
            table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(t.get_presenter())));
            table->setItem(i, 2, new QTableWidgetItem(QString("%1:%2").arg(t.get_minutes()).arg(t.get_seconds(), 2, 10, QChar('0'))));
            table->setItem(i, 3, new QTableWidgetItem(QString::number(t.get_likes())));
            table->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(t.get_link())));
        }

        QVBoxLayout* layout = new QVBoxLayout(tutorialDialog);
        layout->addWidget(table);
        tutorialDialog->setLayout(layout);
        tutorialDialog->exec();

    } catch (const std::exception& e) {
        QMessageBox::information(this, "Notice", e.what()); // Catches "No tutorials available!"
    }
}

void GUI::selectFileFormat()
{
    this->currentFormat = formatComboBox->currentText();
    QMessageBox::information(this, "Format Selected", QString("Data will be saved as %1 files").arg(this->currentFormat));
}

void GUI::displayCurrentData()
{
    QString command;
    if (this->currentFormat == "CSV")
    {
        command = "open watchlist.csv";
    }
    else
    {
        command = "open watchlist.html";
    }
    system(command.toStdString().c_str());
}

void GUI::saveAdminData()
{
    try {
        string format = this->currentFormat.toStdString();
        string filename = "database";
        this->adminService.saveDataToFileSaver(format, filename);
        QMessageBox::information(this, "Saved", "Admin data saved successfully!" );
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

void GUI::saveUserData()
{
    try {
        string format = this->currentFormat.toStdString();
        string filename = "watchlist";

        this->userService.saveDataToFileSaver(format, filename);

        QMessageBox::information(this, "Saved", "Watchlist saved successfully!" );
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

void GUI::playVideoInBrowser(const string& videoURL)
{
    QDesktopServices::openUrl(QUrl(QString::fromStdString(videoURL)));
}

void GUI::showUserTutorials()
{
    bool ok;
    QString presenter = QInputDialog::getText(this, "Search Tutorials",
                                              "Enter presenter name:",
                                              QLineEdit::Normal,
                                              "", &ok);
    if (!ok || presenter.isEmpty()) return;

    try {
        vector<Tutorial> tutorials = userService.see_tutorials_of_given_presenter(presenter.toStdString());

        if (tutorials.empty()) {
            QMessageBox::information(this, "No Tutorials", "No tutorials found for this presenter.");
            return;
        }

        int index = 0;
        while (true) {
            if (index >= tutorials.size()) index = 0;

            Tutorial& t = tutorials[index];

            QDialog dialog(this);
            dialog.setWindowTitle("Now Playing: " + QString::fromStdString(t.get_title()));

            QVBoxLayout* layout = new QVBoxLayout(&dialog);

            QString info = QString("Title: %1\nPresenter: %2\nDuration: %3:%4\nLikes: %5\nLink: %6")
                               .arg(QString::fromStdString(t.get_title()))
                               .arg(QString::fromStdString(t.get_presenter()))
                               .arg(t.get_minutes())
                               .arg(t.get_seconds(), 2, 10, QChar('0'))
                               .arg(t.get_likes())
                               .arg(QString::fromStdString(t.get_link()));
            layout->addWidget(new QLabel(info));

            QDialogButtonBox* buttonBox = new QDialogButtonBox;
            QPushButton* playBtn = buttonBox->addButton("Play Video", QDialogButtonBox::ActionRole); // NEW PLAY BUTTON
            QPushButton* stopBtn = buttonBox->addButton("Stop", QDialogButtonBox::RejectRole);
            QPushButton* likeBtn = buttonBox->addButton("Like", QDialogButtonBox::ActionRole);
            QPushButton* addBtn = buttonBox->addButton("Add to Watchlist", QDialogButtonBox::ActionRole);
            QPushButton* nextBtn = buttonBox->addButton("Next", QDialogButtonBox::AcceptRole);
            layout->addWidget(buttonBox);

            connect(playBtn, &QPushButton::clicked, [&]() {
                playVideoInBrowser(t.get_link());
            });

            connect(likeBtn, &QPushButton::clicked, [&]() {
                try {
                    userService.like_tutorial(t);
                    QMessageBox::information(&dialog, "Liked", "You liked this tutorial.");
                } catch (const std::exception& e) {
                    QMessageBox::critical(&dialog, "Error", e.what());
                }
            });

            connect(addBtn, &QPushButton::clicked, [&]() {
                try {
                    userService.add_to_watch_list(t);
                    QMessageBox::information(&dialog, "Added", "Tutorial added to watchlist.");
                } catch (const std::exception& e) {
                    QMessageBox::warning(&dialog, "Error", e.what());
                }
            });

            connect(stopBtn, &QPushButton::clicked, [&]() {
                dialog.done(0);
            });

            connect(nextBtn, &QPushButton::clicked, [&]() {
                dialog.done(1);
            });

            int result = dialog.exec();
            if (result == 0)
                break;
            else
                index++;
        }
    } catch (const std::exception& e) {
        QMessageBox::information(this, "Notice", e.what());
    }
}

void GUI::displayWatchlist_original()
{
    vector<Tutorial> watchlist = userService.see_watch_list();

    if (watchlist.empty()) {
        QMessageBox::information(this, "Watchlist", "Your watchlist is empty.");
        return;
    }

    QDialog* watchlistDialog = new QDialog(this);
    watchlistDialog->setWindowTitle("Your Watchlist");
    watchlistDialog->resize(800, 600);

    QTableWidget* table = new QTableWidget(watchlistDialog);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setColumnCount(5);
    table->setHorizontalHeaderLabels({"Title", "Presenter", "Duration", "Likes", "Link"});
    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch); // Title
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch); // Presenter
    table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents); // Duration
    table->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents); // Likes
    table->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch); // Link

    table->setRowCount(watchlist.size());
    table->setMinimumWidth(1000);
    for (int i = 0; i < watchlist.size(); i++) {
        Tutorial& t = watchlist[i];
        table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(t.get_title())));
        table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(t.get_presenter())));
        table->setItem(i, 2, new QTableWidgetItem(QString("%1:%2").arg(t.get_minutes()).arg(t.get_seconds(), 2, 10, QChar('0'))));
        table->setItem(i, 3, new QTableWidgetItem(QString::number(t.get_likes())));
        table->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(t.get_link())));
    }

    QVBoxLayout* layout = new QVBoxLayout(watchlistDialog);
    layout->addWidget(table);
    watchlistDialog->setLayout(layout);
    watchlistDialog->exec();
}

void GUI::displayWatchlist() {
    QDialog* watchlistDialog = new QDialog(this);
    watchlistDialog->setWindowTitle("Your Watchlist");
    watchlistDialog->resize(800, 600);

    QTableView* tableView = new QTableView(watchlistDialog);
    WatchlistTableView* model = new WatchlistTableView(userService, tableView);
    tableView->setModel(model);

    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  // makes columns stretch
    tableView->horizontalHeader()->setStretchLastSection(true); // last column fills remaining space
    tableView->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents); // Likes
    tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents); // Duration

    QVBoxLayout* layout = new QVBoxLayout(watchlistDialog);
    layout->addWidget(tableView);
    watchlistDialog->setLayout(layout);
    watchlistDialog->exec();
}

void GUI::manageWatchlist()
{
    try {
        vector<Tutorial> watchlist = userService.see_watch_list();

        QDialog* manageDialog = new QDialog(this);
        manageDialog->setWindowTitle("Manage Watchlist");
        manageDialog->resize(800, 600);

        QTableWidget* table = new QTableWidget(manageDialog);
        table->setColumnCount(6);
        table->setHorizontalHeaderLabels({"#", "Title", "Presenter", "Duration", "Likes", "Link"});

        table->setRowCount(watchlist.size());
        for (int i = 0; i < watchlist.size(); i++) {
            Tutorial& t = watchlist[i];
            table->setItem(i, 0, new QTableWidgetItem(QString::number(i+1)));
            table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(t.get_title())));
            table->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(t.get_presenter())));
            table->setItem(i, 3, new QTableWidgetItem(QString("%1:%2").arg(t.get_minutes()).arg(t.get_seconds(), 2, 10, QChar('0'))));
            table->setItem(i, 4, new QTableWidgetItem(QString::number(t.get_likes())));
            table->setItem(i, 5, new QTableWidgetItem(QString::fromStdString(t.get_link())));
        }

        QPushButton* deleteButton = new QPushButton("Delete Selected", manageDialog);
        QPushButton* likeButton = new QPushButton("Like Selected", manageDialog);
        QPushButton* closeButton = new QPushButton("Close", manageDialog);

        connect(deleteButton, &QPushButton::clicked, [this, table, manageDialog]() {
            int row = table->currentRow();
            if (row >= 0) {
                Tutorial t = userService.see_watch_list()[row];
                userService.remove_from_watch_list(t);
                QMessageBox::information(this, "Success", "Tutorial removed from watchlist!");
                manageDialog->close();
                this->manageWatchlist();
            } else {
                QMessageBox::warning(this, "Error", "Please select a tutorial first!");
            }
        });

        connect(likeButton, &QPushButton::clicked, [this, table]() {
            int row = table->currentRow();
            if (row >= 0) {
                Tutorial t = userService.see_watch_list()[row];
                try {
                    userService.like_tutorial(t);
                    QMessageBox::information(this, "Success", "Tutorial liked!");
                    table->item(row, 4)->setText(QString::number(t.get_likes()));
                } catch (const std::exception& e) {
                    QMessageBox::critical(this, "Error", e.what());
                }
            } else {
                QMessageBox::warning(this, "Error", "Please select a tutorial first!");
            }
        });

        connect(closeButton, &QPushButton::clicked, manageDialog, &QDialog::close);

        QVBoxLayout* mainLayout = new QVBoxLayout(manageDialog);
        QHBoxLayout* buttonLayout = new QHBoxLayout();

        buttonLayout->addWidget(deleteButton);
        buttonLayout->addWidget(likeButton);
        buttonLayout->addWidget(closeButton);

        mainLayout->addWidget(table);
        mainLayout->addLayout(buttonLayout);
        manageDialog->setLayout(mainLayout);
        manageDialog->exec();

    } catch (const std::exception& e) {
        QMessageBox::information(this, "Watchlist", e.what());
    }
}

void GUI::addTutorial()
{
    QDialog dialog(this);
    dialog.setWindowTitle("Add New Tutorial");

    QFormLayout form(&dialog);

    QLineEdit* titleInput = new QLineEdit(&dialog);
    QLineEdit* presenterInput = new QLineEdit(&dialog);
    QLineEdit* minutesInput = new QLineEdit(&dialog);
    QLineEdit* secondsInput = new QLineEdit(&dialog);
    QLineEdit* likesInput = new QLineEdit(&dialog);
    QLineEdit* linkInput = new QLineEdit(&dialog);

    form.addRow("Title:", titleInput);
    form.addRow("Presenter:", presenterInput);
    form.addRow("Minutes:", minutesInput);
    form.addRow("Seconds:", secondsInput);
    form.addRow("Likes:", likesInput);
    form.addRow("Link:", linkInput);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                             Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);

    QObject::connect(&buttonBox, &QDialogButtonBox::accepted, [&]() {
        bool ok;
        int minutes = minutesInput->text().toInt(&ok);
        if (!ok) {
            QMessageBox::warning(this, "Error", "Invalid minutes value");
            return;
        }

        int seconds = secondsInput->text().toInt(&ok);
        if (!ok) {
            QMessageBox::warning(this, "Error", "Invalid seconds value");
            return;
        }

        int likes = likesInput->text().toInt(&ok);
        if (!ok) {
            QMessageBox::warning(this, "Error", "Invalid likes value");
            return;
        }

        try {
            adminService.add_tutorial(
                titleInput->text().toStdString(),
                presenterInput->text().toStdString(),
                minutes,
                seconds,
                likes,
                linkInput->text().toStdString()
            );
            QMessageBox::information(this, "Success", "Tutorial added successfully!");
            dialog.accept();
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Error", QString("Failed to add tutorial: ") + e.what());
        }
    });

    QObject::connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    dialog.exec();
}

void GUI::removeTutorial()
{
    try {
        int max_size = adminService.get_all_tutorials().size();

        bool ok;
        int pos = QInputDialog::getInt(this, "Remove Tutorial",
                                      "Enter tutorial position to remove:",
                                      1, 1, max_size,
                                      1, &ok);
        if (!ok) return;

        adminService.remove_tutorial(pos);
        QMessageBox::information(this, "Success", "Tutorial removed successfully!");
    } catch (const std::exception& e) {
        QMessageBox::information(this, "Notice", e.what());
    }
}

void GUI::updateTutorial()
{
    try {
        vector<Tutorial>& tutorials = adminService.get_all_tutorials();

        bool ok;
        QStringList fields = {"title", "presenter", "minutes", "seconds", "likes", "link"};

        int pos = QInputDialog::getInt(this, "Update Tutorial",
                                      "Enter tutorial position to update (1-" +
                                      QString::number(tutorials.size()) + "):",
                                      1, 1, tutorials.size(), 1, &ok);
        if (!ok) return;

        QString field = QInputDialog::getItem(this, "Update Field",
                                            "Select field to update:",
                                            fields, 0, false, &ok);
        if (!ok) return;

        QString value = QInputDialog::getText(this, "New Value",
                                            "Enter new value for " + field + ":",
                                            QLineEdit::Normal, "", &ok);
        if (!ok || value.isEmpty()) return;

        adminService.update_tutorial(pos, field.toStdString(), value.toStdString());
        QMessageBox::information(this, "Success", "Tutorial updated successfully!");

    } catch (const std::exception& e) {
        QMessageBox::information(this, "Notice", e.what());
    }
}
void GUI::setupShortcuts()
{
    QShortcut* undoShortcut = new QShortcut(QKeySequence("Ctrl+Z"), this);
    QShortcut* redoShortcut = new QShortcut(QKeySequence("Ctrl+Y"), this);

    connect(undoShortcut, &QShortcut::activated, this, &GUI::undo);
    connect(redoShortcut, &QShortcut::activated, this, &GUI::redo);
}

void GUI::undo()
{
    try
    {
        if (!this->adminService.canUndo()) {
            QMessageBox::information(this, "Info", "Nothing left to undo!");
            return;
        }

        this->adminService.undo();
        QMessageBox::information(this, "Success", "Undo operation successful!");
    } catch (const exception& e)
    {
        QMessageBox::warning(this, "Error", e.what());
    }
}

void GUI::redo()
{
    try
    {
        if (!adminService.canRedo()) {
            QMessageBox::information(this, "Info", "Nothing left to redo!");
            return;
        }
        this->adminService.redo();
        QMessageBox::information(this, "Success", "Redo operation successful!");
    } catch (const exception& e)
    {
        QMessageBox::warning(this, "Error", e.what());
    }
}


