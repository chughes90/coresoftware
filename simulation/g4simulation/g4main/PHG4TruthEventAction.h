#ifndef PHG4TruthEventAction_h
#define PHG4TruthEventAction_h

#include "PHG4EventAction.h"

#include <phool/PHCompositeNode.h>

#include <Geant4/G4ThreeVector.hh>
#include <Geant4/globals.hh>

#include <set>

class PHG4TruthInfoContainer;

class PHG4TruthEventAction: public PHG4EventAction
{

public:

  //! constructor
  PHG4TruthEventAction( void );

  //! destuctor
  virtual ~PHG4TruthEventAction( void ) {}

  void BeginOfEventAction(const G4Event*);

  void EndOfEventAction(const G4Event*);
  
  int ResetEvent(PHCompositeNode *);

  //! get relevant nodes from top node passed as argument
  void SetInterfacePointers( PHCompositeNode* );
  
  //! add id into track list
  void AddTrackidToWritelist( const G4int trackid);

 private:
    
  //! set of track ids to be written out
  std::set<G4int> writeList_;

  //! pointer to truth information container
  PHG4TruthInfoContainer* truthInfoList_;
};


#endif
