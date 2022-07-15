#pragma once

#include <Windows.h>
#include <string>

struct profileStruct
{
    LARGE_INTEGER start;

    unsigned long long int sum;
    unsigned long long int min[2];
    unsigned long long int max[2];

    unsigned long long int count;
};

class profilerException : public std::exception {
public:
    profilerException(const char* msg) {
        strcpy_s(message, 256, msg);
    }
    char* what() {
        return message;
    }

private:
    char message[256];
};

class performanceProfiler 
{
public:
    performanceProfiler();
    ~performanceProfiler();

};


class scopeProfiler
{
public:
    scopeProfiler(std::string _name);
    ~scopeProfiler();

private:
    std::string name;
};


void startProfile(std::string name);
void endProfile(std::string name);
void clearProfile();

void setDirProfiles(std::string _dir);
void writeProfiles();
