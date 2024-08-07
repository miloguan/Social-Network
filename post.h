#ifndef POST_H
#define POST_H

#include <string>

class Post
{
public:
    //pre: none
    //post: creates a new Post
    Post();

    //pre: none
    //post: creates a new Post, with specified fields
    Post(int messageId, int ownerId, std::string message, int likes);

    //pre: none
    //post: returns a string in the format "[message_] Liked by [likes_] people."
    virtual std::string toString();

    //pre: none
    //post: returns Post's messageId_
    int getMessageId();

    //pre: none
    //post: returns Post's ownerId_
    int getOwnerId();

    //pre: none
    //post: returns Post's message_
    std::string getMessage();

    //pre: none
    //post: returns Post's likes_
    int getLikes();

    //pre: none
    //post: returns Author of post (if there is an Author)
    virtual std::string getAuthor();

    //pre: none
    //post: returns public status of post (if there is one)
    virtual bool getIsPublic();



private:
    int messageId_;

    int ownerId_;

    std::string message_;

    int likes_;
};



class IncomingPost: public Post{
public:
    //pre: none
    //post: creates a new IncomingPost
    IncomingPost();

    //pre: none
    //post: creates a new IncomingPost, with specified fields
    IncomingPost(int messageId, int ownerId, std::string message, int likes, bool isPublic, std::string author);

    //pre: none
    //post: returns IncomingPost's author_
    std::string getAuthor();

    //pre: none
    //post: returns IncomingPost's isPublic_
    bool getIsPublic();

    //pre: none
    //post: returns a string in the format "[author_] wrote[private]: [toString]"
    std::string toString();
private:
    std::string author_;

    bool isPublic_;
};

#endif //POST_H; //end post.h
