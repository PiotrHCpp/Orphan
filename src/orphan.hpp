#pragma once

#include <string>

void removeFrontSpaces(std::string& line);
void removeSpacesOnTheEnd(std::string& line);
void removeMultipleSpaces(std::string& line);
void insertHardspacesAfterOrphans(std::string& line);
void insertHardSpacesAfterSurnames(std::string& line);
