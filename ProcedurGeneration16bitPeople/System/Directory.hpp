//
//  Directory.hpp
//  ProcedurGeneration16bitPeople
//
//  Created by Асиф Мамедов on 08/12/2018.
//  Copyright © 2018 Asif Mamedov. All rights reserved.
//

#ifndef Directory_hpp
#define Directory_hpp

#include <string>
#include <string_view>

#include <vector>

using namespace std;

class Directory
{
public:
    
    /**
     * Конструктор.
     *
     * @param directoryPath путь до директории
     */
    Directory(const string_view& directoryPath) noexcept;
    
    operator const vector<string>& () const noexcept;
    const vector<string>& fileNames() const noexcept;
    
    const string& directoryPath() const noexcept;
    
private:
    vector<string> _fileNames;
    string _directoryPath;
};

#endif /* Directory_hpp */
