#ifndef USER_H
#define USER_H



#include "string"
#include "set"
#include <vector>
#include "post.h"

class User
{

public:

    //pre: none
    //post: creates a new User
    User();

    //pre: none
    //post: creates a new User, with specified fields
    User(int id, std::string name, int year, int zip, std::set<int> friends);

    //pre: friends_ does not already contain id
    //post: id is inserted into this User's friends_
    void addFriend(int id);

    //pre: friends_ already contains id
    //post: id is erased from friends_
    void deleteFriend(int id);

    //pre: none
    //post: returns User's id_
    int getId();

    //pre: none
    //post: returns User's name_
    std::string getName();

    //pre: none
    //post: returns User's year_
    int getYear();

    //pre: none
    //post: returns User's zip_
    int getZip();

    //pre: none
    //post: returns a pointer to User's friends_
    std::set<int> & getFriends();

    //pre: none
    //post: adds p to messages_
    void addPost(Post* p);

    //pre: none
    //post: returns a pointer to User's messages_
    std::vector<Post*> & getPosts();

    //pre: none
    //post: returns the "howMany" most recent posts, according to the format outlined by the HW
    std::string getPostsString(int howMany, bool showOnlyPublic);
private:
    //Class invariants

    int id_;

    std::string name_;

    int year_;

    int zip_;

    std::set<int> friends_;

    std::vector<Post*> messages_;
};

#endif // USER_H
