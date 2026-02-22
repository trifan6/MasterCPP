#pragma once
#include "Tutorial.h"
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class FileSaver
{
public:
    virtual ~FileSaver() = default;
    virtual void save(vector<Tutorial>& tutorials, string& filename) = 0;
};