/*
 *  FloatingHingeJoint.cpp
 *  GaitSymODE
 *
 *  Created by Bill Sellers on 30/12/2006.
 *  Copyright 2006 Bill Sellers. All rights reserved.
 *
 */

#include <ode/ode.h>

#include <iostream>
#ifdef MALLOC_H_NEEDED
#include <malloc.h>
#endif

#include "FloatingHingeJoint.h"

#include "PGDMath.h"
#include "DataFile.h"
#include "Simulation.h"
#include "Body.h"

// Simulation global
extern Simulation *gSimulation;
#ifdef USE_OPENGL
#include "FacetedConicSegment.h"
extern int gAxisFlag;
extern std::string gOBJName;
#endif


FloatingHingeJoint::FloatingHingeJoint(dWorldID worldID)
{
    m_JointID = dJointCreateFloatingHinge(worldID, 0);
    dJointSetData(m_JointID, this);

    dJointSetFeedback(m_JointID, &m_JointFeedback);
    m_StartAngleReference = 0;
}

void FloatingHingeJoint::SetFloatingHingeAxis(dReal x, dReal y, dReal z)
{
    dJointSetFloatingHingeAxis(m_JointID, x, y, z);
}

// parses the position allowing a relative position specified by BODY ID
// x y z - world coordinates
// bodyName x y z - position relative to bodyName local coordinate system
void
FloatingHingeJoint::SetFloatingHingeAxis(const char *buf)
{
        int i;
    int l = strlen(buf);
    char *lBuf = (char *)alloca((l + 1) * sizeof(char));
    char **lBufPtrs = (char **)alloca(l * sizeof(char *));
    dVector3 pos, result;

    strcpy(lBuf, buf);
        int count = DataFile::ReturnTokens(lBuf, lBufPtrs, l);
        if (count < 3)
    {
        std::cerr << "FloatingHingeJoint::SetFloatingHingeAxis\n";
        return; // error condition
    }

        if (isalpha((int)*lBufPtrs[0]) == 0)
        {
                for (i = 0; i < 3; i++) pos[i] = strtod(lBufPtrs[i], 0);
        dJointSetFloatingHingeAxis(m_JointID, pos[0], pos[1], pos[2]);
                return;
        }

        if (count < 4)
    {
        std::cerr << "Error in FloatingHingeJoint::SetFloatingHingeAxis\n";
        return; // error condition
    }
        Body *theBody = gSimulation->GetBody(lBufPtrs[0]);
        if (theBody == 0)
    {
        if (strcmp(lBufPtrs[0], "World") == 0)
        {
            for (i = 0; i < 3; i++) pos[i] = strtod(lBufPtrs[i + 1], 0);
            dJointSetFloatingHingeAxis(m_JointID, pos[0], pos[1], pos[2]);
            return;
        }
        else
        {
            std::cerr << "Error in FloatingHingeJoint::SetFloatingHingeAxis\n";
            return; // error condition
        }
    }
    for (i = 0; i < 3; i++) pos[i] = strtod(lBufPtrs[i + 1], 0);
    dBodyVectorToWorld(theBody->GetBodyID(), pos[0], pos[1], pos[2], result);
    dJointSetFloatingHingeAxis(m_JointID, result[0], result[1], result[2]);
}

void FloatingHingeJoint::GetFloatingHingeAxis(dVector3 result)
{
    dJointGetFloatingHingeAxis(m_JointID, result);
}

dReal FloatingHingeJoint::GetFloatingHingeAngle()
{
    return dJointGetFloatingHingeAngle(m_JointID) + m_StartAngleReference;
}

dReal FloatingHingeJoint::GetFloatingHingeAngleRate()
{
    return dJointGetFloatingHingeAngleRate(m_JointID);
}

void FloatingHingeJoint::SetStartAngleReference(dReal startAngleReference)
{
    m_StartAngleReference = startAngleReference;
}

void FloatingHingeJoint::SetJointStops(dReal loStop, dReal hiStop)
{
    if (loStop >= hiStop) throw(__LINE__);

    // correct for m_StartAngleReference
    loStop -= m_StartAngleReference;
    hiStop -= m_StartAngleReference;

    if (loStop < -M_PI) loStop = -dInfinity;
    if (hiStop > M_PI) hiStop = dInfinity;

    // note there is safety feature that stops setting incompatible low and high
    // stops which can cause difficulties. The safe option is to set them twice.

    dJointSetFloatingHingeParam (m_JointID, dParamLoStop, loStop);
    dJointSetFloatingHingeParam (m_JointID, dParamHiStop, hiStop);
    dJointSetFloatingHingeParam (m_JointID, dParamLoStop, loStop);
    dJointSetFloatingHingeParam (m_JointID, dParamHiStop, hiStop);
}

#ifdef USE_OPENGL
void FloatingHingeJoint::Draw()
{
    if (m_Visible == false) return;

    // perform late initialisation
    if (m_FirstDraw)
    {
        m_FirstDraw = false;
        m_PhysRep = new FacetedConicSegment(m_AxisSize[0] * 2, m_AxisSize[0] / 10, m_AxisSize[0] / 10, 128, 0, 0, -m_AxisSize[0]);
        m_PhysRep->SetColour(m_Colour);
    }

    if (gAxisFlag)
    {
        gOBJName = m_Name;

        dVector3 axis;
        const dReal *anchor = dBodyGetPosition(GetBody(0));
        dJointGetFloatingHingeAxis(m_JointID, axis);

        m_PhysRep->SetColour(m_Colour);
        m_PhysRep->SetDisplayRotationFromAxis(axis[0], axis[1], axis[2], false);
        m_PhysRep->SetDisplayPosition(anchor[0], anchor[1], anchor[2]);
        m_PhysRep->Draw();

    }
}
#endif

