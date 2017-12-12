#include "domain.h"

bool Position::operator==(const Position& other)
{
    return (other.x == this->x && other.y == this->y);
}

PredatorPrey::PredatorPrey()
{
    /* Default is 2 predators in a 100 by 100 world */
    width = 100;
    height = 100;
    for (int i = 0; i < 2; ++i)
    {
        Predator pred;
        pred.pos.x = 0;
        pred.pos.y = 0;
        pred.index = i;
        Predators.push_back(pred);
    }
    PreyPos.x = 50;
    PreyPos.y = 50;
}

PredatorPrey::PredatorPrey(int width, int height, int num_pred)
{
    this->width = width;
    this->height= height;
    for (int i = 0; i < num_pred; ++i)
    {
        Predator pred;
        pred.pos.x = 0;
        pred.pos.y = 0;
        pred.index = i;
        Predators.push_back(pred);
    }
    /* Set prey in middle of world */
    PreyPos.x = width/2;
    PreyPos.y = height/2;
}

Position PredatorPrey::Distance(Position p1, Position p2)
{
    /* Returns the delta between the observer (p1) and
     * the observed (p2). The sign remains so the information
     * about relative orientation is preserved. */
    Position d;
    d.x = p1.x - p2.x;
    d.y = p1.y - p2.y;
    return d;
}

/* If a single predator occupies the same cell as the prey, 
 * the prey is captured */
bool PredatorPrey::Captured()
{
    for (auto itr=this->Predators.begin(); itr != this->Predators.end(); ++itr)
    {
        if (itr->pos == this->PreyPos)
        {
            return true;
        }
    }
    return false;
}

vector<Position> PredatorPrey::PredatorState(int index)
{
    /* The state is a vector of the position offsets
     * from my current position to the prey, and to all other 
     * predators, as defined in Yong, Miikkulainen 2001 */
    Predator* current = &(Predators[index]);
    vector<Position> state;
    state.push_back(this->Distance(current->pos, this->PreyPos));
    for (auto itr = this->Predators.begin(); itr != this->Predators.end(); ++itr)
    {
        if (itr->index == current->index)
        {
            continue;
        }
        state.push_back(this->Distance( current->pos, itr->pos));
    }
    return state;
}

void PredatorPrey::TakeAction(int index, int action)
{
    Predator* current = &(Predators[index]);
    switch(action)
    {
        case 0: break;               /* STAY  */
        case 1: current->pos.y -= 1; /* UP    */
        case 2: current->pos.y += 1; /* DOWN  */
        case 3: current->pos.x -= 1; /* LEFT  */
        case 4: current->pos.x += 1; /* RIGHT */
    }
    /* Check for invalid positions */
    if (current->pos.x < 0)
        current->pos.x += this->width;
    if (current->pos.x >= width)
        current->pos.x -= this->width;
    if (current->pos.y < 0)
        current->pos.y += this->height;
    if (current->pos.y >= height)
        current->pos.y -= this->height;
}
