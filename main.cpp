#include <iostream>
#include <string>
#include <filesystem>
#include <cstdlib>
#include <sstream>
#include <unistd.h>
#include <cstdio>
#include <vector>
#include <sys/wait.h>

int main() {
    // Flush output immediately so the shell prompt appears correctly
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    while (true) {
        std::cout << "$ ";

        std::string user_input;
        std::getline(std::cin, user_input);

        if (user_input == "exit") {
            break;
        } else if (user_input.substr(0, 5) == "echo ") {
            std::cout << user_input.substr(5) << std::endl;
        } else if (user_input == "pwd") {
            std::cout << std::filesystem::current_path().string() << std::endl;
        } else if (user_input.substr(0, 5) == "type ") {
            std::string command = user_input.substr(5);

            if (command == "exit" ||
                command == "echo" ||
                command == "type" ||
                command == "pwd") {

                std::cout << command << " is a shell builtin" << std::endl;
            } else {
                const char* path = std::getenv("PATH");
                std::istringstream path_str(path);

                std::string pathsplit;
                bool found = false;

                while (std::getline(path_str, pathsplit, ':')) {
                    std::string filepath = pathsplit + "/" + command;

                    if (access(filepath.c_str(), X_OK) == 0) {
                        std::cout << command << " is " << filepath << std::endl;
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    std::cout << command << ": not found" << std::endl;
                }
            }
        } else {
            const char* path = std::getenv("PATH");
            std::istringstream path_str(path);

            std::string pathsplit;
            bool found = false;
            std::string command = user_input;

            if (user_input.find(' ') != std::string::npos) {
                command = user_input.substr(0, user_input.find(' '));
            }

            while (std::getline(path_str, pathsplit, ':')) {
                std::string filepath = pathsplit + "/" + command;

                if (access(filepath.c_str(), X_OK) == 0) {
                    found = true;

                    std::vector<std::string> inputs;
                    std::istringstream iss(user_input);

                    std::string word;

                    while (iss >> word) {
                        inputs.push_back(word);
                    }

                    std::vector<char*> args;

                    for (auto& input : inputs) {
                        args.push_back(const_cast<char*>(input.c_str()));
                    }

                    args.push_back(nullptr);

                    pid_t pid = fork();

                    if (pid == 0) {
                        // Child process runs the external program
                        execvp(filepath.c_str(), args.data());

                        perror("execvp failed");
                        exit(1);
                    } else if (pid > 0) {
                        // Parent shell waits for program to finish
                        waitpid(pid, nullptr, 0);
                    } else {
                        perror("fork failed");
                    }

                    break;
                }
            }

            if (!found) {
                std::cout << command << ": command not found" << std::endl;
            }
        }
    }
}

