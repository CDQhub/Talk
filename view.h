#pragma once
#ifndef VIEW_H
#define VIEW_H

#include <mysql/mysql.h>

class view
{
public:
	virtual void process() = 0;
	virtual void responce() = 0;
protected:
	MYSQL *mpcon;
};

#endif // !VIEW_H