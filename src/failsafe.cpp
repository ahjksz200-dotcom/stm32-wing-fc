#include "failsafe.h"

bool failsafeActive() {
    return rcLost();
}
