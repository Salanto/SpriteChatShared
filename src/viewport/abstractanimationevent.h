#ifndef ABSTRACTANIMATIONEVENT_H
#define ABSTRACTANIMATIONEVENT_H

#include "animationtypes.h"

class AbstractAnimationEvent
{
  public:
    virtual ~AbstractAnimationEvent() {}

    virtual AnimationTypes::AnimationEvent type() = 0;
};

#endif // ABSTRACTANIMATIONEVENT_H
