#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

#include <sys/types.h>
#include <dirent.h>

std::vector<std::string> getDirFiles(const std::string &pathname)
{
  std::vector<std::string> files;
  struct dirent **list = NULL;
  std::string dirName = pathname;
  int filesCount = scandir(dirName.c_str(), &list, NULL, NULL);
  std::cout << "filesCount: " << filesCount << std::endl;

  if (filesCount == -1) {
    std::cout<< "Cannot read files of directory: " << dirName << std::endl;;
  }
  for (int i = 0; i < filesCount; i++) {
    std::string fileName = list[i]->d_name;
    std::cout << "Found file: " << fileName << std::endl;
    if (fileName != "." && fileName != "..") {
      files.push_back(fileName);
    }
    free(list[i]);
  }
  free(list);
  std::sort(files.begin(), files.end());
  return files;
}

int main(int argc, char **argv)
{
  if (argc != 2) {
    std::cout << "Folder not given as argument" << std::endl;
    return EXIT_FAILURE;
  }

  std::vector<std::string> files;
  files = getDirFiles(argv[1]);
  std::cout << "The folder contains:" << std::endl;
  for (int i = 0; i < files.size(); i++) {
    std::cout << files[i] << std::endl;
  }

  std::cout << "The end" << std::endl;
  return EXIT_SUCCESS;
}