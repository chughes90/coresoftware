#ifndef __CALOEVALUATOR_H__
#define __CALOEVALUATOR_H__

#include <fun4all/SubsysReco.h>
#include <phool/PHCompositeNode.h>

#include <string>
#include <stdint.h>
#include <TString.h>

class PHCompositeNode;
class PHG4HitContainer;
class PHG4TruthInfoContainer;
class Fun4AllHistoManager;
class TH1F;
class TTree;
class SvtxEvalStack;
class PHG4Particle;
class RawTowerGeom;
class RawTowerContainer;
class SvtxTrack;

/// \class QAG4SimulationCalorimeter
class QAG4SimulationCalorimeter : public SubsysReco
{

public:

  enum enu_flags
  {
    kProcessG4Hit = 1 << 1, kProcessTower = 1 << 2, kProcessCluster = 1 << 3,

    kDefaultFlag = kProcessG4Hit | kProcessTower
  };

  QAG4SimulationCalorimeter(std::string calo_name, enu_flags flags = kDefaultFlag);
  virtual
  ~QAG4SimulationCalorimeter();

  int
  Init(PHCompositeNode *topNode);
  int
  InitRun(PHCompositeNode *topNode);
  int
  process_event(PHCompositeNode *topNode);
  int
  End(PHCompositeNode *topNode);

  uint32_t
  get_flags() const
  {
    return _flags;
  }

  void
  set_flags(enu_flags flags)
  {
    _flags = (uint32_t) flags;
  }

  void
  set_flag(enu_flags flag)
  {
    _flags |= (uint32_t) flag;
  }

  bool
  flag(enu_flags flag)
  {
    return _flags & flag;
  }

  void
  reset_flag(enu_flags flag)
  {
    _flags &= ~(uint32_t) flag;
  }

  float
  get_mag_field() const
  {
    return _magfield;
  }
  void
  set_mag_field(float magfield)
  {
    _magfield = magfield;
  }

  //! common prefix for QA histograms
  std::string get_histo_prefix();

private:

  int
  Init_G4Hit(PHCompositeNode *topNode);
  int
  process_event_G4Hit(PHCompositeNode *topNode);

  int
  Init_Tower(PHCompositeNode *topNode);
  int
  process_event_Tower(PHCompositeNode *topNode);

//  int
//  Init_MCPhoton(PHCompositeNode *topNode);
//  int
//  process_event_MCPhoton(PHCompositeNode *topNode);

  SvtxEvalStack * _eval_stack;

  //! to be retired with system interface
  double _magfield;

  std::string _calo_name;
  uint32_t _flags;
  unsigned long _ievent;

  PHG4HitContainer* _calo_hit_container;
  PHG4HitContainer* _calo_abs_hit_container;
  PHG4TruthInfoContainer* _truth_container;
};

#endif // __CALOEVALUATOR_H__
