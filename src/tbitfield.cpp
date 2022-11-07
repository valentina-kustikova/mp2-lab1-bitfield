// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len <= 0)
	{
		throw exception("Length must be pozitive");
	}
	else
	{
		BitLen = len;
		MemLen = BitLen / (sizeof(TELEM) * 8);
		if (MemLen * sizeof(TELEM) * 8 < len)
		{
			MemLen++;
		}
		pMem = new TELEM[MemLen];
		memset(pMem, 0, MemLen * sizeof(TELEM));
	}
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	memcpy(pMem, bf.pMem, MemLen * sizeof(TELEM));

}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1 << (n & (sizeof(TELEM) * 8 - 1));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n >= 0 && n < BitLen)
	{
		pMem[GetMemIndex(n)] |= GetMemMask(n);
	}
	else
	{
		throw exception("SetBit out of range");
	}
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n >= 0 && n < BitLen)
	{
		pMem[GetMemIndex(n)] &= ~GetMemMask(n);
	}
	else
	{
		throw exception("ClrBit out of range");
	}
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n >= 0 && n < BitLen)
	{
		if (pMem[GetMemIndex(n)] & GetMemMask(n))
		{
			return 1;
		}
        return 0;
	}
	else
		throw exception("GetBit out of range");
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
	BitLen = bf.BitLen;
	if (MemLen != bf.MemLen)
	{
		delete[] pMem;
		MemLen = bf.MemLen;
		pMem = new TELEM[MemLen];
	}
	memcpy(pMem, bf.pMem, MemLen * sizeof(TELEM));
	return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
	if (BitLen != bf.BitLen)
	{
		return 0;
	}
	for (int i = 0; i < MemLen; ++i)
	{
		if (pMem[i] != bf.pMem[i])
		{
			return 0;
		}
	}
	return 1;
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
	if (*this == bf)
	{
		return 0;
	}
	return 1;
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{        //TBitField.or_operator_applied_to_bitfields_of_non_equal_size

	TBitField temp(max(BitLen, bf.BitLen));
	for (int i = 0; i < MemLen; ++i)
	{
		temp.pMem[i] = pMem[i];
	}
	for (int i = 0; i < bf.MemLen; ++i)
	{
		temp.pMem[i] |= bf.pMem[i];
	}
	return temp;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
	TBitField temp(max(BitLen, bf.BitLen));
	for (int i = 0; i < min(MemLen, bf.MemLen); ++i)
	{
		temp.pMem[i] = pMem[i] & bf.pMem[i];
	}
	return temp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField temp(BitLen);
	for (int i = 0; i < MemLen; ++i)
	{
		temp.pMem[i] = ~pMem[i];
	}
	temp.pMem[MemLen - 1] &= GetMemMask(BitLen) - 1;

	return temp;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
	int max_number = bf.GetLength();
	int input;
	while (true)
	{
		istr >> input;

		if (input >= 0 && input < max_number)
			bf.SetBit(input);
		else
			break;
	}
	return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
	for (int output = 0; output < bf.GetLength(); output++)
	{
		if (bf.GetBit(output))
			ostr << output << " ";
	}
	return ostr;
}
