#include "performanceProfiler.h"

#include <Windows.h>
#include <stdio.h>
#include <time.h>

#include <string>
#include <map>



std::string dir;
LARGE_INTEGER Freq;
std::map<std::string, profileStruct> containor;
performanceProfiler PP;


void startProfile(std::string name)
{
    LARGE_INTEGER test;

    QueryPerformanceCounter(&test);
    if (containor.find(name) == containor.end())
    {
        profileStruct temp;
        temp.sum = 0;
        temp.min[0] = ULLONG_MAX;
        temp.min[1] = ULLONG_MAX;
        temp.max[0] = 0;
        temp.max[1] = 0;
        temp.count = 0;
        containor[name] = temp;
    }
    else if (containor[name].start.QuadPart != 0)
    { 
        std::string msg = "profile name overlapped : " + name;

        throw msg;
    }
    QueryPerformanceCounter(&(containor[name].start));
    
}
void endProfile(std::string name)
{
    if (containor[name].start.QuadPart == 0)
        return;

    LARGE_INTEGER end;
    QueryPerformanceCounter(&end);

    unsigned long long time = end.QuadPart - containor[name].start.QuadPart;
    if (containor[name].min[1] > time)
    {
        containor[name].min[1] = time;
        if (containor[name].min[0] > time)
        {
            containor[name].min[1] = containor[name].min[0];
            containor[name].min[0] = time;
        }
    }

    if (containor[name].max[1] < time)
    {
        containor[name].max[1] = time;
        if (containor[name].max[0] < time)
        {
            containor[name].max[1] = containor[name].max[0];
            containor[name].max[0] = time;
        }
    }

    containor[name].sum += time;
    containor[name].start.QuadPart = 0;
    containor[name].count++;
}
void clearProfile()
{
    containor.clear();
}
void setDirProfiles(std::string _dir)
{
    dir = _dir;
}
void writeProfiles()
{
    struct tm curr_tm;
    time_t t = time(0);
    localtime_s(&curr_tm, &t);

    FILE* file;
    std::string filename = (dir + "["
        + std::to_string(curr_tm.tm_year + 1900) + "."
        + std::to_string(curr_tm.tm_mon + 1) + "."
        + std::to_string(curr_tm.tm_mday) + "] "
        + std::to_string(curr_tm.tm_hour) + "-"
        + std::to_string(curr_tm.tm_min) + "-"
        + std::to_string(curr_tm.tm_sec)
        + ".csv"
        );



    fopen_s(&file, filename.c_str(), "wt");
    
    fprintf(file, "No,Name,Min(§Á),Average(§Á),Max(§Á),Call Count\n");

    int no = 0;
    for (auto item : containor)
    {
        fprintf(file, (
            std::to_string(no++) + ","
            + item.first + ","
            + std::to_string((double)item.second.min[1] / Freq.QuadPart) + ","
            + std::to_string((double)(item.second.sum - item.second.min[0] - item.second.max[0]) / item.second.count / Freq.QuadPart) + ","
            + std::to_string((double)item.second.max[1] / Freq.QuadPart) + ","
            + std::to_string(item.second.count) + "\n"
            ).c_str());
    }

    fclose(file);
}

performanceProfiler::performanceProfiler()
{
	QueryPerformanceFrequency(&Freq);
    dir = "";
}
performanceProfiler::~performanceProfiler()
{
    writeProfiles();
}





scopeProfiler::scopeProfiler(std::string _name) :name(_name)
{
    startProfile(name);
   
};
scopeProfiler::~scopeProfiler()
{
    endProfile(name);
};
