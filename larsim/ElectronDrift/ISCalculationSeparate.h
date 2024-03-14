////////////////////////////////////////////////////////////////////////
/// \file  ISCalculationSeparate.h
/// \brief Calculation of ionization electrons and scintillation photons
///        assuming there is no correlation between the two
///
///
/// \version $Id:  $
/// \author  wenzel@fnal.gov
////////////////////////////////////////////////////////////////////////
#ifndef IS_ISCALCULATION_H
#define IS_ISCALCULATION_H

#include "larcoreobj/SimpleTypesAndConstants/geo_vectors.h"

// forward declaration
namespace detinfo {
  class LArProperties;
  class DetectorProperties;
}
namespace fhicl {
  class ParameterSet;
}
namespace geo {
  class TPCID;
}
namespace sim {
  class SimEnergyDeposit;
  class LArG4Parameters;
}
namespace spacecharge {
  class SpaceCharge;
}

namespace detsim {

  class ISCalculationSeparate {
  public:
    explicit ISCalculationSeparate(fhicl::ParameterSet const& pset);

    struct Data {
      double energyDeposit;
      double numElectrons;
      double numPhotons;
    };
    Data CalculateIonizationAndScintillation(detinfo::DetectorPropertiesData const& detProp,
                                             sim::SimEnergyDeposit const& edep,
                                             geo::TPCID const& tpcid) const;
    double EFieldAtStep(double efield, sim::SimEnergyDeposit const& edep, geo::TPCID const& tpcid)
      const; //value of field with any corrections for this step

  private:
    double fRecombA;
    double fRecombk;
    double fModBoxA;
    double fModBoxB;
    bool fUseModBoxRecomb;
    double fGeVToElectrons; ///< from LArG4Parameters service

    double EFieldAtStep(detinfo::DetectorPropertiesData const& detProp,
                        sim::SimEnergyDeposit const& edep,
                        geo::TPCID const& tpcid) const;
    double EFieldAtStep(detinfo::DetectorPropertiesData const& detProp, 
                        float x, float y, float z, geo::TPCID const& tpcid) const;

    const detinfo::LArProperties* fLArProp;
    const spacecharge::SpaceCharge* fSCE;

    double CalculateIonization(detinfo::DetectorPropertiesData const& detProp,
                               sim::SimEnergyDeposit const& edep, 
                               geo::TPCID const& tpcid) const;
    double CalculateScintillation(sim::SimEnergyDeposit const& edep, 
                                  geo::TPCID const& tpcid) const;
  };
}
#endif // LARG4_ISCALCULATION_H
