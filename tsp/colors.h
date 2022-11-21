#pragma once

#ifndef __COLOR_H__
#define __COLOR_H__

#include <iostream>
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#define NOMINMAX
#include <windows.h>

namespace __Coffee_colors {

	struct color {
	public:

		struct _Color {
		public:
			friend class color;
			_CONSTEXPR17 _Color() : _Val(7) { }
			_CONSTEXPR17 _Color(int value) : _Val(value) { }
			inline friend _STD ostream& operator<<(_STD ostream& os, const _Color& c) {
				SetConsoleTextAttribute(c._Handle, c._Val);
				return os;
			}
		private:
			const int _Val;
			const HANDLE& _Handle = hConsole;
		};

		friend struct color::_Color;
		friend struct _Color;

		static const _Color black;
		static const _Color darkblue;
		static const _Color darkgreen;
		static const _Color darkcyan;
		static const _Color darkred;
		static const _Color darkmagenta;
		static const _Color darkyellow;
		static const _Color darkgray;
		static const _Color gray;
		static const _Color blue;
		static const _Color green;
		static const _Color cyan;
		static const _Color red;
		static const _Color pink;
		static const _Color yellow;
		static const _Color white;
	private:
		static const HANDLE hConsole;
	};

	_INLINE_VAR const HANDLE color::hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	_INLINE_VAR const color::_Color color::black(0);
	_INLINE_VAR const color::_Color color::darkblue(1);
	_INLINE_VAR const color::_Color color::darkgreen(2);
	_INLINE_VAR const color::_Color color::darkcyan(3);
	_INLINE_VAR const color::_Color color::darkred(4);
	_INLINE_VAR const color::_Color color::darkmagenta(5);
	_INLINE_VAR const color::_Color color::darkyellow(6);
	_INLINE_VAR const color::_Color color::gray(7);
	_INLINE_VAR const color::_Color color::darkgray(8);
	_INLINE_VAR const color::_Color color::blue(9);
	_INLINE_VAR const color::_Color color::green(10);
	_INLINE_VAR const color::_Color color::cyan(11);
	_INLINE_VAR const color::_Color color::red(12);
	_INLINE_VAR const color::_Color color::pink(13);
	_INLINE_VAR const color::_Color color::yellow(14);
	_INLINE_VAR const color::_Color color::white(15);
}

using __Coffee_colors::color;

#endif // !__COLOR_H__
