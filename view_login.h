#pragma once
#ifndef VIEW_LOGIN
#define VIEW_LOGIN

#include "view.h"
#include <string>
#include <mysql/mysql.h>

class view_login() : public view
{
public:
	view_login(MYSQL *mpcon);
	~view_login(){}
	void process(Json::Value val, int cli_fd);
	void responce();
private:
	string _message;
	MYSQL *mpcon;
	int _cli_fd;
	bool _flag;
};

#endif // !VIEW_LOGIN