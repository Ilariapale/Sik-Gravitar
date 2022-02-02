#ifndef BUNKERB_H
#define BUNKERB_H

#include <Bunker.h>


class BunkerB : public Bunker
{
    public:
        BunkerB();
        virtual ~BunkerB();

        void Cannon(SpaceShip astronave){
            if (rotation >= (90 - int(angolazione_terreno) - 10))
            v=1;
        else
            if (rotation <= (- 90 - int(angolazione_terreno) + 10))
                v=0;
        if (v==0)
            rotation = rotation + r_speed;
        else
            if (v==1)
                rotation = rotation - r_speed;

        }

    protected:

    private:
};

#endif // BUNKERB_H
