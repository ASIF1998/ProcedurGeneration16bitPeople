//
//  Directory.cpp
//  ProcedurGeneration16bitPeople
//
//  Created by Асиф Мамедов on 08/12/2018.
//  Copyright © 2018 Asif Mamedov. All rights reserved.
//

#include <sys/types.h>
#include <dirent.h>

#include "Directory.hpp"

Directory::Directory(const string_view& directoryPath) noexcept :
    _directoryPath(directoryPath)
{
    DIR* dirp = opendir(directoryPath.data());
    struct dirent* dp;
    
    while ((dp = readdir(dirp)) != NULL) {
        _fileNames.push_back(dp->d_name);
    }
    
    closedir(dirp);
}

Directory::operator const vector<string>& () const noexcept
{
    return _fileNames;
}

const vector<string>& Directory::fileNames() const noexcept
{
    return _fileNames;
}

const string& Directory::directoryPath() const noexcept
{
    return _directoryPath;
}
