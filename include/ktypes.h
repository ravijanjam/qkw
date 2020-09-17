#ifndef KTYPES_H
#define KTYPES_H

#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <unordered_set>
#include <string>
#include <regex>
#include <functional>
#include <sqlite3.h>

#include <fmt/core.h>
#include <fmt/format.h>
#include <yaml.h>

#include <unistd.h>

using namespace std;

typedef map<string,string> MSS_t;
typedef unordered_set<char> CS_t;
typedef vector<string> VS_t;
typedef unordered_set<string> US_t;
typedef map<string,US_t> MUSS_t;
typedef vector<MSS_t> VMSS_t;
typedef YAML::Node YN_t;

#endif
