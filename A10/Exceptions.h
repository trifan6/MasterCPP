#pragma once
#include <stdexcept>
#include <string>
using namespace std;

class RepositoryError : public runtime_error
{
public:
    explicit RepositoryError(const string& message) : runtime_error(message) {}
};

class ValidationError : public runtime_error
{
public:
    explicit ValidationError(const string& message) : runtime_error(message) {}
};

class ServiceError : public runtime_error
{
public:
    explicit ServiceError(const string& message) : runtime_error(message) {}
};

class UIError : public runtime_error
{
public:
    explicit UIError(const string& message) : runtime_error(message) {}
};