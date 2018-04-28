/*
 *  MAMuscleComplete.h
 *  GaitSymODE
 *
 *  Created by Bill Sellers on 03/03/2007.
 *  Copyright 2006 Bill Sellers. All rights reserved.
 *
 */

// MAMuscleComplete - implementation of an Minetti & Alexander style
// muscle based on the StrapForce class

// Minetti & Alexander, J. theor Biol (1997) 186, 467-476

// Added extra terms to allow a serial and parallel spring element
// plus length tension stuff too


#ifndef MAMuscleComplete_h
#define MAMuscleComplete_h

#include "Muscle.h"

class Strap;
class MAMuscle;
class DampedSpringMuscle;
class SimpleStrap;
class Filter;

class MAMuscleComplete : public Muscle
{
public:
    enum StrainModel
    {
        linear = 0,
        square
    };

    // this struct contains all the paramers required for the CalculateForceError function
    struct CalculateForceErrorParams
    {
        // fixed input parameters
        dReal spe; // slack length parallel element (m)
        dReal epe; // elastic constant parallel element (N/m)
        dReal dpe; // damping constant parallel element (N/m)
        StrainModel smpe; // strain model for parallel element
        dReal sse; // slack length serial element (m)
        dReal ese; // elastic constant serial element (N/m)
        dReal dse; // damping constant serial element (N/m)
        StrainModel smse; // strain model for serial element
        dReal k; // shape constant
        dReal vmax; // maximum shortening velocity (m/s)
        dReal fmax; // maximum isometric force (N)
        dReal width; // relative width of length/tension peak

        // variable input parameters
        dReal alpha; // proportion of muscle activated
        dReal timeIncrement; // inegration step size for simulation (s)
        dReal len; // length of the whole element (m)
        dReal v; // contraction velocity of the whole element (m/s)
        dReal lastlpe; // last calculated lpe value (m)

        // output parameters
        dReal fce; // contractile force (N)
        dReal lpe; // contractile and parallel length (m)
        dReal fpe; // parallel element force (N)
        dReal lse; // serial length (m)
        dReal fse; // serial element force (N)
        dReal vce; // contractile element velocity (m/s)
        dReal vse; // serial element velocity (m/s)
        dReal targetFce; // fce calculated from elastic elements (N)
        dReal f0; // length corrected fmax (N)
        dReal err; // error term in lpe (m)
    };

    MAMuscleComplete(Strap *strap);
    ~MAMuscleComplete();

    void SetSerialElasticProperties(dReal serialStrainAtFmax, dReal serialStrainRateAtFmax, dReal tendonLength, MAMuscleComplete::StrainModel serialStrainModel);
    void SetParallelElasticProperties(dReal parallelStrainAtFmax, dReal serialStrainRateAtFmax, dReal parallelElementLength, MAMuscleComplete::StrainModel parallelStrainModel);
    void SetMuscleProperties(dReal vMax, dReal Fmax, dReal K, dReal Width);
    void SetActivationKinetics(bool activationKinetics, dReal akFastTwitchProportion, dReal akTActivationA, dReal akTActivationB, dReal akTDeactivationA, dReal akTDeactivationB);
    void SetInitialFibreLength(dReal initialFibreLength) { m_Params.lastlpe = initialFibreLength; }
    void SetActivationRate(dReal activationRate) { m_ActivationRate = activationRate; }
    void SetStartActivation(dReal startActivation) { m_Params.alpha = startActivation; }
    void SetMinimumActivation(dReal minimumActivation) { m_MinimumActivation = minimumActivation; }

    virtual dReal GetMetabolicPower();

    virtual void SetActivation(dReal activation, dReal timeIncrement);
    virtual dReal GetActivation() { return m_Params.alpha; };

    dReal GetStimulation() { return m_Stim; };

    dReal GetFCE() { return m_Params.fce; } // contractile force (N)
    dReal GetLPE() { return m_Params.lpe; } // contractile and parallel length (m)
    dReal GetFPE() { return m_Params.fpe; } // parallel element force (N)
    dReal GetLSE() { return m_Params.lse; } // serial length (m)
    dReal GetFSE() { return m_Params.fse; } // serial element force (N)
    dReal GetVCE() { return m_Params.vce; } // contractile element velocity (m/s)
    dReal GetVPE() { return m_Params.vce; } // parallel element velocity (m/s)
    dReal GetVSE() { return m_Params.vse; } // serial element velocity (m/s)
    dReal GetESE(); // energy serial element
    dReal GetEPE(); // energy parallel element
    dReal GetPSE() { return GetVSE() * -m_Params.fse; } // power serial element
    dReal GetPPE() { return GetVPE() * -m_Params.fpe; } // power parallel element
    dReal GetPCE() { return GetVCE() * -m_Params.fce; } // power contractile element
    double GetSSE() { return m_Params.sse; };
    double GetSPE() { return m_Params.spe; };

    virtual void Dump();
    virtual void LateInitialisation();

protected:

    dReal m_Stim;
    bool m_ActivationKinetics;
    dReal m_ft;
    dReal m_tact;
    dReal m_tdeact;
    dReal m_ActivationRate;
    dReal m_serialStrainAtFmax;
    dReal m_serialStrainRateAtFmax;
    dReal m_parallelStrainAtFmax;
    dReal m_parallelStrainRateAtFmax;
    dReal m_MinimumActivation;

    CalculateForceErrorParams m_Params;
    dReal m_Tolerance;
    int m_MaxIter;
};






#endif // MAMuscleComplete_h
