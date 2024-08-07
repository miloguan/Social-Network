#include "post.h"
#include <string>
#include <iostream>

Post::Post() {
    //As this is a default constructor, these values ideally shouldn't be used
    messageId_ = 0;
    ownerId_ = 0;
    message_ = "";
    likes_ = 0;
}

Post::Post(int messageId, int ownerId, std::string message, int likes){
    messageId_ = messageId;
    ownerId_ = ownerId;
    message_ = message;
    likes_ = likes;
}

std::string Post::toString(){
    std::string retval = message_ + " Liked by " + std::to_string(likes_) + " people.";
    return retval;
}

int Post::getMessageId(){
    return messageId_;
}

int Post::getOwnerId(){
    return ownerId_;
}

std::string Post::getMessage() {
    return message_;
}

int Post::getLikes() {
    return likes_;
}

std::string Post::getAuthor(){
    return "";
}


bool Post::getIsPublic(){
    return true;
}

IncomingPost::IncomingPost() : Post::Post() {
    author_ = "";
    isPublic_ = true;
}

IncomingPost::IncomingPost(int messageId, int ownerId, std::string message, int likes, bool isPublic, std::string author): Post::Post(messageId, ownerId, message, likes){
    author_ = author;
    isPublic_ = isPublic;
}

std::string IncomingPost::getAuthor() {
    return author_;
}

bool IncomingPost::getIsPublic() {
    std::string s = Post::getAuthor();
    return isPublic_;
}

std::string IncomingPost::toString() {
    std::string privacyString;
    if(isPublic_) {
        privacyString = "";
    } else {
        privacyString = " (private)";
    }
    std::string retval = author_ + " wrote" + privacyString + ": " + Post::toString();
    return retval;
}
