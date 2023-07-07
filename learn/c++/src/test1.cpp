#include <iostream>
#include <string>
#include <vector>
#include <dirent.h>

int main()
{
    std::string dir_path = "../pic"; // 替换为实际路径

    std::vector<std::string> images;

    DIR* dir = opendir(dir_path.c_str());
    if (dir != NULL)
    {
        struct dirent* entry;
        while ((entry = readdir(dir)) != NULL)
        {
            std::string file_name = entry->d_name;
            if (file_name.length() >= 4 && file_name.substr(file_name.length() - 4) == ".jpg")
            {
                images.push_back(dir_path + "/" + file_name);
            }
        }
        closedir(dir);
    }

    std::cout << "Found " << images.size() << " images in " << dir_path << std::endl;

    // 在这里对每张图片进行操作，例如打印文件名
    for (const auto& image : images)
    {
        std::cout << "Processing " << image << std::endl;
    }

    return 0;
}
