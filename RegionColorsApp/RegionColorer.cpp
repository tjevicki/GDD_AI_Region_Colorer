#include "RegionColorer.h"
#include <iostream>
#include "ColorAssignmentException.h"

RegionColorer::RegionColorer(std::vector<std::string> ColorIds)
{
    this->ColorIds = ColorIds;
}

std::map<std::string, std::string>  RegionColorer::AssignColorsToRegions(std::vector<Region*> Regions)
{
    std::map<std::string, std::string> ColorAssignments = {};

    while (ColorAssignments.size() < Regions.size())
    {
        std::vector<Region*> UnassignedRegions = CalculateUnassignedRegions(&Regions, &ColorAssignments);
        
        Region* NextRegionForAssignment = SelectNextRegionForAssignment(&UnassignedRegions, &ColorAssignments);

        if (NextRegionForAssignment == nullptr)
        {
            throw ColorAssignmentException();
        }
        
        std::string SuitableColorId = PickColorForAssignment(NextRegionForAssignment, &UnassignedRegions, &ColorAssignments);
        ColorAssignments[NextRegionForAssignment->GetRegionId()] = SuitableColorId;
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

Region* RegionColorer::SelectNextRegionForAssignment(std::vector<Region*>* UnassignedRegions, std::map<std::string, std::string>* ColorAssignments)
{
    std::vector<Region*> MRVRegions = CalculateMRVRegions(UnassignedRegions, ColorAssignments);

    if (MRVRegions.empty())
    {
        return nullptr;
    }

    Region* RegionToAssign;
        
    if (MRVRegions.size() == 1)
    {
        RegionToAssign = MRVRegions[0];
    }
    else
    {
        RegionToAssign = GetRegionWithMostUnassignedNeighbours(&MRVRegions, ColorAssignments);
    }

    return RegionToAssign;
}

std::string RegionColorer::PickColorForAssignment(Region* Region, std::vector<::Region*>* UnassignedRegions, std::map<std::string, std::string>* ColorAssignments)
{
    const std::vector<std::string> AvailableColors = CalculateAvailableColors(Region, ColorAssignments);

    std::string SuitableColorId;
    if (AvailableColors.empty())
    {
        throw ColorAssignmentException();
    }
    if (AvailableColors.size() == 1)
    {
        SuitableColorId = AvailableColors[0];
    }
    else
    {
        // If there are multiple colors, choose the one which will rule out the least neighbouring values

        // Take each neighbour and calculate available colors
        std::map<std::string, std::vector<std::string>> AvailableNeighbourColors = {};
        for (const auto& NeighbourRegion : Region->GetNeighbouringRegions())
        {
            AvailableNeighbourColors[NeighbourRegion->GetRegionId()] = CalculateAvailableColors(NeighbourRegion, ColorAssignments);
        }
        
        // For each available color, count how many are there in neighbour available colors
        SuitableColorId = AvailableColors[0];
        unsigned int LeastColorCount = ColorIds.size();
        for (const auto& Color : AvailableColors)
        {
            unsigned int ColorCount = 0;
            for (const auto& NeighbourColorsPair : AvailableNeighbourColors) {
                for (const auto& NeighbourColor : NeighbourColorsPair.second)
                {
                    if (NeighbourColor == Color)
                    {
                        ColorCount++;
                    }
                }
            }

            // The one with lowest count wins - it rules out the least neighbouring available colors
            if (ColorCount < LeastColorCount)
            {
                SuitableColorId = Color;
                LeastColorCount = ColorCount;
            }
        }
    }

    return SuitableColorId;
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




