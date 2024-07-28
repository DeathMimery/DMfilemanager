#include <iostream>
#include <string>
#include <filesystem>

//Useless decorational code that awaits for any input
int pressAnyKey(){
std::cout << "Press any key to continue..." << std::endl;
getchar();
return 0;
}

//Wow, a logo output!
int greet(){
    system("clear");
       std::cout << "---------------------------" 
    << std::endl << "Welcome to DM file manager!" 
    << std::endl << "---------------------------" << std::endl;
    return 0;
}

//Outputs files in chosen directory
int dirListReturn(std::string dirPath){
    greet();
    std::cout << "Files in " << dirPath << " directory:" << std::endl;
    for (const auto & entry : std::filesystem::directory_iterator(dirPath)){
        std::cout << entry.path() << std::endl;
    }
    return 0;
}

//Asks for absolute file path and calls an output function
std::string newFilePath(std::string absolutePath){
    std::string absolutePathCheck;
    std::cout << "To finish the operation, enter '#'" << std::endl << "Enter directory path:" << std::endl;
    std::cin >> absolutePathCheck;
    if(absolutePathCheck != "#") {
        absolutePath = absolutePathCheck;
    }
    dirListReturn(absolutePath);
    return absolutePath;
}

//Asks for direction from current directory and calls an output function
std::string relativeFilePath(std::string relativePath){
    std::string relativePathAdd;
    while(relativePathAdd != "#"){
        std::cout << "To finish the operation, enter '#'" << std::endl << "To the previous directory: '..'" << std::endl << "Enter direction you want to go to, including slash(/)" << std::endl;
        std::cin >> relativePathAdd;
        if (relativePathAdd != "#"){
            if(relativePathAdd == ".."){
                
                    size_t pos = relativePath.find_last_of("/");
                    if (pos != std::string::npos) {
                        relativePath.erase(pos);
                        if(relativePath == "") relativePath = "/";
                    }
                
            } else {  
                if(relativePath.size() < 2) relativePath = "";              
                relativePath += relativePathAdd;
            }
        }
        dirListReturn(relativePath);
    }
    return relativePath;
}

//Just some test playground 
int testFeature(){
    std::string dir_path = "/Users/john/Desktop/my_dir...";

    size_t pos = dir_path.find_last_of("/");

    if (pos != std::string::npos) {
        dir_path.erase(pos + 1);
    }

    std::cout << dir_path << std::endl;
    return 0;
}

//Main function bullshit with options you know
int main()
{
    std::string dirName = "/home";
    int functionChoise;
    bool optionError = 0;

programLobby:

       std::cout << dirListReturn(dirName)
    << std::endl << "---------------------------" << std::endl; 
    if(optionError){ std::cout << "Wrong option, try again!" << std::endl; optionError = 0;}
       std::cout << "Choose option:"
    << std::endl << "1. Move from this directory"
    << std::endl << "2. Choose new absolute path"
    << std::endl << "9. test feature"
    << std::endl << "0. Close the program"
    << std::endl;
    
    std::cin >> functionChoise;

    switch (functionChoise)
    {

    case 1:

        dirName = relativeFilePath(dirName);
        goto programLobby;

    case 2:

        dirName = newFilePath(dirName);
        goto programLobby;

    case 9:
        testFeature();
        break;

    case 0:
        std::cout << "Ending process..." << std::endl;
        return 0;
        break;

    default:
        optionError = 1;
        goto programLobby;
    }
    goto programLobby;
    return 0;
}
