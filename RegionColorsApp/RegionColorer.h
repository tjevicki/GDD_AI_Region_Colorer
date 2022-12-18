#pragma once
#include <map>
#include <vector>

#include "Region.h"

class RegionColorer
{
public:
    // Takes a collection of Region objects.
    // Outputs a dictionary of Region objects mapped to their color id.
    // Color ids start from 0
    std::map<Region, int> AssignColorsToRegions(std::vector<Region> Regions, int NumberOfColors);
};
