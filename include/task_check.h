#ifndef TASKCHECK_H
#define TASKCHECK_H
#include <utility>


class TaskCheck
{
	public:
		TaskCheck();

		bool operator()();

		void swap(TaskCheck &check) 
		{
			std::swap(x_,check.x_);
			std::swap(y_,check.y_);
			/*scriptPubKey.swap(check.scriptPubKey);
			std::swap(ptxTo, check.ptxTo);
			std::swap(amount, check.amount);
			std::swap(nIn, check.nIn);
			std::swap(nFlags, check.nFlags);
			std::swap(cacheStore, check.cacheStore);
			std::swap(error, check.error);
			std::swap(txdata, check.txdata);*/

		}

		bool operator()(int x,int y)
		{
			 x_ = x + y;
			 y_ = x*y;
			return true;
		}

private:

	int x_;
	int y_;
	int z_;
	
};

#endif
