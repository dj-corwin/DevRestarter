#include "drApplication.h"

int main(int argc, char* argv[]) {
    // Go to executable directory, for service type of execution 
    std::string path(argv[0]);
    path.erase(path.find_last_of(_DIR_SEP) + 1U);
    if (_chdir(path.c_str())) {
        switch (errno) {
        case ENOENT:
            std::cout << "Unable to locate the directory: " << path << "\n";
            break;
        case EINVAL:
            std::cout << "Invalid buffer.\n";
            break;
        default:
            std::cout << "Unknown error.\n";
        }
    }

    drApplication _app;
    return _app.run(argc, argv);
}
