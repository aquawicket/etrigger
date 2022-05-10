//// KeyToString.h /////////////////////////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef KEYTOSTRING_H
#define KEYTOSTRING_H

///////////
class KeyB
{

public:

	static wxString KeyToString(int code)
	{
		wxString string;

		switch(code){
			case 0: string = wxT("0"); break;
			case 1: string = wxT("1"); break;
			case 2: string = wxT("2"); break;
			case 3: string = wxT("3"); break;
			case 4: string = wxT("4"); break;
			case 5: string = wxT("5"); break;
			case 6: string = wxT("6"); break;
			case 7: string = wxT("7"); break;
			case 8: string = wxT("Backspace"); break;
			case 9: string = wxT("9"); break;
			case 10: string = wxT("10"); break;
			case 11: string = wxT("11"); break;
			case 12: string = wxT("12"); break;
			case 13: string = wxT("13"); break;
			case 14: string = wxT("14"); break;
			case 15: string = wxT("15"); break;
			case 16: string = wxT("16"); break;
			case 17: string = wxT("17"); break;
			case 18: string = wxT("18"); break;
			case 19: string = wxT("19"); break;
			case 20: string = wxT("20"); break;
			case 21: string = wxT("21"); break;
			case 22: string = wxT("22"); break;
			case 23: string = wxT("23"); break;
			case 24: string = wxT("24"); break;
			case 25: string = wxT("25"); break;
			case 26: string = wxT("26"); break;
			case 27: string = wxT("Esc"); break;
			case 28: string = wxT("28"); break;
			case 29: string = wxT("29"); break;
			case 30: string = wxT("30"); break;
			case 31: string = wxT("31"); break;
			case 32: string = wxT("Spacebar"); break;
			case 33: string = wxT("33"); break;
			case 34: string = wxT("34"); break;
			case 35: string = wxT("35"); break;
			case 36: string = wxT("36"); break;
			case 37: string = wxT("37"); break;
			case 38: string = wxT("38"); break;
			case 39: string = wxT("'"); break;
			case 40: string = wxT("40"); break;
			case 41: string = wxT("41"); break;
			case 42: string = wxT("42"); break;
			case 43: string = wxT("="); break;
			case 44: string = wxT(","); break;
			case 45: string = wxT("-"); break;
			case 46: string = wxT("."); break;
			case 47: string = wxT("/"); break;
			case 48: string = wxT("0"); break;
			case 49: string = wxT("1"); break;
			case 50: string = wxT("2"); break;
			case 51: string = wxT("3"); break;
			case 52: string = wxT("4"); break;
			case 53: string = wxT("5"); break;
			case 54: string = wxT("6"); break;
			case 55: string = wxT("7"); break;
			case 56: string = wxT("8"); break;
			case 57: string = wxT("9"); break;
			case 58: string = wxT("58"); break;
			case 59: string = wxT(";"); break;
			case 60: string = wxT("60"); break;
			case 61: string = wxT("61"); break;
			case 62: string = wxT("62"); break;
			case 63: string = wxT("63"); break;
			case 64: string = wxT("64"); break;
			case 65: string = wxT("A"); break;
			case 66: string = wxT("B"); break;
			case 67: string = wxT("C"); break;
			case 68: string = wxT("D"); break;
			case 69: string = wxT("E"); break;
			case 70: string = wxT("F"); break;
			case 71: string = wxT("G"); break;
			case 72: string = wxT("H"); break;
			case 73: string = wxT("I"); break;
			case 74: string = wxT("J"); break;
			case 75: string = wxT("K"); break;
			case 76: string = wxT("L"); break;
			case 77: string = wxT("M"); break;
			case 78: string = wxT("N"); break;
			case 79: string = wxT("O"); break;
			case 80: string = wxT("P"); break;
			case 81: string = wxT("Q"); break;
			case 82: string = wxT("R"); break;
			case 83: string = wxT("S"); break;
			case 84: string = wxT("T"); break;
			case 85: string = wxT("U"); break;
			case 86: string = wxT("V"); break;
			case 87: string = wxT("W"); break;
			case 88: string = wxT("X"); break;
			case 89: string = wxT("Y"); break;
			case 90: string = wxT("Z"); break;
			case 91: string = wxT("["); break;
			case 92: string = wxT("\\"); break;
			case 93: string = wxT("]"); break;
			case 94: string = wxT("F11"); break;
			case 95: string = wxT("F12"); break;
			case 96: string = wxT("96"); break;
			case 97: string = wxT("97"); break;
			case 98: string = wxT("98"); break;
			case 99: string = wxT("99"); break;
			case 100: string = wxT("100"); break;
			case 101: string = wxT("101"); break;
			case 102: string = wxT("102"); break;
			case 103: string = wxT("103"); break;
			case 104: string = wxT("104"); break;
			case 105: string = wxT("105"); break;
			case 106: string = wxT("106"); break;
			case 107: string = wxT("107"); break;
			case 108: string = wxT("Num Lock"); break;
			case 109: string = wxT("Scroll Lock"); break;
			case 110: string = wxT("110"); break;
			case 111: string = wxT("111"); break;
			case 112: string = wxT("112"); break;
			case 113: string = wxT("113"); break;
			case 114: string = wxT("114"); break;
			case 115: string = wxT("115"); break;
			case 116: string = wxT("116"); break;
			case 117: string = wxT("117"); break;
			case 118: string = wxT("118"); break;
			case 119: string = wxT("119"); break;
			default : string = wxT("Unknown Keycode"); break;
		}

		return string;
	};
};

#endif //KEYTOSTRING_H
