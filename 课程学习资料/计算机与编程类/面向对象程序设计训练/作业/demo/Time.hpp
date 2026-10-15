//
//  Time.hpp
//  Demo_Day_01_Time
//
//  Created by 范静涛 on 2026/6/29.
//

#ifndef Time_hpp
#define Time_hpp
#include <string>

class Time{
    //Data Member
private:
    unsigned int m_Hour{MinHour};
    unsigned int m_Min{MinMin};
    unsigned int m_Sec{MinSec};
public:
    //static Data Member
    static const unsigned int MinHour;
    static const unsigned int MinMin;
    static const unsigned int MinSec;
    static const unsigned int MaxHour;
    static const unsigned int MaxMin;
    static const unsigned int MaxSec;
    //Member Function
    //default
    Time();
    Time(unsigned int Hour, unsigned int Min, unsigned int Sec);
    Time& operator=(const Time& Source);
    Time(const Time& Source);
    ~Time();
    //Setter
    void Set(unsigned int Hour, unsigned int Min, unsigned int Sec);
    void SetHour(unsigned int Hour);
    void SetMin(unsigned int Min);
    void SetSec(unsigned int Sec);
    //Getter
    std::string ToString() const;
    const unsigned int& Hour{m_Hour};
    const unsigned int& Min{m_Min};
    const unsigned int& Sec{m_Sec};
};

#endif /* Time_hpp */
