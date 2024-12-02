#include <Client.hpp>

int main(int argc, char* argv[])
{
    // Flush after every std::cout / std::cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    if (argc < 2)
    {
        String L = R"(
usage: git [-v | --version] [-h | --help] [-C <path>] [-c <name>=<value>]
[--exec-path[=<path>]] [--html-path] [--man-path] [--info-path]
[-p | --paginate | -P | --no-pager] [--no-replace-objects] [--no-lazy-fetch]
[--no-optional-locks] [--no-advice] [--bare] [--git-dir=<path>]
[--work-tree=<path>] [--namespace=<name>] [--config-env=<name>=<envvar>]
<command> [<args
These are common Git commands used in various situations:

start a working area (see also: git help tutorial)
    clone     Clone a repository into a new directory
    init      Create an empty Git repository or reinitialize an existing one

work on the current change (see also: git help everyday)
    add       Add file contents to the index
    mv        Move or rename a file, a directory, or a symlink
    restore   Restore working tree files
    rm        Remove files from the working tree and from the index

examine the history and state (see also: git help revisions)
    bisect    Use binary search to find the commit that introduced a bug
    diff      Show changes between commits, commit and working tree, etc
    grep      Print lines matching a pattern
    log       Show commit logs
    show      Show various types of objects
    status    Show the working tree status

grow, mark and tweak your common history
    backfill  Download missing objects in a partial clone
    branch    List, create, or delete branches
    commit    Record changes to the repository
    merge     Join two or more development histories together
    rebase    Reapply commits on top of another base tip
    reset     Reset current HEAD to the specified state
    switch    Switch branches
    tag       Create, list, delete or verify a tag object signed with GPG

collaborate (see also: git help workflows)
    fetch     Download objects and refs from another repository
    pull      Fetch from and integrate with another repository or a local branch
    push      Update remote refs along with associated objects

'git help -a' and 'git help -g' list available subcommands and some
concept guides. See 'git help <command>' or 'git help <concept>'
to read about a specific subcommand or concept.
See 'git help git' for an overview of the system.
)";
        std::cerr << "No command provided.\n";
        std::cout << L;

        return EXIT_FAILURE;
    }

    String command = argv[1];

    if (command == "--version" || command == "-v")
    {
        std::cout << "Git version 0.0.2. \n";
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
        if (argc < 4) // Ensure there are at least 4 arguments.
        {
            std::cerr << "usage: git cat-file <type> <object>\n";
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
            std::cerr << "Give needed amount of parameters" << std::endl;
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
        
        flag = argv[2];
        sha = "";
        if (argc < 4)
        {
            sha = flag; flag.clear();
            handleLSTree(flag,sha);
            return EXIT_SUCCESS;
        }
        sha = argv[3];
        handleLSTree(flag, sha);
        return EXIT_SUCCESS;
    }
    
    else
    {
        String L = R"(
            usage: git [-v | --version] [-h | --help] [-C <path>] [-c <name>=<value>]
            [--exec-path[=<path>]] [--html-path] [--man-path] [--info-path]
            [-p | --paginate | -P | --no-pager] [--no-replace-objects] [--no-lazy-fetch]
            [--no-optional-locks] [--no-advice] [--bare] [--git-dir=<path>]
            [--work-tree=<path>] [--namespace=<name>] [--config-env=<name>=<envvar>]
            <command> [<args>]

            These are common Git commands used in various situations:
            
            start a working area (see also: git help tutorial)
                clone     Clone a repository into a new directory
                init      Create an empty Git repository or reinitialize an existing one
            
            work on the current change (see also: git help everyday)
                add       Add file contents to the index
                mv        Move or rename a file, a directory, or a symlink
                restore   Restore working tree files
                rm        Remove files from the working tree and from the index
            
            examine the history and state (see also: git help revisions)
                bisect    Use binary search to find the commit that introduced a bug
                diff      Show changes between commits, commit and working tree, etc
                grep      Print lines matching a pattern
                log       Show commit logs
                show      Show various types of objects
                status    Show the working tree status
            
            grow, mark and tweak your common history
                backfill  Download missing objects in a partial clone
                branch    List, create, or delete branches
                commit    Record changes to the repository
                merge     Join two or more development histories together
                rebase    Reapply commits on top of another base tip
                reset     Reset current HEAD to the specified state
                switch    Switch branches
                tag       Create, list, delete or verify a tag object signed with GPG
            
            collaborate (see also: git help workflows)
                fetch     Download objects and refs from another repository
                pull      Fetch from and integrate with another repository or a local branch
                push      Update remote refs along with associated objects
            
            'git help -a' and 'git help -g' list available subcommands and some
            concept guides. See 'git help <command>' or 'git help <concept>'
            to read about a specific subcommand or concept.
            See 'git help git' for an overview of the system.
)";
        std::cerr << "Unknown command " << command << '\n';
        std::cout << L;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}