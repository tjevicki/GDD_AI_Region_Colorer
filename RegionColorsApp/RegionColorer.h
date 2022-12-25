#pragma once
#include <map>
#include <vector>

#include "Region.h"

class RegionColorer
{

private:
    std::vector<std::string> ColorIds;
    
public:
    RegionColorer(std::vector<std::string> ColorIds);
    
    // Takes a collection of Region objects, and number of different colors to be assigned to them
    // Outputs a dictionary of RegionId strings mapped to their color id.
    // Color ids start from 0
    std::map<std::string, std::string> AssignColorsToRegions(std::vector<Region*> Regions);

private:
    // Makes a sub-vector of all regions, which contains regions that have not yet been assigned a color
    // based on provided color assignments
    std::vector<Region*> CalculateUnassignedRegions(std::vector<Region*>* AllRegions, std::map<std::string, std::string>* ColorAssignments);

    // Makes a sub-vector of provided regions, which contains regions with minimum remaining color options
    std::vector<Region*> CalculateMRVRegions(std::vector<Region*>* Regions, std::map<std::string, std::string>* ColorAssignments);

    // Makes a vecter of all colors that can be assigned to the provided region so that it differs from all adjacent regions' colors
    std::vector<std::string> CalculateAvailableColors(Region* Region, std::map<std::string, std::string>* ColorAssignments);

    Region* GetRegionWithMostUnassignedNeighbours(std::vector<Region*>* Regions, std::map<std::string, std::string>* ColorAssignments);
};
