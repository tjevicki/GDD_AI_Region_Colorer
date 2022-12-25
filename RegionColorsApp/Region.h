#pragma once
#include <string>
#include <vector>

struct Region
{
public:
    Region(std::string RegionId, std::vector<Region*> NeighbouringRegions);

private:
    std::string RegionId;
    std::vector<Region*> NeighbouringRegions;

public:
    std::string GetRegionId();
    std::vector<Region*> GetNeighbouringRegions();
    void SetNeighbouringRegions(std::vector<Region*> NewNeighbouringRegions);
};
