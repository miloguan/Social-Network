/********************************************************************************
** Form generated from reading UI file 'socialnetworkwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SOCIALNETWORKWINDOW_H
#define UI_SOCIALNETWORKWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SocialNetworkWindow
{
public:
    QWidget *centralwidget;
    QTextEdit *loginTextEdit;
    QPushButton *loginButton;
    QLabel *loginLabel;
    QLabel *profileTitle;
    QTableWidget *friendsTable;
    QLabel *postsLabel;
    QPushButton *backButton;
    QPushButton *addFriendButton;
    QTableWidget *friendSuggestionsTable;
    QPushButton *logoutButton;
    QPushButton *accountCreation;
    QLabel *loginLabel_2;
    QLabel *loginLabel_3;
    QLabel *loginLabel_4;
    QPushButton *makeAccountButton;
    QSpinBox *yearSpin;
    QSpinBox *zipSpin;
    QTextEdit *nameBox;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SocialNetworkWindow)
    {
        if (SocialNetworkWindow->objectName().isEmpty())
            SocialNetworkWindow->setObjectName("SocialNetworkWindow");
        SocialNetworkWindow->resize(800, 600);
        centralwidget = new QWidget(SocialNetworkWindow);
        centralwidget->setObjectName("centralwidget");
        loginTextEdit = new QTextEdit(centralwidget);
        loginTextEdit->setObjectName("loginTextEdit");
        loginTextEdit->setGeometry(QRect(180, 210, 291, 31));
        loginButton = new QPushButton(centralwidget);
        loginButton->setObjectName("loginButton");
        loginButton->setGeometry(QRect(490, 211, 81, 31));
        loginLabel = new QLabel(centralwidget);
        loginLabel->setObjectName("loginLabel");
        loginLabel->setGeometry(QRect(180, 250, 401, 61));
        loginLabel->setWordWrap(true);
        profileTitle = new QLabel(centralwidget);
        profileTitle->setObjectName("profileTitle");
        profileTitle->setGeometry(QRect(307, 20, 161, 71));
        QFont font;
        font.setPointSize(20);
        profileTitle->setFont(font);
        profileTitle->setAlignment(Qt::AlignCenter);
        profileTitle->setWordWrap(true);
        friendsTable = new QTableWidget(centralwidget);
        if (friendsTable->columnCount() < 1)
            friendsTable->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        friendsTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        friendsTable->setObjectName("friendsTable");
        friendsTable->setGeometry(QRect(20, 80, 131, 421));
        QFont font1;
        font1.setPointSize(10);
        friendsTable->setFont(font1);
        friendsTable->setAutoScroll(true);
        friendsTable->setEditTriggers(QAbstractItemView::DoubleClicked|QAbstractItemView::SelectedClicked);
        friendsTable->setShowGrid(false);
        friendsTable->setWordWrap(true);
        friendsTable->setCornerButtonEnabled(false);
        friendsTable->horizontalHeader()->setVisible(false);
        friendsTable->horizontalHeader()->setHighlightSections(false);
        friendsTable->verticalHeader()->setVisible(false);
        friendsTable->verticalHeader()->setHighlightSections(false);
        postsLabel = new QLabel(centralwidget);
        postsLabel->setObjectName("postsLabel");
        postsLabel->setGeometry(QRect(220, 70, 331, 341));
        postsLabel->setWordWrap(true);
        backButton = new QPushButton(centralwidget);
        backButton->setObjectName("backButton");
        backButton->setGeometry(QRect(260, 470, 251, 32));
        addFriendButton = new QPushButton(centralwidget);
        addFriendButton->setObjectName("addFriendButton");
        addFriendButton->setGeometry(QRect(590, 290, 100, 32));
        friendSuggestionsTable = new QTableWidget(centralwidget);
        if (friendSuggestionsTable->columnCount() < 1)
            friendSuggestionsTable->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        friendSuggestionsTable->setHorizontalHeaderItem(0, __qtablewidgetitem1);
        friendSuggestionsTable->setObjectName("friendSuggestionsTable");
        friendSuggestionsTable->setGeometry(QRect(640, 80, 131, 421));
        friendSuggestionsTable->setFont(font1);
        friendSuggestionsTable->setAutoScroll(true);
        friendSuggestionsTable->setEditTriggers(QAbstractItemView::DoubleClicked|QAbstractItemView::SelectedClicked);
        friendSuggestionsTable->setShowGrid(false);
        friendSuggestionsTable->setWordWrap(true);
        friendSuggestionsTable->setCornerButtonEnabled(false);
        friendSuggestionsTable->horizontalHeader()->setVisible(false);
        friendSuggestionsTable->horizontalHeader()->setHighlightSections(false);
        friendSuggestionsTable->verticalHeader()->setVisible(false);
        friendSuggestionsTable->verticalHeader()->setHighlightSections(false);
        logoutButton = new QPushButton(centralwidget);
        logoutButton->setObjectName("logoutButton");
        logoutButton->setGeometry(QRect(260, 500, 251, 32));
        accountCreation = new QPushButton(centralwidget);
        accountCreation->setObjectName("accountCreation");
        accountCreation->setGeometry(QRect(260, 500, 251, 32));
        loginLabel_2 = new QLabel(centralwidget);
        loginLabel_2->setObjectName("loginLabel_2");
        loginLabel_2->setGeometry(QRect(150, 80, 401, 61));
        loginLabel_2->setWordWrap(true);
        loginLabel_3 = new QLabel(centralwidget);
        loginLabel_3->setObjectName("loginLabel_3");
        loginLabel_3->setGeometry(QRect(150, 140, 401, 61));
        loginLabel_3->setWordWrap(true);
        loginLabel_4 = new QLabel(centralwidget);
        loginLabel_4->setObjectName("loginLabel_4");
        loginLabel_4->setGeometry(QRect(150, 210, 401, 61));
        loginLabel_4->setWordWrap(true);
        makeAccountButton = new QPushButton(centralwidget);
        makeAccountButton->setObjectName("makeAccountButton");
        makeAccountButton->setGeometry(QRect(260, 370, 251, 32));
        yearSpin = new QSpinBox(centralwidget);
        yearSpin->setObjectName("yearSpin");
        yearSpin->setGeometry(QRect(330, 160, 181, 22));
        zipSpin = new QSpinBox(centralwidget);
        zipSpin->setObjectName("zipSpin");
        zipSpin->setGeometry(QRect(330, 230, 181, 22));
        nameBox = new QTextEdit(centralwidget);
        nameBox->setObjectName("nameBox");
        nameBox->setGeometry(QRect(330, 100, 181, 31));
        SocialNetworkWindow->setCentralWidget(centralwidget);
        loginTextEdit->raise();
        loginButton->raise();
        loginLabel->raise();
        profileTitle->raise();
        friendsTable->raise();
        postsLabel->raise();
        backButton->raise();
        friendSuggestionsTable->raise();
        addFriendButton->raise();
        logoutButton->raise();
        accountCreation->raise();
        loginLabel_2->raise();
        loginLabel_3->raise();
        loginLabel_4->raise();
        makeAccountButton->raise();
        yearSpin->raise();
        zipSpin->raise();
        nameBox->raise();
        menubar = new QMenuBar(SocialNetworkWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 37));
        SocialNetworkWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(SocialNetworkWindow);
        statusbar->setObjectName("statusbar");
        SocialNetworkWindow->setStatusBar(statusbar);

        retranslateUi(SocialNetworkWindow);

        QMetaObject::connectSlotsByName(SocialNetworkWindow);
    } // setupUi

    void retranslateUi(QMainWindow *SocialNetworkWindow)
    {
        SocialNetworkWindow->setWindowTitle(QCoreApplication::translate("SocialNetworkWindow", "SocialNetworkWindow", nullptr));
        loginButton->setText(QCoreApplication::translate("SocialNetworkWindow", "Login", nullptr));
        loginLabel->setText(QCoreApplication::translate("SocialNetworkWindow", "Enter Your Name", nullptr));
        profileTitle->setText(QCoreApplication::translate("SocialNetworkWindow", "My Profile", nullptr));
        QTableWidgetItem *___qtablewidgetitem = friendsTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SocialNetworkWindow", "Item", nullptr));
        postsLabel->setText(QCoreApplication::translate("SocialNetworkWindow", "Put 5 most recent posts here", nullptr));
        backButton->setText(QCoreApplication::translate("SocialNetworkWindow", "Go back to own profile", nullptr));
        addFriendButton->setText(QCoreApplication::translate("SocialNetworkWindow", "AddFriend", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = friendSuggestionsTable->horizontalHeaderItem(0);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SocialNetworkWindow", "Item", nullptr));
        logoutButton->setText(QCoreApplication::translate("SocialNetworkWindow", "Logout", nullptr));
        accountCreation->setText(QCoreApplication::translate("SocialNetworkWindow", "Create new account", nullptr));
        loginLabel_2->setText(QCoreApplication::translate("SocialNetworkWindow", "Enter Your Name", nullptr));
        loginLabel_3->setText(QCoreApplication::translate("SocialNetworkWindow", "Enter Your date of birth", nullptr));
        loginLabel_4->setText(QCoreApplication::translate("SocialNetworkWindow", "Enter your zip code", nullptr));
        makeAccountButton->setText(QCoreApplication::translate("SocialNetworkWindow", "Create New Account", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SocialNetworkWindow: public Ui_SocialNetworkWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOCIALNETWORKWINDOW_H
