
#include "RegionColorer.h"
#include "Region.h"
#include <vector>

int main(int argc, char* argv[])
{
    RegionColorer* Colorer = new RegionColorer({"Red", "Green", "Blue"});

    Region* WesternAustralia = new Region("WesternAustralia", {});
    Region* NorthernTerritory = new Region("NorthernTerritory", {});
    Region* SouthernAustralia = new Region("SouthAustralia", {});
    Region* Queensland = new Region("Queensland", {});
    Region* NewSouthWales = new Region("NewSouthWales", {});
    Region* Victoria = new Region("Victoria", {});
    Region* Tasmania = new Region("Tasmania", {});
    
    // Create sample regions
    std::vector<Region*> SampleRegions = {
        WesternAustralia,
        NorthernTerritory,
        SouthernAustralia,
        Queensland,
        NewSouthWales,
        Victoria,
        Tasmania
    };

    // Assign constraints (neighbouring regions)
    WesternAustralia->SetNeighbouringRegions(std::vector<Region*> { NorthernTerritory, SouthernAustralia });
    NorthernTerritory->SetNeighbouringRegions(std::vector<Region*> { WesternAustralia, SouthernAustralia, Queensland });
    SouthernAustralia->SetNeighbouringRegions(std::vector<Region*> { WesternAustralia, NorthernTerritory, Queensland, NewSouthWales, Victoria });
    Queensland->SetNeighbouringRegions(std::vector<Region*> { NorthernTerritory, SouthernAustralia, NewSouthWales });
    NewSouthWales->SetNeighbouringRegions(std::vector<Region*> { Queensland, SouthernAustralia, Victoria });
    Victoria->SetNeighbouringRegions(std::vector<Region*> { NewSouthWales, SouthernAustralia });
    Tasmania->SetNeighbouringRegions(std::vector<Region*> {});
    
    std::map<std::string, std::string> RegionsWithColors = Colorer->AssignColorsToRegions(SampleRegions);
    return 0;
}
