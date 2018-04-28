/*
 *  SliderJoint.h
 *  GaitSymODE
 *
 *  Created by Bill Sellers on 25/05/2012.
 *  Copyright 2012 Bill Sellers. All rights reserved.
 *
 */

#ifndef SLIDERJOINT_H
#define SLIDERJOINT_H

#include "Joint.h"

class SliderJoint: public Joint
{
public:
    SliderJoint(dWorldID worldID);
    ~SliderJoint();

    void SetSliderAxis(dReal x, dReal y, dReal z);
    void SetSliderAxis(const char *buf);

    void SetStartDistanceReference(dReal startDistanceReference);
    void SetJointStops(dReal loStop, dReal hiStop);
    void SetStopCFM(dReal cfm);
    void SetStopERP(dReal erp);
    void SetStopBounce(dReal bounce);
    void SetStopSpringDamp(dReal springConstant, dReal dampingConstant, dReal integrationStep);
    void SetStopSpringERP(dReal springConstant, dReal ERP, dReal integrationStep);

    void GetSliderAnchor(dVector3 result);
    void GetSliderAnchor2(dVector3 result);
    void GetSliderAxis(dVector3 result);

    dReal GetSliderDistance();
    dReal GetSliderDistanceRate();

    virtual void Update();
    virtual void Dump();

#ifdef USE_OPENGL
    virtual void Draw();
#endif

protected:

    dReal m_StartDistanceReference;
};

#endif // SLIDERJOINT_H
