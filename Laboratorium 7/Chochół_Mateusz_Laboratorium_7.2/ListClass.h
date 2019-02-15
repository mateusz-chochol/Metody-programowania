#ifndef LISTCLASS_H
#define LISTCLASS_H

/*
 * W C++ classa od structa rozni sie jedynie hermetyzacja danych (w structcie wszystko jest defaultowo publiczne, w klasie - prywatne),
 * dlatego tez daruje sobie tworzenie structa i powtarzania wszystkiego na nim
 */
class List
{
public:
	List *next;
	int value;
};

#endif // !LISTCLASS_H