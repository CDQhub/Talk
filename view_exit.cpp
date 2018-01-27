#include <iostream>
#include "view_exit.h"
#include <mysql/mysql.h>
#include <errno.h>
#include <string>
#include <string.h>
#include <sys/socket.h>
using namespace std;

extern pthread_mutex_t mutex;

view_exit::view_exit(void *mpcon)
{
    _mpcon = (MYSQL *)mpcon;
}

void view_exit::process(Json::Value value, int cli_fd)
{
    _cli_fd = cli_fd;
    _flag = false;

    MYSQL *mpcon = _mpcon;
    MYSQL_RES * mp_res;
    MYSQL_ROW mp_row;

    if(mysql_select_db(mpcon,"talk"))
    {
        cerr << "select fail; errno:" << errno << endl;
        return;
    }

    pthread_mutex_lock(&mutex);
    //访问在线表
    string cmd = "DELETE FROM online WHERE name='';";
    cmd.insert(cmd.size()-2, value["name"].asString().c_str());
    if(mysql_real_query(mpcon, cmd.c_str(), cmd.size()))
    {
        cerr << "0 query fail; errno:" << errno << endl;
        return;
    }
    pthread_mutex_unlock(&mutex);
    _flag = true;
}


void view_exit::responce()
{
    if(_flag)
    {
        //退出成功
        char buff[] = "退出成功";
        send(_cli_fd, buff, strlen(buff), 0);
    }
    else
    {
        //退出失败
        char buff[] = "退出失败，请稍候重试";
        send(_cli_fd, buff, strlen(buff), 0);
    }
}
