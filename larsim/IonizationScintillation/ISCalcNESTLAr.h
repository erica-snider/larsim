////////////////////////////////////////////////////////////////////////
// Class:       ISCalcNESTLAr
// Plugin Type: Algorithm
// File:        ISCalcNESTLAr.cxx
// Description:
// Aug. 30 by Mu Wei
////////////////////////////////////////////////////////////////////////

#ifndef LARG4_ISCALCNESTLAr_H
#define LARG4_ISCALCNESTLAr_H

#include "larcoreobj/SimpleTypesAndConstants/geo_vectors.h"
#include "larsim/IonizationScintillation/ISCalc.h"

namespace geo {
  class GeometryCore;
  class TPCID;
}

namespace spacecharge {
  class SpaceCharge;
}

namespace CLHEP {
  class HepRandomEngine;
}

namespace larg4 {
  class ISCalcNESTLAr : public ISCalc {
  public:
    explicit ISCalcNESTLAr(CLHEP::HepRandomEngine& fEngine);

    // double EFieldAtStep(double efield,
    //                     sim::SimEnergyDeposit const& edep)
    //   override; //value of field with any corrections for this step
    geo::Vector_t EfieldVecAtPoint( double nomEfield, geo::Vector_t const& nomEfieldDir, 
                                    geo::Point_t const& point, geo::TPCID const& tpcid) const override;
    ISCalcData CalcIonAndScint(detinfo::DetectorPropertiesData const& detProp,
                               sim::SimEnergyDeposit const& edep,
                               geo::TPCID const& tpcid) override;

  private:
    CLHEP::HepRandomEngine& fEngine; // random engine
    const spacecharge::SpaceCharge* fSCE;
    const geo::GeometryCore* fGeo;

    int BinomFluct(int N0, double prob);
    double CalcElectronLET(double E);
  };
}
#endif // LARG4_ISCALCNESTLAr_H
