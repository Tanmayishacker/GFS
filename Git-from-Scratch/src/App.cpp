#include <Client.hpp>

int main(int argc, char* argv[])
{
    // Flush after every std::cout / std::cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    if (argc < 2)
    {
        std::cerr << "No command provided.\n";
        return EXIT_FAILURE;
    }

    std::string command = argv[1];

    if (command == "--version" || command == "-v")
    {
        std::cout << "Git version 0.0.2" << std::endl;
        return EXIT_SUCCESS;
    }

    if (command == "init")
    {
        try
        {
            std::filesystem::create_directory(".git");
            std::filesystem::create_directory(".git/objects");
            std::filesystem::create_directory(".git/refs");
            std::ofstream headFile(".git/HEAD");
            if (headFile.is_open())
            {
                headFile << "ref: refs/heads/main\n";
                headFile.close();
            }
            else
            {
                std::cerr << "Failed to create .git/HEAD file.\n";
                return EXIT_FAILURE;
            }
            std::cout << "Initialized git directory\n";
        }
        catch (std::filesystem::filesystem_error& e)
        {
            std::cerr << e.what() << '\n';
            return EXIT_FAILURE;
        }
    }

    else if (command == "cat-file")
    {
        if (argc < 4) // Ensure there are at least 4 arguments
        {
            std::cerr << "usage: git cat-file <type> <object>\n";
            return EXIT_FAILURE;
        }

        std::string flag = argv[2];
        std::string commitSHA_Hash = argv[3];

        handleCatCommand(flag, commitSHA_Hash);
    }

    else if (command == "hash-object")
    {
        String flag;
        String filePath;
        if (argc < 3)
        {
            std::cerr << "Give needed amount of parameters" << std::endl;
            return EXIT_FAILURE;
        }
        else if (argc < 4)
        {
            flag = "";
            filePath = argv[2];

            handleHashObject(flag, filePath);
            return EXIT_SUCCESS;
        }

        flag = argv[2];
        filePath = argv[3];

        std::cout << flag + "\t" << filePath << std::endl;

        handleHashObject(flag, filePath);

        EXIT_SUCCESS;
    }

    else
    {
        std::cerr << "Unknown command " << command << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}