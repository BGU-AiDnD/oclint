#ifndef OCLINT_UTIL_FOUNDSTATUS_H
#define OCLINT_UTIL_FOUNDSTATUS_H

enum class CountStatus
{
    None,
    Found,
    MoreThan1,
};
enum class MatchStatus
{
    None,
    Match,
    NoMatch,
};

class FoundStatus
{
public:
    CountStatus countStatus;
    MatchStatus matchStatus;

    void foundMatch()
    {
        if (countStatus == CountStatus::Found)
        {
            countStatus = CountStatus::MoreThan1;
        }
        else
        {
            countStatus = CountStatus::Found;
        }

        if (matchStatus != MatchStatus::NoMatch)
        {
            matchStatus = MatchStatus::Match;
        }
    }

    bool isMatch() const
    {
        return matchStatus == MatchStatus::Match &&
               countStatus == CountStatus::Found;
    }

    bool isValid() const
    {
        return matchStatus != MatchStatus::NoMatch &&
               countStatus != CountStatus::MoreThan1;
    }

    void reset()
    {
        matchStatus = MatchStatus::None;
        countStatus = CountStatus::None;
    }
};

#endif //OCLINT_UTIL_FOUNDSTATUS_H
