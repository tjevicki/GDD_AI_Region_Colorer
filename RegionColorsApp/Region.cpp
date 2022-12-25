#include "Region.h"

Region::Region(std::string RegionId, std::vector<Region*> NeighbouringRegions)
{
    this->RegionId = RegionId;
    this->NeighbouringRegions = NeighbouringRegions;
}

std::string Region::GetRegionId()
{
    return RegionId;
}

std::vector<Region*> Region::GetNeighbouringRegions()
{
    return NeighbouringRegions;
}

void Region::SetNeighbouringRegions(std::vector<Region*> NewNeighbouringRegions)
{
    this->NeighbouringRegions = NewNeighbouringRegions;
}





