#include "kpop.h"
#include "metal.h"
#include "jazz.h"
#include "rock.h"


int RockBand::play(MusicBand *other)
{
    double c;
    
    KPopBand *b1 = dynamic_cast<KPopBand*>(other);
    if (b1 != nullptr)
        c = 0.5;
    MetalBand *b2 = dynamic_cast<MetalBand*>(other); 
    if (b2 != nullptr)
        c = 1.4;
    RockBand *b3 = dynamic_cast<RockBand*>(other); 
    if (b3 != nullptr)
        c = 1.0;
    JazzBand *b4 = dynamic_cast<JazzBand*>(other); 
    if (b4 != nullptr)
        c = 0.8;
    
    int score = (get_fan_count() + 0.1 * get_talent() * get_energy()) * c;
    
    set_energy(get_energy() * (1 - 0.1));
    
    return score;
    
    return 0;
}

void RockBand::rehearse(void) 
{
    set_energy(get_energy() - 0.5 * 0.1);
    set_talent(get_talent() + 10);
}