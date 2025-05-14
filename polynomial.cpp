#include <iostream>
#include <vector>

template <typename T>
class Polynomial {
public:
    Polynomial() = default;

    Polynomial(const std::vector<T>& coeffs) : coefficients{coeffs} {
        Normalize();
    }

    Polynomial(const T& coeff) {
        coefficients.push_back(coeff);
        Normalize();
    }

    template <typename Iterator>
    Polynomial(Iterator first, Iterator last) : coefficients{first, last} {
        Normalize();
    }

    int Degree() const {
        return static_cast<int>(coefficients.size()) - 1;
    }

    const T& operator [] (int degree) const {
        if (degree > Degree()) {
            return zero_val;
        }
        return coefficients[degree];
    }

    typename std::vector<T>::const_iterator begin() const {
        return coefficients.cbegin();
    }

    typename std::vector<T>::const_iterator end() const {
        return coefficients.cend();
    }

    friend bool operator == (const Polynomial<T>& lhs, const Polynomial<T>& rhs) {
        return lhs.coefficients == rhs.coefficients;
    }

    friend bool operator != (const Polynomial<T>& lhs, const Polynomial<T>& rhs) {
        return !(lhs == rhs);
    }

    Polynomial<T>& operator += (const Polynomial<T>& other) {
        if (other.Degree() > Degree()) {
            coefficients.resize(other.Degree() + 1);
        }
        for (size_t i = 0; i <= std::min(static_cast<size_t>(Degree()), static_cast<size_t>(other.Degree())); ++i) {
            coefficients[i] += other.coefficients[i];
        }
        Normalize();
        return *this;
    }

    Polynomial<T>& operator -= (const Polynomial<T>& other) {
        if (other.Degree() > Degree()) {
            coefficients.resize(other.Degree() + 1);
        }
        for (int i = 0; i <= std::min(Degree(), other.Degree()); ++i) {
            coefficients[i] -= other.coefficients[i];
        }
        Normalize();
        return *this;
    }

    Polynomial<T>& operator *= (const Polynomial<T>& other) {
        if (Degree() != -1 && other.Degree() != -1) {
            int old_degree = Degree();
            const std::vector<T> lhs = coefficients;
            coefficients.assign(old_degree + other.Degree() + 1, zero_val);
            for (int i = 0; i <= old_degree; ++i) {
                for (int j = 0; j <= other.Degree(); ++j) {
                    coefficients[i + j] += lhs[i] * other.coefficients[j];
                }
            }
            Normalize();
        } else {
            coefficients.clear();
        }
        return *this;
    }

    T operator () (const T& val) const {
        T res = T{0};
        T prev_x = T{1};
        for (size_t i = 0; i != coefficients.size(); ++i) {
            res += coefficients[i] * prev_x;
            prev_x *= val;
        }
        return res;
    }

    friend Polynomial<T> operator + (Polynomial<T> lhs, const Polynomial<T>& rhs) {
        return lhs += rhs;
    }

    friend Polynomial<T> operator - (Polynomial<T> lhs, const Polynomial<T>& rhs) {
        return lhs -= rhs;
    }

    friend Polynomial<T> operator * (Polynomial<T> lhs, const Polynomial<T>& rhs) {
        return lhs *= rhs;
    }
private:
    std::vector<T> coefficients; // ascending degrees
    inline static const T zero_val = T{0};

    void Normalize() {
        while (!coefficients.empty() && coefficients.back() == zero_val) {
            coefficients.pop_back();
        }
    }
};

template <typename T>
std::ostream& operator << (std::ostream& os, const Polynomial<T>& p) {
    for (int degree = p.Degree(); degree >= 0; --degree) {
        os << p[degree];
        if (degree != 0) {
            os << " ";
        }
    }
    return os;
}

/*
void TestSum() {
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {1, 2, -3, 10};
    Polynomial<int> p1(v1);
    Polynomial<int> p2(v2);
    std::cout << p1 + p2 << '\n';
    auto p3 = p1 + 2;
    p1 += p2;
    std::cout << p1 << " " << p2 << '\n';
}

void TestDifference() {
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {1, 2, -3, 10};
    Polynomial<int> p1(v1);
    Polynomial<int> p2(v2);
    std::cout << p1 - p2 << '\n';
    p1 -= p2;
    std::cout << p1 << " " << p2 << '\n';
}

void TestMultiply() {
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {1, 2, 3};
    Polynomial<int> p1(v1);
    Polynomial<int> p2(v2);
    std::cout << "p1: " << p1 << " p2: " << p2 << "\n p1 * p2: " << p1 * p2 << '\n';
    std::cout << p1 * 2 << '\n';
    p1 *= p2;
    std::cout << p1 << p2 << '\n';
    std::cout << p1(-10);
    Polynomial<int> zero_poly(0);
    Polynomial<int> poly(1);
    std::cout << zero_poly * zero_poly << '\n';
}
*/

