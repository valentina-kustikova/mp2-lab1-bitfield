// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len >= 0)
	{
		BitLen = len;
		MemLen = BitLen / (sizeof(TELEM) * 8) + 1;
		pMem = new TELEM[MemLen];
		for (size_t i = 0; i < MemLen; i++)
		{
			pMem[i] = 0;
		}
	}
	else
	{
		std::cout << "Negative value" << std::endl;
		throw "Negative value"
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	MemLen = bf.MemLen;
	BitLen = bf.BitLen;
	pMem = new TELEM[MemLen];
	for (size_t i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n >= 0 && n <= BitLen)
		return (n / sizeof(TELEM) * 8);
	else
		std::cout << "Invalid index" << std::endl;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n >= 0 && n <= BitLen)
		return (1 << (n % sizeof(TELEM) * 8));
	else
		std::cout << "Invalid value" << std::endl;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n >= 0 && n <= BitLen)
		pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n);
	else
	{
		std::cout << "Invalid index" << std::endl;
		throw "Invalid index";
	}
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n >= 0 && n <= BitLen)
		pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & ~GetMemMask(n);
	else
	{
		std::cout << "Invalid index" << std::endl;
		throw "Invalid index";
	}
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n >= 0 && n <= BitLen)
		if (pMem[GetMemIndex(n)] & GetMemMask(n))
			return 1;
		else
			return 0;
	else
	{
		std::cout << "Invalid index" << std::endl;
		throw "Invalid index";
	}
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	MemLen = bf.MemLen;
	BitLen = bf.BitLen;
	pMem = new TELEM[MemLen];
	for (size_t i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	for (size_t i = 0; i < MemLen; i++)
	{
		if (pMem[i] != bf.pMem[i])
			return 0;
	}

	if (BitLen != bf.BitLen)
		return 0;

	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (*this == bf)
		return 0;
	return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int tmpSize;
	if (BitLen <= bf.BitLen)
		tmpSize = bf.BitLen;
	else tmpSize = BitLen;

	TBitField tmp(tmpSize);
	for (size_t i = 0; i < MemLen; i++)
		tmp.pMem[i] = pMem[i];
	for (size_t i = 0; i < MemLen; i++)
		tmp.pMem[i] = (bf.pMem[i] | pMem[i]);
	return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int tmpSize;
	int tmpMem;

	if (BitLen > bf,BitLen)
	{
		tmpSize = BitLen;
		tmpMem = bf.MemLen;
	}
	else 
	{
		tmpSize = bf.BitLen;
		tmpMem = MemLen;
	}

	TBitField tmp(tmpSize);

	for (size_t i = 0; i < tmpMem; i++)
		tmp.pMem[i] = bf.pMem[i] & pMem[i];
	return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField tmp(BitLen);
	for (size_t i = 0; i < BitLen; i++)
	{
		if (GetBit(i) != 0)
			tmp.ClrBit(i);
		else
			tmp.SetBit(i);
	}
	return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int value;
	for (size_t i = 0; i < bf.GetLength(); i++)
	{
		istr >> value;
		if (value != 0)
			bf.SetBit(i);
		else
			bf.ClrBit(i);
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (size_t i = 0; i < bf.GetLength(); i++)
		ostr << bf.GetBit(i);
	ostr << std::endl;
	return ostr
}
