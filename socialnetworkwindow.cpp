#include "socialnetworkwindow.h"
#include "ui_socialnetworkwindow.h"
#include <sstream>
#include <string>
#include <iostream>//For testing and debugging
#include <random>

SocialNetworkWindow::SocialNetworkWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SocialNetworkWindow)
{
    ui->setupUi(this);
    connect(ui->loginButton, &QPushButton::clicked, this, &SocialNetworkWindow::login);
    connect(ui->friendsTable, &QTableWidget::itemClicked, this, &SocialNetworkWindow::tableClickGo);//The implicit field item should be passed in the signal to tableClickGo
    connect(ui->backButton, &QPushButton::clicked, this, &SocialNetworkWindow::goBack);
    connect(ui->addFriendButton, &QPushButton::clicked, this, &SocialNetworkWindow::addFriend);
    connect(ui->friendSuggestionsTable, &QTableWidget::itemClicked, this, &SocialNetworkWindow::tableClickAddFriend);
    connect(ui->logoutButton, &QPushButton::clicked, this, &SocialNetworkWindow::goLogin);
    connect(ui->accountCreation, &QPushButton::clicked, this, &SocialNetworkWindow::goCreateAccount);
    connect(ui->makeAccountButton, &QPushButton::clicked, this, &SocialNetworkWindow::addAccount);

    n_ = Network();
    curPage_ = 0;
    char fileName[] = "/Users/miloguan/Qt2/Projects/MiloG-HW-62/users.txt";
    char postFile[] = "/Users/miloguan/Qt2/Projects/MiloG-HW-62/posts.txt";
    n_.readUsers(fileName);
    n_.readPosts(postFile);
    //you_ and uDisplay_ are left uninitialized
    display();
}

void SocialNetworkWindow::setNetwork(Network n){
    n_ = n;
}

void SocialNetworkWindow::setYou(User* u) {
    you_ = u;
}

void SocialNetworkWindow::setUserDisplayed(User* u) {
    uDisplay_ = u;
}

void SocialNetworkWindow::addFriend(){
    n_.addConnection(you_->getName(), uDisplay_->getName());
    char fileName[] = "/Users/miloguan/Qt2/Projects/MiloG-HW-62/users.txt";
    n_.writeUsers(fileName);
    display();
}

void SocialNetworkWindow::goBack(){
    curPage_ = 1;
    uDisplay_ = you_;
    display();
}

void SocialNetworkWindow::goLogin(){
    curPage_ = 0;
    you_ = nullptr;//Is it ok to set it to nullptr?
    uDisplay_ = nullptr;
    display();
}

void SocialNetworkWindow::goCreateAccount(){
    curPage_ = 3;
    display();
}

void SocialNetworkWindow::addAccount(){
    std::string nameU = ui->nameBox->toPlainText().toStdString();
    int yearU = ui->yearSpin->value();
    int zipU = ui->zipSpin->value();
    ui->loginTextEdit->clear();
    std::stringstream ss(nameU);
    std::string firstname, lastname;
    ss >> firstname >> lastname;
    if (firstname.size() == 0 || lastname.size() == 0) {
        QString label2 = "Error: Invalid name";
        ui->loginLabel_2->setText(label2);
    } else if(yearU < 1000 || yearU > 9999) {
        ui->yearSpin->setValue(2000);
        QString label3 = "Error: Invalid year";
        ui->loginLabel_3->setText(label3);
    } else if(zipU < 1000 || zipU > 99999) {
        ui->yearSpin->setValue(10000);
        QString label4 = "Error: Invalid zip code";
        ui->loginLabel_4->setText(label4);
    } else {
        std::set<int> wfriends = std::set<int>{};
        std::string wname = firstname + " " + lastname;
        User* newU = new User(n_.numUsers(), wname, yearU, zipU, wfriends);
        n_.addUser(newU);
        char fileName[] = "/Users/miloguan/Qt2/Projects/MiloG-HW-62/users.txt";
        n_.writeUsers(fileName);
        you_ = n_.getUser(n_.getId(wname));
        uDisplay_ = you_;
        curPage_ = 1;
        display();
    }
}

void SocialNetworkWindow::login(){
    //Called on loginButton click
    QString userName = ui->loginTextEdit->toPlainText();
    ui->loginTextEdit->clear();
    if(n_.getId(userName.toStdString()) == -1){
        QString errorMessage = "Error: user not found. Please enter a valid user name.";
        ui->loginLabel->setText(errorMessage);//It's more convenient to have the loginLabel update here rather than in display()
    } else {      
        you_ = n_.getUser(n_.getId(userName.toStdString()));
        uDisplay_ = you_;
        curPage_ = 1;
        display();
    }
}

void SocialNetworkWindow::tableClickGo(QTableWidgetItem* item){
    //item should be the UI item that was clicked
    QString name = item->text();
    int id = n_.getId(name.toStdString());
    uDisplay_ = n_.getUser(id);
    if(id == you_->getId()){
        curPage_ = 1;
        display();
    }else{
        curPage_ = 2;
        display();
    }
}

void SocialNetworkWindow::tableClickAddFriend(QTableWidgetItem* item){
    QString name = item->text();
    n_.addConnection(you_->getName(), name.toStdString());
    char fileName[] = "/Users/miloguan/Qt2/Projects/MiloG-HW-62/users.txt";
    n_.writeUsers(fileName);
    display();
}

void SocialNetworkWindow::makeFriendsTable(){
    ui->friendsTable->clear();

    ui->friendsTable->show();

    ui->friendsTable->setColumnCount(1);
    ui->friendsTable->setRowCount(uDisplay_->getFriends().size());

    int row = 0;
    for(int id : uDisplay_->getFriends()){
        QString friendName = QString::fromStdString(n_.getUser(id)->getName());
        QTableWidgetItem* f = new QTableWidgetItem();
        f->setText(friendName);
        ui->friendsTable->setItem(0, row, f);
        row++;
    }
}

void SocialNetworkWindow::makeFriendsSuggestion(){
    ui->friendSuggestionsTable->clear();

    ui->friendSuggestionsTable->show();
    int score = -1;
    std::vector<int> friendSuggestions;
    //show friends suggestions in friendsSuggestionsTable
    if(you_->getFriends().size() < 1){
        int friendStartNum = 5;
        friendSuggestions = std::vector<int>(friendStartNum);
        for(int i = 0; i < friendStartNum; i++){
            int potentialFriend = rand() % n_.numUsers();//You could get the same user more than once - that's ok
            int score = -1;
            while(n_.suggestFriends(potentialFriend, score).size() == 0){
                potentialFriend = rand() % n_.numUsers();
            }
            friendSuggestions[i] = potentialFriend;
        }
    } else {
        friendSuggestions = n_.suggestFriends(you_->getId(), score);
    }
    ui->friendSuggestionsTable->setColumnCount(1);
    ui->friendSuggestionsTable->setRowCount(friendSuggestions.size());
    int row = 0;
    bool friendsAlready = false;
    for(int id : friendSuggestions){
        //Check if user is already friends with them
        for(int i : you_->getFriends()){
            if(id == i){
                friendsAlready = true;
            }
        }
        //Then add friend suggestion to table
        if(!friendsAlready){
            QString friendName = QString::fromStdString(n_.getUser(id)->getName());
            QTableWidgetItem* f = new QTableWidgetItem();
            f->setText(friendName);
            ui->friendSuggestionsTable->setItem(0, row, f);
            row++;
            friendsAlready = false;
        }
    }
}

//display only updates the UI, helper methods do backend work
//curPage 0 on login, 1 on user's profile page, 2 on someone else's page
void SocialNetworkWindow::display(){
    //Keep in mind that we start with login, and it should never be the case that curPage is greater than 0 before you_ and uDisplay_ are initialized
    if(curPage_ == 0){
        //Create login page
        ui->addFriendButton->hide();
        ui->backButton->hide();
        ui->friendSuggestionsTable->hide();
        ui->friendsTable->hide();
        ui->profileTitle->hide();
        ui->postsLabel->hide();
        ui->logoutButton->hide();
        ui->loginLabel_2->hide();
        ui->loginLabel_3->hide();
        ui->loginLabel_4->hide();
        ui->nameBox->hide();
        ui->yearSpin->hide();
        ui->zipSpin->hide();
        ui->makeAccountButton->hide();

        ui->accountCreation->show();

        ui->loginButton->show();

        ui->loginLabel->show();
        QString startingMessage = "Enter your name";
        ui->loginLabel->setText(startingMessage);

        ui->loginTextEdit->show();
    } else if(curPage_ == 1){
        //Create user's own page
        ui->loginButton->hide();
        ui->loginLabel->hide();
        ui->loginTextEdit->hide();
        ui->addFriendButton->hide();
        ui->backButton->hide();
        ui->accountCreation->hide();
        ui->loginLabel_2->hide();
        ui->loginLabel_3->hide();
        ui->loginLabel_4->hide();
        ui->nameBox->hide();
        ui->yearSpin->hide();
        ui->zipSpin->hide();
        ui->makeAccountButton->hide();

        ui->logoutButton->show();

        makeFriendsSuggestion();

        makeFriendsTable();
        //shows friendsTable and user friends in friendsTable


        ui->profileTitle->show();
        QString title = "My profile";
        ui->profileTitle->setText(title);

        ui->postsLabel->show();
        //show posts
        std::string postString = uDisplay_->getPostsString(5, false);
        QString postQString = QString::fromStdString(postString);
        ui->postsLabel->setText(postQString);
    } else if(curPage_ == 2){
        //Create another user's page
        ui->loginButton->hide();
        ui->loginLabel->hide();
        ui->loginTextEdit->hide();
        ui->friendSuggestionsTable->hide();
        ui->accountCreation->hide();
        ui->loginLabel_2->hide();
        ui->loginLabel_3->hide();
        ui->loginLabel_4->hide();
        ui->nameBox->hide();
        ui->yearSpin->hide();
        ui->zipSpin->hide();
        ui->makeAccountButton->hide();

        makeFriendsTable();
        //shows friendsTable and user friends in friendsTable

        ui->logoutButton->show();

        ui->profileTitle->show();
        std::string name = uDisplay_->getName();
        QString title = QString::fromStdString(name);
        title.append("'s profile");//This should work right?
        ui->profileTitle->setText(title);

        ui->postsLabel->show();
        //show posts
        std::string postString = uDisplay_->getPostsString(5, true);
        QString postQString = QString::fromStdString(postString);
        ui->postsLabel->setText(postQString);

        ui->addFriendButton->show();

        ui->backButton->show();
    } else if(curPage_ == 3){
        ui->loginButton->hide();
        ui->loginLabel->hide();
        ui->loginTextEdit->hide();
        ui->friendSuggestionsTable->hide();
        ui->accountCreation->hide();
        ui->addFriendButton->hide();
        ui->backButton->hide();
        ui->friendsTable->hide();
        ui->postsLabel->hide();

        ui->logoutButton->show();
        ui->loginLabel_2->show();
        ui->loginLabel_3->show();
        ui->loginLabel_4->show();
        ui->nameBox->show();
        ui->yearSpin->show();
        ui->yearSpin->setRange(1000, 9999);
        ui->zipSpin->show();
        ui->zipSpin->setRange(1000, 99999);
        ui->makeAccountButton->show();

        //I repurposed the profile title here
        ui->profileTitle->show();
        QString title2 = "Create New Profile";
        ui->profileTitle->setText(title2);
    }
}

SocialNetworkWindow::~SocialNetworkWindow()
{
    delete ui;
}
