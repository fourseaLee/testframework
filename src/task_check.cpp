#include "task_check.h"
#include <iostream>
TaskCheck::TaskCheck()
{
	z_ = 0;
}

bool TaskCheck::operator() ()
{
	

	 z_ = x_ + y_ ;

	std::cout << "z:" << z_ << std::endl;
	std::cout << "x:" << x_ << std::endl;
	std::cout << "y:" << y_ << std::endl;
	std::cout << "taskcheck test" << std::endl;
	return true;
}


