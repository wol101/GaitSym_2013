/*
 *  SwingClearanceAbortReporter.h
 *  GaitSymODE
 *
 *  Created by Bill Sellers on 26/04/2011.
 *  Copyright 2011 Bill Sellers. All rights reserved.
 *
 */

#ifndef SWINGCLEARANCEABORTREPORTER_H
#define SWINGCLEARANCEABORTREPORTER_H

#include "PositionReporter.h"
#include "PGDMath.h"

class SwingClearanceAbortReporter : public PositionReporter
{
public:
    SwingClearanceAbortReporter();

    enum axis {x, y, z};

    void SetHeightThreshold(dReal heightThreshold) { m_heightThreshold = heightThreshold; }
    void SetVelocityThreshold(dReal velocityThreshold) { m_velocityThreshold = velocityThreshold; }
    void SetUpAxis(const char *upAxis);
    void SetUpAxis(axis upAxis) { m_upAxis = upAxis; }
    void SetDirectionAxis(dReal x, dReal y, dReal z);
    void SetDirectionAxis(const char *buf);

    virtual bool ShouldAbort();
    virtual void Dump();

protected:

    dReal m_heightThreshold;
    dReal m_velocityThreshold;
    axis m_upAxis;
    bool m_useDirectionAxis;
    pgd::Vector m_directionAxis;
    dReal m_velocity;
    dReal m_height;


};

#endif // SWINGCLEARANCEABORTREPORTER_H
