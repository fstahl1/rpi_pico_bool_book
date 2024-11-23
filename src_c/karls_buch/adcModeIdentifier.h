#ifndef AdcModeIdentifier_h
#define AdcModeIdentifier_h

#include "abstractModeIdentifier.h"
#include "mcp3008.h"

class AdcModeIdentifier : public AbstractModeIdentifier {
    private:
        MCP3008 mcp3008;
       
    public:
        AdcModeIdentifier();
        void Initialize();
        Mode IdentifyMode();
        void PrintState();
};


#endif