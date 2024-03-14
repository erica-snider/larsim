////////////////////////////////////////////////////////////////////////
// Class:       ISCalc
// Plugin Type: Algorithm
// File:        ISCalc.h and ISCalc.cxx
// Description: Interface to the ion and scintillation calculation algorithm
// Input: 'sim::SimEnergyDeposit'
// Output: number of photons and electrons
// Spet.16 by Mu Wei
////////////////////////////////////////////////////////////////////////

#ifndef LARG4_ISCALC_H
#define LARG4_ISCALC_H

#include "larcoreobj/SimpleTypesAndConstants/geo_vectors.h"

namespace detinfo {
  class DetectorPropertiesData;
  class LArProperties;
}

namespace geo {
  class TPCID;
}

namespace sim {
  class SimEnergyDeposit;
}

namespace larg4 {
  struct ISCalcData {
    double energyDeposit;           // total energy deposited in the step
    double numElectrons;            // number of ionization electrons for this step
    double numPhotons;              // number of scintillation photons for this step
    double scintillationYieldRatio; // liquid argon scintillation yield ratio
  };

  class ISCalc {
  private:
    const detinfo::LArProperties* fLArProp;

  public:
    ISCalc();
    virtual ~ISCalc() = default;
    virtual ISCalcData CalcIonAndScint(detinfo::DetectorPropertiesData const& detProp,
                                       sim::SimEnergyDeposit const& edep,
                                       geo::TPCID const& tpcid) = 0;
    
    // Magnitude of Efield at this step with any space charge corrections
    // virtual double EFieldAtStep(
    //   double efield,
    //   sim::SimEnergyDeposit const& edep) = 0; 
    
    // E-field with SCE corrections (if enabled) at a specified position. TPC id must be known
    // Pass invalid TPC id for points outside any TPC.
    // virtual double EfieldAtStep( double nomEfield, geo::Vector_t const& nomEfieldDir, 
    //                              sim::SimEnergyDeposit const& edep, 
    //                              geo::TPCID const& tpcid) const = 0;
    virtual geo::Vector_t EfieldVecAtPoint(double nomEfield, geo::Vector_t const& nomEfieldDir,
                                geo::Point_t const& point, geo::TPCID const& tpcid) const = 0;
    // virtual geo::Vector_t EfieldVecAtStep(double nomEfield, geo::Vector_t const& nomEfieldDir,
    //                              geo::TPCID const& tpcid) const = 0;
    double GetScintYield(sim::SimEnergyDeposit const& edep, bool prescale);
    double GetScintYieldRatio(sim::SimEnergyDeposit const& edep);
  };
}
#endif // LARG4_ISCALC_H
