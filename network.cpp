#include "network.h"

#include <vector>
#include <string>
#include <fstream>      //std::ifstream
#include <sstream>       //std::sstream
#include <iostream>
#include <queue>
#include <stack>
#include "user.h"
#include "set"
#include <algorithm>

Network::Network() {
    users_ = std::vector<User*>{};
}

User* Network::getUser(int id) {
    if(id < users_.size()) {
        return users_.at(id);
    } else {
        return nullptr;
    }
}

void Network::addUser(User* user){
    //Checks if user is already in network
    for (User * u: users_){
        if(u == user){
            return;
        }
    }
    users_.push_back(user);
}

int Network::addConnection(std::string s1, std::string s2) {
    if(s1 == s2) return -1;
    User * user1 = getUser(getId(s1));
    User * user2 = getUser(getId(s2));
    if(getId(s1) == -1) {
        return -1;
    }
    if(getId(s2) == -1) {
        return -1;
    }
    for (User * u: users_)
    {
        if(u->getName() == s1){
            user1 = u;
        }
        if(u->getName() == s2){
            user2 = u;
        }
    }
    user1->addFriend(user2->getId());
    user2->addFriend(user1->getId());
    return 0;
}

int Network::deleteConnection(std::string s1, std::string s2) {
    if(s1 == s2) return -1;
    User * user1 = getUser(getId(s1));
    User * user2 = getUser(getId(s2));
    if(getId(s1) == -1) {
        return -1;
    }
    if(getId(s2) == -1) {
        return -1;
    }
    for (User * u: users_)
    {
        if(u->getName() == s1){
            user1 = u;
        }
        if(u->getName() == s2){
            user2 = u;
        }
    }
    std::set<int>& user1friends = user1->getFriends();
    std::set<int>& user2friends = user2->getFriends();
    bool user1has2 = false, user2has1 = false;
    for(int i1: user1friends){
        if(i1 == user2->getId()){
            user1has2=true;
        }
    }
    for(int i2: user2friends){
        if(i2 == user1->getId()){
            user2has1=true;
        }
    }
    if(user1has2 && user2has1){
        user1->deleteFriend(user2->getId());
        user2->deleteFriend(user1->getId());
        return 0;
    }
    return -1;
}

int Network::getId(std::string name) {
    for (User * u: users_) {
        if(u->getName() == name){
            return u->getId();
        }
    }
    return -1;
}

int Network::numUsers() {
    return users_.size();
}

int Network::readUsers(char* fname) {
    std::string myLine;
    std::ifstream myFile (fname);
    if(myFile.fail()){
        return -1;
    }
    int curLine = 0;
    int wyear, wzip, wf;//int wid
    std::string firstname, lastname;
    int fileNumUsers;
    while(getline(myFile, myLine)) {
        std::stringstream ss(myLine);
        if(curLine == 0) {
            ss >> fileNumUsers;
        }
        if(curLine%5 == 1){
            //Do nothing, as we are on the user id line
        }
        if(curLine%5 == 2){
            ss >> firstname >> lastname;
        }
        if(curLine%5 == 3){
            ss >> wyear;
        }
        if(curLine%5 == 4){
            ss >> wzip;
        }
        if(curLine%5 == 0 && curLine != 0){
            //We are on the friends list line
            //A new user will not be created unless there are 5 lines, so a single blank line at the end of users.txt won't matter
            std::string wname = firstname + " " + lastname;
            std::set<int> wfriends = std::set<int>{};
            while(ss >> wf) {
                wfriends.insert(wf);
            }
            User* wuser = new User(numUsers(), wname, wyear, wzip, wfriends);
            addUser(wuser);
        }
        curLine++;
    }
    if(numUsers() != fileNumUsers) return -1;
    myFile.close();
    return 0;
}

int Network::writeUsers(char* fname) {
    std::string myLine;
    std::ofstream myFile (fname);
    if(myFile.fail()){
        return -1;
    }
    myFile << numUsers() << "\n";//Adds number of users to line 0
    //int curUser = 0;
    for (User * u: users_) {
        myFile << u->getId() << "\n";//Adds user id
        myFile << "\t" << u->getName() << "\n";//Adds user name
        myFile << "\t" << u->getYear() << "\n";//Adds user year
        myFile << "\t" << u->getZip() << "\n";// adds user zip
        myFile << "\t";
        int j = u->getFriends().size();
        if(j == 0); //There are no users
        else {

            for(int i: u->getFriends()){//adds user friends
                myFile << i;
                myFile << " ";
            }
        }
        myFile << "\n";
        //curUser++;
    }
    myFile.close();
    return 0;
}

std::vector<int> Network::shortestPath(int from, int to){
    if(from == to){
        std::vector<int> retval(1, from);
        return retval;
    }
    std::queue<int> qu;//Tracks which nodes we need to visit next
    std::vector<bool> visited(numUsers(), false);//Tracks which nodes have been visited
    std::vector<int> prev(numUsers(), -1);//Tracks the path that is taken, each space contains the user that leads to that space
    visited[from] = true;
    qu.push(from);
    bool found = false;
    while(qu.size() > 0 && !found) {
        int cur = qu.front();
        qu.pop();
        if(cur == to) found = true;
        for(int neighbor: getFriends(cur)){
            if(!visited[neighbor]){
                visited[neighbor] = true;
                prev[neighbor] = cur;
                qu.push(neighbor);
            }
        }
    }
    if(prev[to] == -1){
        return {};//"to" was not visited, so the search failed.
    }

    //Record route in prev to a stack
    std::stack<int> stk;
    int i = to;
    stk.push(i);
    while(i != from){
        i = prev[i];
        stk.push(i);
    }


    std::vector<int> retval(stk.size(), -1);
    int j = 0;
    while(!stk.empty()){
        retval[j] = stk.top();
        stk.pop();
        j++;
    }
    return retval;
}

//It looks kinda silly at first, but I think this is more efficient than calling shortestPath multiple times
std::vector<int> Network::distanceUser(int from, int& to, int distance){
    if(distance > users_.size()) {//since there can't be a user who is more than distance away from "from", there is no such user
        to = -1;
        return {};
    }
    if(distance == 0){
        to = from;
        std::vector<int> retval(1, from);
        return retval;
    }
    std::vector<std::set<int>> levels(numUsers());//each set n in levels represents the nodes of distance n from from.
    std::queue<int> qu;//Tracks which nodes we need to visit next
    std::vector<bool> visited(numUsers(), false);//Tracks which nodes have been visited
    std::vector<int> prev(numUsers(), -1);//Tracks the path that is taken, each space contains the user that leads to that space
    visited[from] = true;
    qu.push(from);
    int n = 0;
    while(qu.size() > 0) {
        int cur = qu.front();
        qu.pop();
        //adds the neighbors of nodes on level n to level n+1
        for(int neighbor: getFriends(cur)){
            if(!visited[neighbor]){
                visited[neighbor] = true;
                prev[neighbor] = cur;
                levels[n+1].insert(neighbor);
            }
        }
        if(n == distance){
            //we can end the while loop, since we've reached level n, which has nodes which are n away from from.
            to = cur;
            break;
        }
        if(qu.size() == 0){//We've reached the end of the current level n
            if(levels[n+1].empty()){
                //We've reached the end of the nodes connected to "from", so there's no node of distance "distance"
                to = -1;
                return {};
            }else{
                for(int i: levels[n+1]){//Load the nodes on the next level to qu
                    qu.push(i);
                }
                n++;
            }
        }
    }

    //record the route from "from" to "to" in prev to a stack
    std::stack<int> stk;
    int i = to;
    stk.push(i);
    while(i != from){
        i = prev[i];
        stk.push(i);
    }


    std::vector<int> retval(stk.size(), -1);
    int j = 0;
    while(!stk.empty()){
        retval[j] = stk.top();
        stk.pop();
        j++;
    }
    levels.clear();//hoping to not waste memory!
    return retval;
}

std::vector<int> Network::suggestFriends(int who, int& score) {
    std::vector<bool> visited(numUsers(), false);//Tracks which nodes have been visited
    std::vector<int> prev(numUsers(), -1);//Tracks the path that is taken, each space contains the user that leads to that space
    //Mark all users less than 2 away from who as visited
    visited[who] = true;
    for(int i: getFriends(who)){
        visited[i] = true;
    }

    //find all users 2 away from who
    std::set<int> users2away;
    for(int neighbor: getFriends(who)){
        for(int i: getFriends(neighbor)){
            if(!visited[i]){
                users2away.insert(i);
                visited[i] = true;
            }
        }
    }

    //Check if there are any suggestions
    if(users2away.empty()){
        score = 0;
        return {};
    }

    //Filter candidates with highscore into fs, clearing fs if a candidate with a higher score is found
    int highscore = 0;
    std::set<int> fs;
    for(int candidate: users2away){
        int cscore = numcommonfriends(who, candidate);
        if(cscore > highscore){
            highscore = cscore;
            fs.clear();
            fs.insert(candidate);
        } else if(cscore == highscore){
            fs.insert(candidate);
        }
    }
    score = highscore;
    std::vector<int> retval(fs.size(), -1);
    int count = 0;
    for(int i: fs){
        retval[count] = i;
        count++;
    }
    return retval;
}

int Network::numcommonfriends(int a, int b){
    std::set<int> afriends = getFriends(a);
    std::set<int> bfriends = getFriends(b);
    int retval = 0;
    for(int i: afriends){
        for(int j: bfriends){
            if(i == j){
                retval++;
            }
        }
    }
    return retval;
}

//I'm assuming that the order of comps and the vectors in comps doesn't matter, and we don't need prev
std::vector<std::vector<int>> Network::groups(){
    std::vector<std::vector<int>> comps(numUsers(), std::vector<int>(numUsers()));//each vector v in comps represents a connected component
    std::vector<bool> visited(numUsers(), false);//Tracks which nodes have been visited
    //std::vector<int> prev(numUsers(), -1);//Tracks the path that is taken, each space contains the user that leads to that space
    int compnum = 0;//Tracks the number of connected components
    std::vector<int> usernums(numUsers());//tracks the number of users in each connected component
    for(User* u: users_){
        int uid = u->getId();
        int neighbornum = 0;//Tracks the current number of neighbors in the current connnected component.
        if(visited[uid]){
            continue;
        }else{
            //Everything here only runs if u is part of a new connnected component.
            std::stack<int> stk;//Tracks which nodes we need to visit next
            stk.push(uid);
            while(!stk.empty()){
                int cur = stk.top();
                stk.pop();
                for(int neighbor: getFriends(cur)){
                    if(!visited[neighbor]){
                        visited[neighbor] = true;
                        comps[compnum][neighbornum] = neighbor;
                        stk.push(neighbor);
                        neighbornum++;
                        usernums[compnum] = neighbornum;
                    }
                }
            }
            compnum++;
        }
    }

    //retval is comps but cut down to size
    std::vector<std::vector<int>> retval(compnum);
    for(int i = 0; i < compnum; i++){
        retval[i] = std::vector<int>(usernums[i]);
        for(int j = 0; j < usernums[i]; j++){
            retval[i][j] = comps[i][j];
        }
    }
    return retval;
}

std::set<int> Network::getFriends(int id) {
    if(getUser(id) == nullptr){
        std::cout << "Error: user not found" << std::endl;
        return {-1};
    } else {
        User* u = getUser(id);
        return u->getFriends();
    }
}

void Network::addPost(int ownerId, std::string message, int likes, bool isIncoming, std::string authorName, bool isPublic){
    User* u = users_[ownerId];
    int numPosts = getNumPosts();
    Post* p;
    if(isIncoming){
        p = new IncomingPost(numPosts, ownerId, message, likes, isPublic, authorName);
        u->addPost(p);
    } else{
        p = new Post(numPosts, ownerId, message, likes);
        u->addPost(p);
    }
}


std::string Network::getPostsString(int ownerId, int howMany, bool showOnlyPublic) {
    std::string retval = getUser(ownerId)->getPostsString(howMany, showOnlyPublic);
    return retval;
}

int Network::readPosts(char* fname){
    std::string myLine;
    std::ifstream myFile (fname);
    if(myFile.fail()){
        return -1;
    }
    int curLine = 0;
    int mid, ownerId, likes;//mid = message id, ownerID = ownerID, likes = likes of message
    std::string message;//The message
    std::string mw;//Individual word in message
    std::string pubstring;//Public/private status of message if present
    bool isPublic;//True if public, false if private
    std::string afirstname, alastname;//Author first name and last name if author is present
    bool isIncoming;
    int fileNumPosts;
    while(getline(myFile, myLine)) {
        std::stringstream ss(myLine);
        if(curLine == 0) {
            ss >> fileNumPosts;//We are on the first line
        }
        if(curLine%6 == 1){
            ss >> mid;//We are on the message id line
        }
        if(curLine%6 == 2){
            //We are on the message line
            message = "";//Once loop repeats, we need to clear the message
            while(ss >> mw){
                message += mw + " ";
            }
        }
        if(curLine%6 == 3){
            ss >> ownerId;//We are on the user id line
        }
        if(curLine%6 == 4){
            ss >> likes;//We are on the likes line
        }
        if(curLine%6 == 5){
            //we are on the public private status line
            ss >> pubstring;
            if(pubstring.compare("public") == 0){
                isIncoming = true;
                isPublic = true;
            } else if(pubstring.compare("private") == 0){
                isIncoming = true;
                isPublic = false;
            } else {
                isIncoming = false;
            }
        }
        if(curLine%6 == 0 && curLine != 0){
            //We are on the author name line
            //A new post will not be created unless there are 6 lines, so a single blank line at the end of posts.txt won't matter
            std::string authorName = "";
            if(isIncoming){
                ss >> afirstname >> alastname;
                authorName = afirstname + " " + alastname;
            }

            addPost(ownerId, message, likes, isIncoming, authorName, isPublic);
        }
        curLine++;
    }
    myFile.close();
    return 0;
}

//pre: none
//post: compares p1 and p2, returns false if their messageId_ is equal, true if p1 has a smaller messageId_, false if p1 has a larger messageId_.
//not a member function, since sort doesn't take member functions
bool pcompare(Post* p1, Post* p2){
    if(p1->getMessageId() == p2->getMessageId()) return false;
    if(p1->getMessageId() < p2->getMessageId()) return true;
    if(p1->getMessageId() > p2->getMessageId()) return false;
    return 0;//This should not run in any control path
}

int Network::writePosts(char* fname){
    std::vector<Post*> allposts;
    for(User* u: users_){
        for(Post* pinu: u->getPosts()){
            allposts.push_back(pinu);
        }
    }

    std::sort(allposts.begin(), allposts.end(), pcompare);
    //Now allposts should be sorted by id


    std::string myLine;
    std::ofstream myFile (fname);
    if(myFile.fail()){
        return -1;
    }
    myFile << getNumPosts() << "\n";//Adds number of users to line 0
    //int curUser = 0;
    bool isIncoming;
    for (Post* p: allposts) {
        myFile << p->getMessageId() << "\n";//Adds user id
        myFile << "\t" << p->getMessage() << "\n";//Adds user name
        myFile << "\t" << p->getOwnerId() << "\n";//Adds user year
        myFile << "\t" << p->getLikes() << "\n";// adds user zip
        //Uses getAuthor to check if p is an IncomingPost
        if(p->getAuthor() == ""){
            isIncoming = false;
        } else {
            isIncoming = true;
        }
        myFile << "\t";
        if(isIncoming){
            if(p->getIsPublic()){
                myFile << "public";
            }else if(!p->getIsPublic()){
                myFile << "private";
            }
        }
        myFile << "\n";
        myFile << "\t";
        if(isIncoming){
            myFile << p->getAuthor();
        }
        myFile << "\n";

        //curUser++;
    }
    myFile.close();
    return 0;
}

int Network::getNumPosts() {
    int retval = 0;
    for(User* u: users_){
        retval += u->getPosts().size();
    }
    return retval;
}
