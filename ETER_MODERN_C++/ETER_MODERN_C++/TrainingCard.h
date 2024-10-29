#ifndef TRAININGCARD_H
#define TRAININGCARD_H

#include "Card.h"

class TrainingCard : public Card {
public:
    TrainingCard(int value, const std::string& type = "training");
};

#endif // TRAININGCARD_H
