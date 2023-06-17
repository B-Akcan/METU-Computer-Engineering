#include "tournament_round.h"

// TournamentRound functions goes here

TournamentRound::TournamentRound() {}
TournamentRound::TournamentRound(std::list<MusicBand*>_bands)
{
    bands = _bands;
}
TournamentRound::TournamentRound(std::vector<MusicBand*>_bands)
{
    bands.assign(_bands.begin(), _bands.end());
}

std::size_t TournamentRound::size() { return bands.size(); }
    
TournamentRound& TournamentRound::operator=(TournamentRound&& other)
{
    bands.clear();
    bands = std::move(other.bands);
    return *this;
}

TournamentRound& TournamentRound::get_next_round()
{
    std::list<MusicBand*> lst;
    int sz = bands.size(), fan_change, score1, score2;
    if (sz % 2 == 1)
    {
        auto it2 = bands.end();
        it2--;
        for (auto it1=bands.begin(); it1 != it2; it1++, it2--)
        {
            score1 = (*it1)->play(*it2);
            score2 = (*it2)->play(*it1);
            if (score1 >= score2)
            {
                fan_change = score1 - score2;
                if (fan_change <= (*it2)->get_fan_count())
                {
                    (*it1)->set_fan_count((*it1)->get_fan_count() + fan_change);
                    (*it2)->set_fan_count((*it2)->get_fan_count() - fan_change);
                }
                else
                {
                    (*it1)->set_fan_count((*it1)->get_fan_count() + (*it2)->get_fan_count());
                    (*it2)->set_fan_count(0);
                }
                lst.push_back(*it1);
            }
            else
            {
                fan_change = score2 - score1;
                if (fan_change <= (*it1)->get_fan_count())
                {
                    (*it1)->set_fan_count((*it1)->get_fan_count() - fan_change);
                    (*it2)->set_fan_count((*it2)->get_fan_count() + fan_change);
                }
                else
                {
                    (*it1)->set_fan_count(0);
                    (*it2)->set_fan_count((*it1)->get_fan_count() + (*it2)->get_fan_count());
                }
                lst.push_back(*it2);
            }
        }
        lst.push_back(*it2);
    }
    else
    {
        auto it2 = bands.end();
        it2--;
        for (auto it1=bands.begin(); std::distance(bands.begin(), it1) < std::distance(bands.begin(), it2); it1++, it2--)
        {
            score1 = (*it1)->play(*it2);
            score2 = (*it2)->play(*it1);
            if (score1 >= score2)
            {
                fan_change = score1 - score2;
                if (fan_change <= (*it2)->get_fan_count())
                {
                    (*it1)->set_fan_count((*it1)->get_fan_count() + fan_change);
                    (*it2)->set_fan_count((*it2)->get_fan_count() - fan_change);
                }
                else
                {
                    (*it1)->set_fan_count((*it1)->get_fan_count() + (*it2)->get_fan_count());
                    (*it2)->set_fan_count(0);
                }
                lst.push_back(*it1);
            }
            else
            {
                fan_change = score2 - score1;
                if (fan_change <= (*it1)->get_fan_count())
                {
                    (*it1)->set_fan_count((*it1)->get_fan_count() - fan_change);
                    (*it2)->set_fan_count((*it2)->get_fan_count() + fan_change);
                }
                else
                {
                    (*it1)->set_fan_count(0);
                    (*it2)->set_fan_count((*it1)->get_fan_count() + (*it2)->get_fan_count());
                }
                lst.push_back(*it2);
            }
        }
    }

    TournamentRound *tr = new TournamentRound(lst);
    return *tr;
}

std::ostream& operator<< (std::ostream &os, TournamentRound &other)
{
    for (auto it=other.bands.begin(); it != other.bands.end(); it++)
    {
        os << (*it)->get_name();
        if (std::distance(it, other.bands.end()) > 1)
            os << '\t';
    }
    return os;
}