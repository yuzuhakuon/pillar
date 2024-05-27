#pragma once

namespace pillar
{
template <class T>
class SingleTon
{
public:
    static T& instance()
    {
        static T t;
        return t;
    }
    SingleTon(const SingleTon&) = delete;
    SingleTon(SingleTon&&) = delete;
    SingleTon& operator=(const SingleTon&) = delete;
    SingleTon& operator=(SingleTon&&) = delete;

protected:
    SingleTon() = default;
};
} // namespace pillar