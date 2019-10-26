#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <ostream>

class Complex
{
public:
	explicit Complex(double re = 0.0, double im = 0.0);
	Complex(const Complex &c);

	double re() const;
	double im() const;

	Complex operator-() const;
	Complex &operator+=(const Complex c);
	Complex &operator-=(const Complex c);
	Complex &operator*=(const Complex c);
	Complex &operator/=(const Complex c);
	Complex operator+(const Complex c) const;
	Complex operator-(const Complex c) const;
	Complex operator*(const Complex c) const;
	Complex operator/(const Complex c) const;
	friend std::ostream &operator<<(std::ostream &, const Complex &);

private:
	double m_re;
	double m_im;
};

#endif // COMPLEX_HPP
