// TODO: implement division and square root

constexpr auto zero = [](auto) {
    return [](auto x) {
        return x;
    };
};

constexpr auto succ = [](auto numeral) {
    return [=](auto f) {
        return [=](auto x) {
            return f(numeral(f)(x));
        };
    };
};

constexpr auto add = [](auto m) {
    return [=](auto n) {
        return [=](auto f) {
            return [=](auto x) {
                return m(f)(n(f)(x));
            };
        };
    };
};

constexpr auto mult = [](auto m) {
    return [=](auto n) {
        return [=](auto f) {
            return [=](auto x) {
                return m(n(f))(x);
            };
        };
    };
};

constexpr auto expo = [](auto m) {
    return [=](auto n) {
        return n(m);
    };
};

// pred(zero) is (functionally equivalent to) zero
constexpr auto pred = [](auto n) {
    return [=](auto f) {
        return [=](auto x) {
            return n([=](auto g) {
                return [=](auto h) {
                    return h(g(f));
                };
            })([=](auto) { return x; })([=](auto u) { return u; });
        };
    };
};

// subtract(m, n) is (functionally equivalent to) zero iff m <= n
constexpr auto subtract = [](auto m) {
    return [=](auto n) {
        return n(pred)(m);
    };
};

int main() {
    constexpr auto one = succ(zero);
    constexpr auto two = succ(one);
    constexpr auto four = add(two)(two);
    constexpr auto eight = mult(two)(four);
    constexpr auto n_4096 = expo(eight)(four);
    constexpr auto seven = pred(eight);
    constexpr auto five = subtract(seven)(two);

    constexpr auto f = [](int x) {
        return x + 1;
    };

    static_assert(eight(f)(0) == 8);
    static_assert(n_4096(f)(0) == 4096);
    static_assert(seven(f)(0) == 7);
    static_assert(five(f)(0) == 5);
}

