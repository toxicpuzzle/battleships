//
// Created by toxic on 23/11/2023.
//

#ifndef VISUALISER_VEC2UTILS_H
#define VISUALISER_VEC2UTILS_H
/**
 * Templates to allow using coords as keys (hash and equal to function
 * these are passed into to constructor of hashmap implicitly (or can
 * be explicitly done through lambda functions)
 */
template <>
struct std::hash<Vector2>
{
    std::size_t operator()(Vector2 const &s) const noexcept
    {
        auto getIntHash = std::hash<int>{};
        return getIntHash(s.x) ^ getIntHash(s.y); // or use boost::hash_combine (see Discussion) https://en.cppreference.com/w/Talk:cpp/utility/hash
    }
};

template<>
struct std::equal_to<Vector2>
{
    constexpr bool operator()(const Vector2& lhs, const Vector2& rhs) const
    {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }
};
#endif //VISUALISER_VEC2UTILS_H
