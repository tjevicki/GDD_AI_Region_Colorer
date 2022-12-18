#include "Region.h"

Region::Region(int RegionId, std::vector<Region> NeighbouringRegions)
{
    this->RegionId = RegionId;
    this->NeighbouringRegions = NeighbouringRegions;
}

int Region::GetRegionId()
{
    return RegionId;
}



