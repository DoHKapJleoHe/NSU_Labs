#pragma once

enum Trit
{
	FALSE = 1,
	UNKNOWN = 0,
	TRUE = 2
};

Trit operator ~ (Trit Trit);
Trit operator & (Trit trit1, Trit trit2);
Trit operator | (Trit trit1, Trit trit2);
