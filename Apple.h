#include "PerennialCrop.h"

#ifndef APPLE_H
#define APPLE_H

class Apple: public PerennialCrop {
    public:
        Apple(int phase);
        std::string get_type();
        double HarvestMinigame() override;
};
#endif