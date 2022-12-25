#include "RegionColorer.h"

#include <iostream>

RegionColorer::RegionColorer(std::vector<std::string> ColorIds)
{
    this->ColorIds = ColorIds;
}

std::map<std::string, std::string>  RegionColorer::AssignColorsToRegions(std::vector<Region*> Regions)
{
    std::cout << "Assigning " << ColorIds.size() << " colors to " << Regions.size() << " regions." << std::endl;

    // Create a map of assigned colors
    std::map<std::string, std::string> ColorAssignments = {};

    while (ColorAssignments.size() < Regions.size())
    {
        std::vector<Region*> UnassignedRegions = CalculateUnassignedRegions(&Regions, &ColorAssignments);
        std::vector<Region*> MRVRegions = CalculateMRVRegions(&UnassignedRegions, &ColorAssignments);

        Region* RegionToAssign;
        
        if (MRVRegions.empty())
        {
            // Throw a runtime exception
            return {};
        }
        
        if (MRVRegions.size() == 1)
        {
            RegionToAssign = MRVRegions[0];
        }
        else
        {
            RegionToAssign = GetRegionWithMostUnassignedNeighbours(&MRVRegions, &ColorAssignments);
        }
        
        std::cout << "Next region to assign: " << RegionToAssign->GetRegionId() << std::endl;
        
        //     Least constraining value:
        //       Once a region is selected, choose a color that will rule out the least adjacent region colors
        //       If there are multiple colors to choose from, choose a random color
        std::string SuitableColorId = CalculateAvailableColors(RegionToAssign, &ColorAssignments)[0];
        
        ColorAssignments[RegionToAssign->GetRegionId()] = SuitableColorId;

        std::cout << "Assigned color " << SuitableColorId << " to " << RegionToAssign->GetRegionId() << std::endl;
    }
    
    return ColorAssignments;
}

std::vector<Region*> RegionColorer::CalculateUnassignedRegions(std::vector<Region*>* AllRegions, std::map<std::string, std::string>* ColorAssignments)
{
    std::vector<Region*> UnassignedRegions = {};
    for (const auto& Region : *AllRegions)
    {
        if (ColorAssignments->count(Region->GetRegionId()) == 0)
        {
            UnassignedRegions.push_back(Region);
        }
    }

    return UnassignedRegions;
}

std::vector<Region*> RegionColorer::CalculateMRVRegions(std::vector<Region*>* Regions, std::map<std::string, std::string>* ColorAssignments)
{
    std::vector<Region*> MRVRegions = {};

    unsigned int MRV = ColorIds.size() + 1;
    for (const auto& Region : *Regions)
    {
        std::vector<std::string> AvailableColors = CalculateAvailableColors(Region, ColorAssignments);
        if (AvailableColors.size() < MRV)
        {
            MRV = AvailableColors.size();
            MRVRegions.clear();
            
        }

        MRVRegions.push_back(Region);
    }
    return *Regions;
}

std::vector<std::string> RegionColorer::CalculateAvailableColors(Region* Region, std::map<std::string, std::string>* ColorAssignments)
{
    std::vector<std::string> AvailableColors = {};

    for (std::string ColorId : ColorIds)
    {
        bool IsAssignedToAdjacentRegion = false;

        // Check if adjacent regions have been assigned this color
        for (const auto& AdjacentRegion : Region->GetNeighbouringRegions())
        {
            if (ColorAssignments->count(AdjacentRegion->GetRegionId()) > 0 && (*ColorAssignments)[AdjacentRegion->GetRegionId()] == ColorId)
            {
                IsAssignedToAdjacentRegion = true;
                break;
            }
        }
        
        if (!IsAssignedToAdjacentRegion)
        {
            AvailableColors.push_back(ColorId);
        }
    }
    
    return AvailableColors;
}

Region* RegionColorer::GetRegionWithMostUnassignedNeighbours(std::vector<Region*>* Regions, std::map<std::string, std::string>* ColorAssignments)
{
    Region* RegionWithMostUnassignedNeighbours = nullptr;
    
    int MostUnassignedNeighbours = 0;
    for (const auto& Region : *Regions)
    {
        int UnassignedNeighbours = 0;
        for (const auto& Neighbour : Region->GetNeighbouringRegions())
        {
            if (ColorAssignments->count(Neighbour->GetRegionId()) == 0)
            {
                UnassignedNeighbours += 1;
            }
        }

        if (UnassignedNeighbours > MostUnassignedNeighbours)
        {
            RegionWithMostUnassignedNeighbours = Region;
            MostUnassignedNeighbours = UnassignedNeighbours;
        }
    }

    if (RegionWithMostUnassignedNeighbours == nullptr)
    {
        RegionWithMostUnassignedNeighbours = (*Regions)[0];
    }

    return RegionWithMostUnassignedNeighbours;
}




