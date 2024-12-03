#include <Client.hpp>

int main(int argc, char* argv[])
{
    // Flush after every std::cout / std::cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    if (argc < 2)
    {
        std::cerr << "No command provided.\n";
        std::cout << DefaultReturnBack();
        return EXIT_FAILURE;
    }

    String command = argv[1];

    if (command == "--version" || command == "-v")
    {
        std::cout << "Git version 0.0.3 \n";
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
        catch (fs::filesystem_error& e)
        {
            std::cerr << e.what() << '\n';
            return EXIT_FAILURE;
        }
    }

    else if (command == "cat-file")
    {
        if (!fs::exists(".git"))
        {
            std::cout << "fatal: not a git repository (or any of the parent directories): .git";
            return EXIT_FAILURE;
        }
        if (argc < 3) // Ensure there are at least 4 arguments.
        {
            std::cerr << CatCommandAvailable();
            return EXIT_FAILURE;
        }
        if (argc < 4)
        {
            std::cout << "fatal: only two arguments allowed in <type> <object> mode, not 1\n" << std::endl;
            std::cerr << CatCommandAvailable();
            return EXIT_FAILURE;
        }

        String flag = argv[2];
        String commitSHA_Hash = argv[3];

        handleCatCommand(flag, commitSHA_Hash);
        return EXIT_SUCCESS;
    }

    else if (command == "hash-object")
    {
        String flag = "";
        String filePath = "";
        if (argc < 3)
        {
            return EXIT_FAILURE;
        }

        flag = argv[2];
        filePath = "";
        if (argc < 4)
        {
            filePath = flag; flag.clear();
            handleHashObject(flag, filePath);
            return EXIT_SUCCESS;
        }

        filePath = argv[3];
        handleHashObject(flag, filePath);
        EXIT_SUCCESS;
    }
    
    else if (command == "ls-tree")
    {
        String flag = "";
        String sha = "";
        if (argc < 3)
        {   std::cout << "Not enough!!";
            return EXIT_FAILURE;
        }
        else if (argc == 3)
        {
            flag = argv[2];
            sha = "";
            sha = flag; flag.clear();
            handleLSTree(flag, sha);
            return EXIT_SUCCESS;
        }
        else
        {
            flag = argv[2];
            sha = argv[3];
            handleLSTree(flag, sha);
            return EXIT_SUCCESS;
        }
    }
    
    else
    {
        std::cerr << "Unknown command " << command << '\n';
        std::cout << DefaultReturnBack();
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}