#ifndef SOCIALNETWORKWINDOW_H
#define SOCIALNETWORKWINDOW_H

#include <QMainWindow>
#include "QtWidgets"
#include "network.h"
#include "user.h"
#include "post.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class SocialNetworkWindow;
}
QT_END_NAMESPACE
//SocialNetworkWindow inherits from QMainWindow
class SocialNetworkWindow : public QMainWindow
{
    Q_OBJECT

public:
    //pre: none
    //post: creates a new SocialNetworkWindow
    SocialNetworkWindow(QWidget *parent = nullptr);

    //pre: none
    //post: sets n_ to n
    void setNetwork(Network n);

    //pre: none
    //post: sets you_ to u
    void setYou(User* u);

    //pre: none
    //post: sets uDisplay_ to u
    void setUserDisplayed(User* u);

    //pre: none
    //post: updates the UI depending on the states of n_, you_, and uDisplay_. Most of the frontend heavy lifting is done here
    void display();

    //pre: none
    //post: deletes this SocialNetworkWindow
    ~SocialNetworkWindow();

private:
    Ui::SocialNetworkWindow *ui;

    //Not sure how we're meant to fill these
    Network n_;//The network

    User* you_;//The user you are currently logged in as

    User* uDisplay_;//The user who's page we are currently looking at

    int curPage_;//0 on login, 1 on user's profile page, 2 on someone else's page

    //pre: none
    //post: checks if the contents of loginTextEdit are a valid user, if so, goes to the user's page and sets you_ to that user.
    void login();

    //pre: none
    //post: makes you_ friends with uDisplay_
    void addFriend();

    //pre: none
    //post: sends user back to their own page
    void goBack();

    //pre: none
    //post: sends user back to login page
    void goLogin();

    //pre: none
    //post: sends user to account creation page
    void goCreateAccount();

    //pre: none
    //post: sends user to the page of the user clicked
    void tableClickGo(QTableWidgetItem* item);

    //pre: none
    //post: adds the user clicked to user's friends
    void tableClickAddFriend(QTableWidgetItem* item);

    //private helper method of display()
    void makeFriendsTable();

    //private helper method of display()
    void makeFriendsSuggestion();

    //Makes a new account
    void addAccount();
};
#endif // SOCIALNETWORKWINDOW_H
