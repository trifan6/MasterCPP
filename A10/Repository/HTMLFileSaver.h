#pragma once
#include "FileSaver.h"

class HTMLFileSaver : public FileSaver
{
public:
    void save(vector<Tutorial>& tutorials, string& filename) override;
};