// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include <cmath>

const size_t bitsInElem = numeric_limits<TELEM>::digits;

TBitField::TBitField(int len) 
{
	if (len <= 0) throw invalid_argument("trying to create bitfield with negative length");
	BitLen = len;
	MemLen = (len / bitsInElem) + 1 ;
	pMem = new TELEM[MemLen];
	if (pMem != nullptr) {
		for (size_t i = 0; i < MemLen; i++) {
			pMem[i] = 0;
		}
	}

}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	if (pMem != nullptr) {
		for (size_t i = 0; i < MemLen; i++) {
			pMem[i] = 0;
		}
	}
	for (size_t i = 0; i < MemLen; i++) {
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return n / bitsInElem;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1 << (n % (bitsInElem - 1));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	
	if ((n >= BitLen) || (n < 0)) throw out_of_range("bit pos is out of range");
	pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n >= BitLen) || (n < 0)) throw out_of_range("bit pos is out of range");
	pMem[GetMemIndex(n)] &= ~(GetMemMask(n));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n >= BitLen) || (n < 0)) throw out_of_range("bit pos is out of range");
	if (!(pMem[GetMemIndex(n)] & GetMemMask(n))) return 0;
	else return 1;
 
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	BitLen = bf.BitLen;
	if (MemLen != bf.MemLen) {
		delete[] pMem;
		MemLen = bf.MemLen;
		pMem= new TELEM[MemLen]{};
		
	}
	for (size_t i = 0; i < bf.MemLen; i++) {
		pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen) return 0;
	for (size_t i = 0; i < MemLen; i++) {
		if (pMem[i] != bf.pMem[i]) return 0;
	}
	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (*this == bf) return 0;
	else return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	size_t len = max(BitLen, bf.BitLen);
	TBitField tmp(len);
	if (MemLen > bf.MemLen) tmp = *this;
	else tmp = bf;
	for (size_t i = 0; i < min(MemLen, bf.MemLen); i++) {
		tmp.pMem[i] = pMem[i] | bf.pMem[i];
	}
	return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	size_t len = max(BitLen, bf.BitLen);
	TBitField tmp(len);
	for (size_t i = 0; i < min(MemLen, bf.MemLen); i++) {
		tmp.pMem[i] = pMem[i] & bf.pMem[i];
	}
	return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField tmp(*this);
	for (size_t i = 0; i < BitLen; i++) {
		if (GetBit(i)) tmp.ClrBit(i);
		else tmp.SetBit(i);
	}
	return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	unsigned int tmp;
	for (size_t i = 0; i < bf.GetLength(); i++) {
		cout << "Enter " << i << " bit";
		cin >> tmp;
		if (tmp == 1) bf.SetBit(i);
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (size_t i = 0; i < bf.BitLen; i++) {
		ostr << bf.GetBit(i);
		return ostr;
	}
}
