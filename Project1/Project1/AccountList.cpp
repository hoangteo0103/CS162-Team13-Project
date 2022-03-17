#include "AccountList.h"

void addAccount(Account*& listHead, Account*& listLast, std::string account, std::string password) {
	if (!listHead) {
		listHead = new Account;
		listHead->accnt = account;
		listHead->psswrd = password;
		listHead->nextStudent = nullptr;
		listLast = listHead;
		return;
	}

	Account* tmp = new Account;
	tmp->accnt = account;
	tmp->psswrd = password;
	tmp->nextStudent = nullptr;
	listLast->nextStudent = tmp;
	listLast = listLast->nextStudent;
}

bool findStudent(Account* listHead, std::string accnt, std::string psswrd) {
	for (Account* i = listHead; i; i = i->nextStudent) {
		if (!(i->accnt.compare(accnt)) && !(i->psswrd.compare(psswrd))) {
			return true;
		}
	}
	return false;
}

void delList(Account* listHead) {
	if (listHead->nextStudent) {
		delList(listHead->nextStudent);
	}
	delete listHead;
}