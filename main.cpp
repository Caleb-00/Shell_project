#include <iostream>
#include <string>
#include <filesystem>
#include <cstdlib>
#include <sstream>
#include <unistd.h>

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  
  while (true) { // loops forever
    std::cout << "$ ";

    std::string user_input; // input for user typed values
    std::getline(std::cin,user_input); // takes in the user input in get line format 

    if (user_input == "exit") {
      break;
    } 
    else if (user_input.substr(0, 5) == "echo ") {
      std::cout << user_input.substr(5)<< std::endl; // outputs the user input after the echo command
    } 
    else if (user_input.substr(0, 5) == "type ") {
      if (user_input.substr(5) == "exit" || user_input.substr(5) == "echo" || user_input.substr(5) == "type") {
        std::cout << user_input.substr(5) << " is a shell builtin" << std::endl;
      }
      else {
        const char* path = std::getenv("PATH");
        std::istringstream path_str(path);
        std::string pathsplit;
        bool found = false;
        while(std::getline(path_str,pathsplit,':')) {
            std::string filepath = pathsplit + "/" + user_input.substr(5);
            if (access(filepath.c_str(), X_OK) == 0) {
                std::cout << user_input.substr(5) << " is " << filepath << std::endl; // outputs the file path if the input
                found=true;
                break;
            }
        }
        if(!found) {
            std::cout << user_input.substr(5) << ": not found" << std::endl; // outputs the file path if the input
        }

      }
    }

    
    else {
      std::cout << user_input << ": command not found"<< std::endl; // outputs user input if the input does not exist

    }
  }
}