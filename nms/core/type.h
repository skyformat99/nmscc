#pragma once

#include <nms/core/base.h>
#include <nms/core/view.h>

namespace nms
{

struct Type
{
    __forceinline constexpr StrView name() const {
        return get_name_();
    }

    template<class T>
    constexpr static Type make() {
        return Type{ _get_name<T> };
    }

    friend __forceinline constexpr bool operator==(Type a, Type b) {
        return a.get_name_ == b.get_name_;
    }

    friend __forceinline constexpr bool operator!=(Type a, Type b) {
        return a.get_name_ != b.get_name_;
    }

private:
    StrView(*get_name_)();

    explicit constexpr Type(StrView(*func_name)())
        : get_name_(func_name)
    {}

#ifdef NMS_CC_MSVC
    static constexpr auto funcsig_head_size_ = sizeof("struct nms::View<char const ,0> __cdecl nms::Type::_get_name<") - 1;
    static constexpr auto funcsig_tail_size_ = sizeof(">(void)") - 1;
#else
    static constexpr auto funcsig_head_size_ = sizeof("static StrView nms::Type::_get_name() [T = ") - 1;
    static constexpr auto funcsig_tail_size_ = sizeof("]") - 1;
#endif
    template<class T>
    static StrView _get_name() {
        const StrView name =  { __PRETTY_FUNCTION__ + funcsig_head_size_, { u32(sizeof(__PRETTY_FUNCTION__) - funcsig_head_size_ - funcsig_tail_size_ - 1) } };
        return name;
    }
};

template<class T>
__forceinline constexpr Type typeof() {
    return Type::make<T>();
}

template<class T>
__forceinline constexpr Type typeof(const T&) {
    return Type::make<T>();
}

}
