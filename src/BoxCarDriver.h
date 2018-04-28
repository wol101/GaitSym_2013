/*
 *  BoxCarDriver.h
 *  GaitSymODE
 *
 *  Created by Bill Sellers on Thu Feb 21 2013.
 *  Copyright (c) 2013 Bill Sellers. All rights reserved.
 *
 *  Uses a cyclic boxcar function to return a the value at a given time
 *
 */

#ifndef BOXCARDRIVER_H
#define BOXCARDRIVER_H

#include "Driver.h"

class BoxCarDriver : public Driver
{
public:
    BoxCarDriver();
    ~BoxCarDriver();

    void SetBoxCarParameters(dReal CycleTime, dReal Delay, dReal Width, dReal Height);

    dReal GetCycleTime() { return m_CycleTime; }
    dReal GetDelay() { return m_Delay; }
    dReal GetWidth() { return m_Width; }
    dReal GetHeight() { return m_Height; }

    dReal GetValue(dReal Time);

protected:
    dReal m_CycleTime;
    dReal m_Delay;
    dReal m_Width;
    dReal m_Height;
};

#endif // BOXCARDRIVER_H

