
#include "RegionColorer.h"
#include "Region.h"
#include <vector>

int main(int argc, char* argv[])
{
    RegionColorer* Colorer = new RegionColorer();

    // Create sample regions
    const auto SampleRegions = {
        Region(1, {}),
        Region(2, {}),
        Region(3, {}),
        Region(4, {}),
        Region(5, {}),
        Region(6, {})
    };
    
    std::map<Region, int> RegionsWithColors = Colorer->AssignColorsToRegions(SampleRegions, 3);
    return 0;
}
