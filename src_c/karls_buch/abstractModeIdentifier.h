#ifndef ABSTRACT_MODE_IDENTIFIER_H
#define ABSTRACT_MODE_IDENTIFIER_H

#include "modes.h"

class AbstractModeIdentifier {
    public:
        virtual void Initialize() = 0;
        virtual Mode IdentifyMode() = 0;
        virtual void PrintState() = 0;
};

#endif