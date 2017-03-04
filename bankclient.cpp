#include "bankclient.h"

BankClient::BankClient() :
	deposit_(0.0),
	debt_(0.0),
	company_(nullptr)
{ }

BankClient::~BankClient() { }

void BankClient::update() { }
