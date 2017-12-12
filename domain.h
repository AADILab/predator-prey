#ifndef _DOMAIN_H
#define _DOMAIN_H

#include <string>
#include <iostream>
#include <vector>
using std::vector;

class Position
{
    public:
        int x;
        int y;
        bool operator==(const Position&);
};

typedef struct Predator
{
    Position pos;
    int index;
} Predator;


class PredatorPrey
{
    public:
        /* Standard Variables */
        int width;
        int height;
        vector<Predator> Predators;
        Position PreyPos;
        /* Constructors */
        PredatorPrey();
        PredatorPrey(int width, int height, int num_pred);
        /* Helper functions */
        Position Distance(Position p1, Position p2);
        bool Captured();
        /* Predator functions */
        vector<Position> PredatorState(int index);
        void TakeAction(int index, int action);
};

#endif
