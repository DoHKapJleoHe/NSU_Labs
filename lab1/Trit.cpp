#include "Trit.h"

Trit operator ~ (Trit trit1)
{
	if (trit1 == TRUE)
		return FALSE;
	else if (trit1 == FALSE)
		return TRUE;
	else
		return UNKNOWN;
}

Trit operator & (Trit trit1, Trit trit2)
{
	if (trit1 == FALSE || trit2 == FALSE)
		return FALSE;
	else if (trit1 == TRUE && trit2 == TRUE)
		return TRUE;
	else
		return UNKNOWN;
}

Trit operator | (Trit trit1, Trit trit2)
{
	if (trit1 == TRUE || trit2 == TRUE)
		return TRUE;
	else if (trit1 == FALSE && trit2 == FALSE)
		return FALSE;
	else
		return UNKNOWN;
}
