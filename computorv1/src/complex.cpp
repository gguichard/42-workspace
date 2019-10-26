#include <ostream>
#include "complex.hpp"

Complex::Complex(double re, double im) : m_re(re), m_im(im)
{
}

Complex::Complex(const Complex &c) : m_re(c.m_re), m_im(c.m_im)
{
}

double Complex::re() const
{
	return m_re;
}

double Complex::im() const
{
	return m_im;
}

Complex Complex::operator-() const
{
	return Complex(-m_re, -m_im);
}

Complex &Complex::operator+=(const Complex c2)
{
	m_re += c2.m_re;
	m_im += c2.m_im;
	return *this;
}

Complex &Complex::operator-=(const Complex c2)
{
	m_re -= c2.m_re;
	m_im -= c2.m_im;
	return *this;
}

Complex &Complex::operator*=(const Complex c2)
{
	Complex c = Complex(*this);
	m_re = c.m_re * c2.m_re - c.m_im * c2.m_im;
	m_im = c.m_re * c2.m_im + c.m_im * c2.m_re;
	return *this;
}

Complex &Complex::operator/=(const Complex c2)
{
	Complex nm = Complex(*this) * Complex(c2.m_re, -c2.m_im);
	double dn = c2.m_re * c2.m_re + c2.m_im * c2.m_im;
	m_re = nm.m_re / dn;
	m_im = nm.m_im / dn;
	return *this;
}

Complex Complex::operator+(const Complex c2) const
{
	return Complex(*this) += c2;
}

Complex Complex::operator-(const Complex c2) const
{
	return Complex(*this) -= c2;
}

Complex Complex::operator*(const Complex c2) const
{
	return Complex(*this) *= c2;
}

Complex Complex::operator/(const Complex c2) const
{
	return Complex(*this) /= c2;
}

std::ostream &operator<<(std::ostream &os, const Complex &c)
{
	os << c.m_re;
	if (c.m_im < 0.0)
		os << c.m_im << "i";
	else if (c.m_im > 0.0)
		os << "+" << c.m_im << "i";
	return os;
}
