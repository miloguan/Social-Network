#include "socialnetworkwindow.h"

#include <QApplication>
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);//Not sure what this does, might be worth checking

    SocialNetworkWindow w = SocialNetworkWindow();
    w.show();//User is on login page initially


    return a.exec();
}
