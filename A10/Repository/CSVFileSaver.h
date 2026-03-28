#pragma once
#include "FileSaver.h"

class CSVFileSaver : public FileSaver
{
public:
    void save(vector<Tutorial>& tutorials, string& filename) override;
};