//
//  Time.cpp
//  Demo_Day_01_Time
//
//  Created by 范静涛 on 2026/6/29.
//

#include "Time.hpp"
#include <string>

//static Data Member
const unsigned int Time::MinHour{0};
const unsigned int Time::MinMin{0};
const unsigned int Time::MinSec{0};
const unsigned int Time::MaxHour{23};
const unsigned int Time::MaxMin{59};
const unsigned int Time::MaxSec{59};
//Member Function
//default
Time::Time(){
    SetHour(MinHour);
    SetMin(MinMin);
    SetSec(MinSec);
}

Time::Time(unsigned int Hour, unsigned int Min, unsigned int Sec){
    Set(Hour, Min, Sec);
}
Time& Time::operator=(const Time& Source){
    if (this != &Source){
        Set(Source.Hour, Source.Min, Source.Sec);
    }
    return *this;
}
Time::Time(const Time& Source){
    Set(Source.Hour, Source.Min, Source.Sec);
}
Time::~Time(){
}

//Setter
void Time::Set(unsigned int Hour, unsigned int Min, unsigned int Sec){
    if (Hour <= MaxHour && Min <= MaxMin && Sec <= MinSec){
        SetHour(Hour);
        SetMin(Min);
        SetSec(Sec);
    }
}
void Time::SetHour(unsigned int Hour){
    if (Hour <= MaxHour){
        m_Hour = Hour;
    }
}
void Time::SetMin(unsigned int Min){
    if (Min <= MaxMin){
        m_Min = Min;
    }
}
void Time::SetSec(unsigned int Sec){
    if (Sec <= MaxSec){
        m_Sec = Sec;
    }
}
//Getter
std::string Time::ToString() const{
    return std::string();
}
