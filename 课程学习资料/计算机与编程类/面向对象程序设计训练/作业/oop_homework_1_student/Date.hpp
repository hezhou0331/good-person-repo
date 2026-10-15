//------------------------------------------------------------------------------
//【文件名】           Date.hpp
//【功能模块和目的】   声明 Date 日期类，描述 1900-01-01 至 9999-12-31 之间的合法日期。
//【开发者及日期】   刘江宇, 2026-07-08
//【更改记录】       2026-07-08 统一注释格式，规范文件头位置。
//------------------------------------------------------------------------------

#ifndef DATE_HPP
#define DATE_HPP

#include <string>

//------------------------------------------------------------------------------
//【类名】       Date
//【功能】       封装年、月、日，提供合法性判断、日期比较和日期增减。
//【接口说明】   Get/Set 访问日期；IsValidDate/IsLeapYear/GetDaysInMonth 提供
//               日期工具；Compare/GetDaysBetween 判断日期关系；++/-- 增减一天。
//【开发者及日期】   刘江宇, 2026-07-08
//【更改记录】       2026-07-08 统一注释格式，精简冗余说明。
//------------------------------------------------------------------------------
class Date {
public:
    //必要的构造、赋值、析构行为
    Date();
    Date(int Year, int Month, int Day);
    Date(const Date& Source);
    Date& operator=(const Date& Source);
    ~Date();

    //日期读写接口
    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;
    void SetYear(int Year);
    void SetMonth(int Month);
    void SetDay(int Day);
    void SetDate(int Year, int Month, int Day);

    //静态日期工具函数
    static bool IsLeapYear(int Year);
    static int GetDaysInMonth(int Year, int Month);
    static bool IsValidDate(int Year, int Month, int Day);
    static int Compare(const Date& Left, const Date& Right);
    static int GetDaysFromMinDate(const Date& Target);
    static int GetDaysBetween(const Date& Left, const Date& Right);

    //非静态日期关系接口
    bool IsBefore(const Date& Other) const;
    bool IsAfter(const Date& Other) const;
    bool IsSameDay(const Date& Other) const;
    int GetDaysFromMinDate() const;
    int GetDaysBetween(const Date& Other) const;

    //日期增减一天
    Date& operator++();
    Date operator++(int UnusedFlag);
    Date& operator--();
    Date operator--(int UnusedFlag);

    //字符串与关系运算
    std::string ToString() const;
    bool operator==(const Date& Other) const;
    bool operator!=(const Date& Other) const;
    bool operator<(const Date& Other) const;
    bool operator<=(const Date& Other) const;
    bool operator>(const Date& Other) const;
    bool operator>=(const Date& Other) const;

private:
    //日期范围常量和月份天数表
    static const int MIN_YEAR;
    static const int MAX_YEAR;
    static const int MIN_MONTH;
    static const int MAX_MONTH;
    static const int MIN_DAY;
    static const int DAYS_PER_MONTH[12];

    int m_iYear;
    int m_iMonth;
    int m_iDay;
};

#endif
