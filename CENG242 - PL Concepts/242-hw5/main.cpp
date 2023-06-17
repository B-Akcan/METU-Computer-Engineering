#include "kpop.cpp"
#include "jazz.cpp"
#include "rock.cpp"
#include "metal.cpp"

#include "tournament.cpp"
#include "tournament_round.cpp"


int main()
{
    JazzBand band1("jazz", 50, 100, 25);
    RockBand band2("rock", 50, 100, 25);
    MetalBand band3("metal", 50, 100, 25);
    KPopBand band4("kpop", 50, 100, 25);
    KPopBand band5("kpop2", 50, 100, 25);
    
    Tournament tournament;
    
    tournament.enroll(band1);
    tournament.enroll(band2);
    tournament.enroll(band3);
    tournament.enroll(band4);
    tournament.enroll(band5);
    
    tournament.make_tournament();
    return 0;
}