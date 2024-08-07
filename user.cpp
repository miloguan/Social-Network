#include "user.h"
#include <string>
#include <set>
#include "post.h"
#include <iostream>

User::User() {
    id_ = 0;
    name_ = "";
    year_ = 0;
    zip_ = 0;
    friends_ = std::set<int>{};
}

User::User(int id, std::string name, int year, int zip, std::set<int> friends) {
    id_ = id;
    name_ = name;
    year_ = year;
    zip_ = zip;
    std::set<int> placeholder = std::set<int>{};
    for (int const& i: friends)
    {
        placeholder.insert(i);
    }
    friends_ = placeholder;
}

void User::addFriend(int id) {
    if(friends_.find(id) == friends_.end()){    //returns false if there is an instance of id in set, returns true if there is no instance of id in set
        friends_.insert(id);
    }
}

void User::deleteFriend(int id) {
    if(!(friends_.find(id) == friends_.end())){
        friends_.erase(id);
    }
}

int User::getId() {
    return id_;
}
std::string User::getName() {
    return name_;
}

int User::getYear() {
    return year_;
}

int User::getZip() {
    return zip_;
}

//if used like set<int> s = username.getFriends(), s is a copy of friends_
//if used like set<int> & s = username.getFriends(), s is a reference to username's friends_, so changes to s change friends_
std::set<int> & User::getFriends() {
    return friends_;
};

void User::addPost(Post* p) {
    //Check that p is not already in messages_
    for(Post* q: messages_){
        if(q == p){
            std::cout << "Error: post already in user" << std::endl;
            return;
        }
    }
    messages_.push_back(p);//Users should be stored in increasing order of messageID, but not necessarily in order 1,2,3
}

std::vector<Post*> & User::getPosts() {
    return messages_;
}

std::string User::getPostsString(int howMany, bool showOnlyPublic){
    std::string retval = "";
    int h = messages_.size() - howMany;//h is the id of the last, least recent post we add to retval
    if(howMany<=0){//Don't return any of the posts
        return retval;
    }
    if(h < 0){//howMany must be greater than the number of posts, so we just return all of them.
        h = 0;
    }
    for(int i = messages_.size() - 1; i >= h; i--){
        if(showOnlyPublic && messages_[i]->getIsPublic() == false){
            //do nothing, since we are on showOnlyPublic mode and this Post is not public (getIsPublic returned false).
        }else{
            retval += messages_[i]->toString() + "  ";//The virtual keyword should make it so the right toString is used by the compiler automatically
        }
    }
    return retval;
}
