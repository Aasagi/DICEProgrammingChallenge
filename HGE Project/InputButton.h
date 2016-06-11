#ifndef _INPUT_BUTTON_H_
#define _INPUT_BUTTON_H_

enum class eButton
{
	eLEFTMOUSE		= 0x01,		// 1
	eRIGHTMOUSE		= 0x02,		// 2
	eMIDDLEMOUSE	= 0x04,		// 4
	eESCAPE			= 0x1B,		// 27
	eBACKSPACE		= 0x08,		// 8
	eTAB			= 0x09,		// 9
	eENTER			= 0x0D,		// 13
	eSPACE			= 0x20,		// 32
	eSHIFT			= 0x10,		// 16
	eCTRL			= 0x11,		// 17
	eALT			= 0x12,		// 18
	eLWIN			= 0x5B,		// 91
	eRWIN			= 0x5C,		// 92
	eAPPS			= 0x5D,		// 93
	ePAUSE			= 0x13,		// 19
	eCAPSLOCK		= 0x14,		// 20
	eNUMLOCK		= 0x90,		// 144
	eSCROLLLOCK		= 0x91,		// 145
	ePGUP			= 0x21,		// 33
	ePGDN			= 0x22,		// 34
	eHOME			= 0x24,		// 36
	eEND			= 0x23,		// 35
	eINSERT			= 0x2D,		// 45
	eDELETE			= 0x2E,		// 46
	eLEFT			= 0x25,		// 37
	eUP				= 0x26,		// 38
	eRIGHT			= 0x27,		// 39
	eDOWN			= 0x28,		// 40
	e0				= 0x30,		// 48
	e1				= 0x31,		// 49
	e2				= 0x32,		// 50
	e3				= 0x33,		// 51
	e4				= 0x34,		// 52
	e5				= 0x35,		// 53
	e6				= 0x36,		// 54
	e7				= 0x37,		// 55
	e8				= 0x38,		// 56
	e9				= 0x39,		// 57
	eA				= 0x41,		// 65
	eB				= 0x42,		// 66
	eC				= 0x43,		// 67
	eD				= 0x44,		// 68
	eE				= 0x45,		// 69
	eF				= 0x46,		// 70
	eG				= 0x47,		// 71
	eH				= 0x48,		// 72
	eI				= 0x49,		// 73
	eJ				= 0x4A,		// 74
	eK				= 0x4B,		// 75
	eL				= 0x4C,		// 76
	eM				= 0x4D,		// 77
	eN				= 0x4E,		// 78
	eO				= 0x4F,		// 79
	eP				= 0x50,		// 80
	eQ				= 0x51,		// 81
	eR				= 0x52,		// 82
	eS				= 0x53,		// 83
	eT				= 0x54,		// 84
	eU				= 0x55,		// 85
	eV				= 0x56,		// 86
	eW				= 0x57,		// 87
	eX				= 0x58,		// 88
	eY				= 0x59,		// 89
	eZ				= 0x5A,		// 90
	eGRAVE			= 0xC0,		// 192
	eMINUS			= 0xBD,		// 189
	eEQUALS			= 0xBB,		// 187
	eBACKSLASH		= 0xDC,		// 220
	eLBRACKET		= 0xDB,		// 219
	eRBRACKET		= 0xDD,		// 221
	eSEMICOLON		= 0xBA,		// 186
	eAPOSTROPHE		= 0xDE,		// 222
	eCOMMA			= 0xBC,		// 188
	ePERIOD			= 0xBE,		// 190
	eSLASH			= 0xBF,		// 191
	eNUMPAD0		= 0x60,		// 96
	eNUMPAD1		= 0x61,		// 97
	eNUMPAD2		= 0x62,		// 98
	eNUMPAD3		= 0x63,		// 99
	eNUMPAD4		= 0x64,		// 100
	eNUMPAD5		= 0x65,		// 101
	eNUMPAD6		= 0x66,		// 102
	eNUMPAD7		= 0x67,		// 103
	eNUMPAD8		= 0x68,		// 104
	eNUMPAD9		= 0x69,		// 105
	eMULTIPLY		= 0x6A,		// 106
	eDIVIDE			= 0x6F,		// 111
	eADD			= 0x6B,		// 107
	eSUBTRACT		= 0x6D,		// 109
	eDECIMAL		= 0x6E,		// 110
	eF1				= 0x70,		// 112
	eF2				= 0x71,		// 113
	eF3				= 0x72,		// 114
	eF4				= 0x73,		// 115
	eF5				= 0x74,		// 116
	eF6				= 0x75,		// 117
	eF7				= 0x76,		// 118
	eF8				= 0x77,		// 119
	eF9				= 0x78,		// 120
	eF10			= 0x79,		// 121
	eF11			= 0x7A,		// 122
	eF12			= 0x7B,		// 123
};

class InputButton
{
public:
	InputButton(void)
	{
		myCurrentState = false;
		myLastState = false;
	} 

	~InputButton(void) { }

	eButton myButton;
	bool myCurrentState;
	bool myLastState;

private:

};

#endif