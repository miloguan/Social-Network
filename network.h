#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include <string>
#include "user.h"

class Network
{
public:
    //pre: none
    //post: creates a new Network
    Network();

    //pre: there is a user with an id of id in Network
    //post: returns a pointer to the corresponding user
    User* getUser(int id);

    //pre: none
    //post: adds user to users
    void addUser(User* user);

    //pre: s1 and s2 are valid strings (format: "firstname lastname") corresponding to the names of two different users in Network
    //post: creates connection between the users named s1 and s2, returns 0 if successful, -1 if invalid
    int addConnection(std::string s1, std::string s2);

    //pre: s1 and s2 are valid strings (format: "firstname lastname") corresponding to the names of two different users in Network
    //post: deletes connection between the users named s1 and s2, returns 0 if successful, -1 if invalid
    int deleteConnection(std::string s1, std::string s2);

    //pre: name is a valid string (format: "firstname lastname") corresponding to the name of a user in Network
    //post: returns the corresponding id_ of user, or -1 otherwise
    int getId(std::string name);

    //pre: none
    //post: returns the number of users in the network
    int numUsers();

    //pre: fname is the name of a valid file containing information for the network in a valid format
    //post: reads the info on fname and initializes it to this Network. Return 0 if it worked, -1 if the file didn't open(in other words always return 0)
    int readUsers(char* fname);

    //pre: fname is the name of a valid file containing information for the network in a valid format
    //post: writes the info on Network onto fname. Return 0 if it worked, -1 if the file didn't open(in other words always return 0)
    int writeUsers(char *fname);

    //pre: there is a path from "from" to "to" in the network
    //post: returns a vector listing the shortest path from "from" to "to". Returns an empty vector if "to" is not connected to "from".
    std::vector<int> shortestPath(int from, int to);

    //pre: none
    //post: sets "to" to a user who's relational distance from "from" is "distance". Returns an empty vector and sets "to" to -1 if no such user exists.
    std::vector<int> distanceUser(int from, int& to, int distance);

    //pre: none
    //post: returns a list of suggested friends for user who
    std::vector<int> suggestFriends(int who, int& score);

    //pre: none
    //post: returns a vector v, which each item in v being a connected component of users_
    std::vector<std::vector<int>> groups();

    //pre: none
    //post: creates a new post and adds it to the specified user
    void addPost(int ownerId, std::string message, int likes, bool isIncoming, std::string authorName, bool isPublic);

    //pre: none
    //post: returns the "howMany" most recent posts made by user of id ownerID, according to the format outlined by the HW
    std::string getPostsString(int ownerId, int howMany, bool showOnlyPublic);

    //pre: fname is the name of a valid file containing post information for the network in a valid format
    //post: reads the post info on fname and initializes it to this Network. Return 0 if it worked, -1 if the file didn't open(in other words always return 0)
    int readPosts(char* fname);

    //pre: fname is the name of a valid file containing post information for the network in a valid format
    //post: writes the post info of the network onto fname. Return 0 if it worked, -1 if the file didn't open(in other words always return 0)
    int writePosts(char* fname);
private:
    std::vector<User*> users_;

    //pre: none
    //post: returns the number of users a and b are both friends with
    int numcommonfriends(int a, int b);

    //pre: none
    //post: returns a set<int> containing users' friends, returns {-1} if user not found
    std::set<int> getFriends(int id);

    //pre: none
    //post: returns the total number of posts in the network
    int getNumPosts();
};

#endif // NETWORK_H
