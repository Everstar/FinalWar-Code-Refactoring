#include "BossState.h"

void BossState::SetContext(Boss* context)
{
	this->_context = context;
	this->init();
}