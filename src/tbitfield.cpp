// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

#include <stdexcept>

TBitField::TBitField(int len)
{
    if (len > 0)
    {
        BitLen = len;
        pMem = new TELEM[BitLen];
        for (int i = 0; i < BitLen; ++i)
        {
            pMem[i] = 0;
        }
    }
    else
    {
        throw std::range_error("BitField length can't be negative");
    }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{

}

TBitField::~TBitField()
{

}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{

}


TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{

}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{

}

void TBitField::ClrBit(const int n) // очистить бит
{

}

int TBitField::GetBit(const int n) const // получить значение бита
{
    return pMem[n];
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{

}

int TBitField::operator==(const TBitField &bf) // сравнение
{

}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{

}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{

}

TBitField TBitField::operator~(void) // отрицание
{

}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{

}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{

}
