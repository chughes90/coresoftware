#ifndef MICROMEGAS_MicromegasRawDataEvaluation_H
#define MICROMEGAS_MicromegasRawDataEvaluation_H

/*!
 * \file MicromegasRawDataEvaluation.h
 * \author Hugo Pereira Da Costa <hugo.pereira-da-costa@cea.fr>
 */

#include "MicromegasMapping.h"

#include <fun4all/SubsysReco.h>
#include <phool/PHObject.h>

#include <TTree.h>

#include <map>
#include <memory>
#include <string>

class PHCompositeNode;
class TFile;
class TH1;
class TH2;
class TProfile;

/// micromegas raw data decoder
class MicromegasRawDataEvaluation : public SubsysReco
{
  public:

  /// constructor
  MicromegasRawDataEvaluation( const std::string &name = "MicromegasRawDataEvaluation" );

  /// global initialization
  int Init(PHCompositeNode*) override;

  /// run initialization
  int InitRun(PHCompositeNode*) override;

  /// event processing
  int process_event(PHCompositeNode*) override;

  /// end of processing
  int End(PHCompositeNode*) override;

  /// output file name for evaluation histograms
  void set_evaluation_outputfile(const std::string &outputfile) {m_evaluation_filename = outputfile;}

  class Sample
  {
    public:
    /// packet
    unsigned int packet_id = 0;

    /// bco
    unsigned int bco = 0;
    
    /// checksum and checksum error
    unsigned int checksum = 0;
    unsigned int checksum_error = 0;

    /// fee
    unsigned short fee_id = 0;
    unsigned short layer = 0;
    unsigned short tile = 0;
    
    /// sampa channel and sampa address
    unsigned short sampa_address = 0;
    unsigned short sampa_channel = 0;
    
    /// channel id
    unsigned short channel = 0;
    
    /// physical strip id
    unsigned short strip = 0;
    
    /// absolute channel id, used to show all channels in a given plot
    unsigned short absolute_channel = 0;
    unsigned short sample = 0;
    unsigned short adc = 0;
    
    using List = std::vector<Sample>;
  };
    
  class Container: public PHObject
  {
    public:
    void Reset();
    int n_tagger = 0;
    int max_fee_count = 0;
    int n_waveforms = 0;
    Sample::List samples;
    ClassDef(Container,1)
  };

  private:
    
  // evaluation output filename
  std::string m_evaluation_filename = "MicromegasRawDataEvaluation.root";
  std::unique_ptr<TFile> m_evaluation_file;

  // mapping
  MicromegasMapping m_mapping;
  
  // tree
  TTree* m_evaluation_tree = nullptr;
  
  // main branch
  Container* m_container = nullptr;
  
  // map bco to waiveforms
  using bco_map_t = std::map<int,unsigned int>;
  bco_map_t m_bco_map;

};

#endif
