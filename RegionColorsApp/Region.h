#pragma once
#include <vector>

struct Region
{
public:
    Region(int RegionId, std::vector<Region> NeighbouringRegions);

private:
    int RegionId;
    std::vector<Region> NeighbouringRegions;

public:
    int GetRegionId();
    std::vector<Region> GetNeighbouringRegions();
    std::vector<Region> SetNeighbouringRegions();
};
