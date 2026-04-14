#ifndef OHOS_STD_COMPAT_H
#define OHOS_STD_COMPAT_H

#include <filesystem>
#include <functional>
#include <algorithm>
#include <iterator>

// OHOS NDK libcxx does not provide std::hash<std::filesystem::path> specialization
namespace std {
template <>
struct hash<std::filesystem::path> {
    size_t operator()(const std::filesystem::path& p) const noexcept {
        return hash<std::string>()(p.string());
    }
};
} // namespace std

// OHOS NDK libcxx does not fully support C++20 ranges
// Provide compatibility shims delegating to standard algorithms
namespace std {
namespace ranges {
    template<typename InputIt, typename Pred>
    auto count_if(InputIt first, InputIt last, Pred pred) {
        return std::count_if(first, last, pred);
    }

    // count with iterators
    template<typename InputIt, typename T>
    auto count(InputIt first, InputIt last, const T& value) {
        return std::count(first, last, value);
    }

    // count with container + value (C++20 ranges::count(c, value) style)
    template<typename Range, typename T>
    auto count(Range& range, const T& value) -> decltype(std::count(range.begin(), range.end(), value)) {
        return std::count(range.begin(), range.end(), value);
    }

    // count with const container + value
    template<typename Range, typename T>
    auto count(const Range& range, const T& value) -> decltype(std::count(range.begin(), range.end(), value)) {
        return std::count(range.begin(), range.end(), value);
    }

    // find with iterators
    template<typename InputIt, typename T>
    InputIt find(InputIt first, InputIt last, const T& value) {
        return std::find(first, last, value);
    }

    // find with container + value (C++20 ranges::find(c, value) style)
    template<typename Range, typename T>
    auto find(Range& range, const T& value) -> decltype(range.begin()) {
        return std::find(range.begin(), range.end(), value);
    }

    // find with const container + value
    template<typename Range, typename T>
    auto find(const Range& range, const T& value) -> decltype(range.begin()) {
        return std::find(range.begin(), range.end(), value);
    }

    // sort with iterators + comparator
    template<typename RandomIt, typename Comp>
    void sort(RandomIt first, RandomIt last, Comp comp) {
        std::sort(first, last, comp);
    }

    // sort with iterators only
    template<typename RandomIt>
    void sort(RandomIt first, RandomIt last) {
        std::sort(first, last);
    }

    // sort with container + comparator (C++20 ranges::sort(c, comp) style)
    template<typename Range, typename Comp>
    void sort(Range& range, Comp comp) {
        std::sort(range.begin(), range.end(), comp);
    }

    // sort with container only
    template<typename Range>
    void sort(Range& range) {
        std::sort(range.begin(), range.end());
    }
} // namespace ranges
} // namespace std

#endif
