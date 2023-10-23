// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len) : BitLen(len)
{
	if (len < 0) throw std::invalid_argument("error");
	MemLen = BitLen / (8 * sizeof(TELEM)) + 1;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++) { pMem[i] = 0; }
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++) { pMem[i] = bf.pMem[i]; }
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if ((n < 0) | (n > BitLen)) throw invalid_argument("error");
	return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if ((n < 0) | (n > BitLen)) throw invalid_argument("error");
	TELEM result = (1 << (n % (sizeof(TELEM) * 8)));
	return result;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0) | (n > BitLen)) throw invalid_argument("error");
	pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n < 0) | (n > BitLen)) throw invalid_argument("error");
	pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n < 0) | (n > BitLen)) throw invalid_argument("error");
	return ((pMem[GetMemIndex(n)] & GetMemMask(n)) > 0) ? 1 : 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++) pMem[i] = bf.pMem[i];
	return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
	if (BitLen != bf.BitLen) return 0;
	for (int i = 0; i < BitLen;i++) {
		if (GetBit(i) != bf.GetBit(i)) return 0;
	}
	return 1;
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
	if (BitLen != bf.BitLen) return 1;
	for (int i = 0; i < BitLen;i++) {
		if (GetBit(i) != bf.GetBit(i)) return 1;
	}
	return 0;
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
	TBitField result(GetLength() >= bf.GetLength() ? *this : bf);
	for (int i = 0; i < (BitLen < bf.BitLen ? BitLen : bf.BitLen); i++)
		if ((GetBit(i) | bf.GetBit(i)) > 0) result.SetBit(i);
	return result;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
	int max_len = BitLen > bf.BitLen ? BitLen : bf.BitLen;
	int min_len = BitLen + bf.BitLen - max_len;
	TBitField result(max_len);
	for (int i = 0; i < min_len; i++)
		if (GetBit(i) & bf.GetBit(i)) result.SetBit(i);
		else result.ClrBit(i);
	for (int i = min_len; i < max_len; i++) result.ClrBit(i);
	return result;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField result(BitLen);
	for (int i = 0; i < BitLen; i++)
		if (GetBit(i)) result.ClrBit(i);
		else result.SetBit(i);
	return result;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
	int sign;
	for (int i = 0; i < bf.BitLen; i++) {
		istr >> sign;
		if (sign == 1) bf.SetBit(bf.BitLen - i - 1);
		else if (sign == 0) bf.ClrBit(bf.BitLen - i - 1);
		else i--;
	}
	return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
	ostr << "{ ";
	for (int i = bf.BitLen - 1; i >= 0; i--)
		ostr << bf.GetBit(i) << " ";
	ostr << "}";
	return ostr;
}
