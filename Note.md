THIS PAGE IS FOR NOTES EXPLAINING CONCEPTS IVE LEARNED DURING THIS

---------------------------------------------------------------
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
---------------------------------------------------------------


---------------------------------------------------------------
input.substr(5)
---------------------------------------------------------------

---------------------------------------------------------------
.npos
---------------------------------------------------------------

---------------------------------------------------------------
execcvp
---------------------------------------------------------------

What does fork() do? 
Splits a single process into 2 one being a child process which is indenticle to the parent but stilll seperate

Why can't a shell use only execvp()?
It need the data split up into array format because it doesnt just want the first word up until the space it wants each individual word

What is the difference between parent and child after fork()?
a parent is the original process but the chilld is essentially a copy 

What does pid == 0 mean?
means you are in the child process

Why does the parent use waitpid()?
Its waiting for the child procces to finish then it continues to $

Why does execvp() replace a process?
It replaces current proccess code with another
The child is needed because we want to sacrifice the child not the entire shell