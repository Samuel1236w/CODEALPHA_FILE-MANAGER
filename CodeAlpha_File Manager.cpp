#include <iostream>
#include <filesystem>  // For directory and file operations
#include <fstream>     // For file handling
#include <string>

namespace fs = std::filesystem;

void listDirectory(const fs::path& currentPath) {
    std::cout << "\nContents of Directory: " << currentPath << "\n";
    for (const auto& entry : fs::directory_iterator(currentPath)) {
        std::cout << (entry.is_directory() ? "[DIR] " : "[FILE] ") << entry.path().filename().string() << "\n";
    }
}

void createDirectory(const fs::path& currentPath) {
    std::string dirName;
    std::cout << "Enter the name of the new directory: ";
    std::cin >> dirName;

    fs::path newDir = currentPath / dirName;
    if (fs::create_directory(newDir)) {
        std::cout << "Directory created successfully: " << newDir << "\n";
    } else {
        std::cout << "Error: Unable to create directory.\n";
    }
}

void copyFile(const fs::path& currentPath) {
    std::string sourceFile, destinationFile;
    std::cout << "Enter the name of the file to copy: ";
    std::cin >> sourceFile;
    std::cout << "Enter the destination path or filename: ";
    std::cin >> destinationFile;

    try {
        fs::copy(currentPath / sourceFile, currentPath / destinationFile);
        std::cout << "File copied successfully.\n";
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

void moveFile(const fs::path& currentPath) {
    std::string sourceFile, destinationFile;
    std::cout << "Enter the name of the file to move: ";
    std::cin >> sourceFile;
    std::cout << "Enter the destination path or filename: ";
    std::cin >> destinationFile;

    try {
        fs::rename(currentPath / sourceFile, currentPath / destinationFile);
        std::cout << "File moved successfully.\n";
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

int main() {
    fs::path currentPath = fs::current_path();  // Start in the current directory
    int choice;

    std::cout << "Welcome to the Basic File Manager!\n";

    do {
        std::cout << "\nCurrent Directory: " << currentPath << "\n";
        std::cout << "1. List Directory Contents\n";
        std::cout << "2. Create Directory\n";
        std::cout << "3. Copy File\n";
        std::cout << "4. Move File\n";
        std::cout << "5. Change Directory\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                listDirectory(currentPath);
                break;
            case 2:
                createDirectory(currentPath);
                break;
            case 3:
                copyFile(currentPath);
                break;
            case 4:
                moveFile(currentPath);
                break;
            case 5: {
                std::string newDir;
                std::cout << "Enter the directory to navigate to: ";
                std::cin >> newDir;
                fs::path newPath = currentPath / newDir;
                if (fs::exists(newPath) && fs::is_directory(newPath)) {
                    currentPath = newPath;
                    std::cout << "Changed directory to: " << currentPath << "\n";
                } else {
                    std::cout << "Error: Directory does not exist.\n";
                }
                break;
            }
            case 6:
                std::cout << "Exiting the File Manager. Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}


