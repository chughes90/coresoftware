/**
 * @file trackbase/TrkrClusterv2.h
 * @author J. Osborn
 * @date March 2021
 * @brief Version 2 of TrkrCluster
 */
#ifndef TRACKBASE_TRKRCLUSTERV2_H
#define TRACKBASE_TRKRCLUSTERV2_H

#include "TrkrCluster.h"
#include "TrkrDefs.h"
#include <iostream>

class PHObject;

/**
 * @brief Version 2 of TrkrCluster
 *
 * This version of TrkrCluster contains Acts source link objects
 * as member variables, to join the Svtx and Acts worlds
 */
class TrkrClusterv2 : public TrkrCluster
{
 public:
 
  //! ctor
  TrkrClusterv2();

  //!dtor
  virtual ~TrkrClusterv2() {}
  // PHObject virtual overloads
  virtual void identify(std::ostream& os = std::cout) const override;
  virtual void Reset() override {}
  virtual int isValid() const override;
  virtual PHObject* CloneMe() const override { return new TrkrClusterv2(*this); }

  virtual void setClusKey(TrkrDefs::cluskey id) override { m_cluskey = id; }
  virtual TrkrDefs::cluskey getClusKey() const override { return m_cluskey; }
  
  
  //
  // cluster position
  //
  virtual float getX() const override { return m_pos[0]; }
  virtual void setX(float x) override { m_pos[0] = x; }
  virtual float getY() const override { return m_pos[1]; }
  virtual void setY(float y) override { m_pos[1] = y; }
  virtual float getZ() const override { return m_pos[2]; }
  virtual void setZ(float z) override { m_pos[2] = z; }
  virtual float getPosition(int coor) const override { return m_pos[coor]; }
  virtual void setPosition(int coor, float xi) override { m_pos[coor] = xi; }
  virtual void setGlobal() override { m_isGlobal = true; }
  virtual void setLocal() override { m_isGlobal = false; }
  virtual bool isGlobal() override { return m_isGlobal; }

  virtual float getLocalX() const override { return m_local[0]; }
  virtual void setLocalX(float loc0) override { m_local[0] = loc0; }
  virtual float getLocalY() const override { return m_local[1]; }
  virtual void setLocalY(float loc1) override { m_local[1] = loc1; }

  /// Acts functions, for Acts module use only
  virtual void setActsLocalError(unsigned int i, unsigned int j, float value) override;
  virtual float getActsLocalError(unsigned int i, unsigned int j) const override { return m_actsLocalErr[i][j]; }
  virtual TrkrDefs::subsurfkey getSubSurfKey() const override { return m_subsurfkey; }
  virtual void setSubSurfKey(TrkrDefs::subsurfkey id) override { m_subsurfkey = id; }

  //
  // cluster info
  //
  virtual unsigned int getAdc() const override { return m_adc; }
  virtual void setAdc(unsigned int adc) override { m_adc = adc; }
  virtual float getSize(unsigned int i, unsigned int j) const override;        //< get cluster dimension covar
  virtual void setSize(unsigned int i, unsigned int j, float value) override;  //< set cluster dimension covar

  virtual float getError(unsigned int i, unsigned int j) const override;        //< get cluster error covar
  virtual void setError(unsigned int i, unsigned int j, float value) override;  //< set cluster error covar
  
  //
  // convenience interface
  //
  virtual float getPhiSize() const override;
  virtual float getZSize() const override;

  virtual float getRPhiError() const override;
  virtual float getPhiError() const override;
  virtual float getZError() const override;

 protected:

  TrkrDefs::cluskey m_cluskey;  //< unique identifier within container
  TrkrDefs::subsurfkey m_subsurfkey; //< unique identifier for hitsetkey-surface maps
  float m_pos[3];               //< mean position x,y,z
  bool m_isGlobal;             //< flag for coord sys (true = global)
  unsigned int m_adc;           //< cluster sum adc (D. McGlinchey - Do we need this?)
  float m_size[6];              //< size covariance matrix (packed storage) (+/- cm^2)
  float m_err[6];               //< covariance matrix: rad, arc and z

  float m_local[2];             //< 2D local position [cm]
  float m_actsLocalErr[2][2];   //< 2D local error for Acts [cm]

  ClassDefOverride(TrkrClusterv2, 2)
};

#endif //TRACKBASE_TRKRCLUSTERV2_H
