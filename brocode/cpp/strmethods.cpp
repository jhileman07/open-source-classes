#include <iostream>

int main() {
    
    std::string name;
    std::cout << "enter your name: ";
    std::getline(std::cin, name);

    if (name.length() > 12) {
        std::cout << "Your name can't be over 12 characters!";
    }
    name.empty(); //boolean value ""
    name.length(); //number value of length of string
    name.clear(); //clear name to empty
    name.append(""); //add a string to another string
    name.at(0); //same as string[0] in py
    name.insert(0, "@"); //inserting a character at that position
    name.find(' '); //finds position of the first space
    name.erase(0,3); //removes that slice of string
    return 0;
}