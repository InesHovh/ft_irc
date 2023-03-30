#pragma once

class Server;

#include <unistd.h>
#include <fcntl.h>
#include <map>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/select.h>

#include "User.hpp"
#include "Channel.hpp"
#include "Commands/CommandHandler.hpp"
class User;
class Channel;
class CommandHandler;

class Server
{
public:

    typedef std::map<int, User*>::iterator  iterator;

    Server(short port, const std::string& pass);

    ~Server();

    std::string get_password();
    User*     get_user(const std::string& nickname);
    Channel*    get_channel(const std::string& name);
    Channel*    add_channel(const std::string& name, const std::string& pass);

    void    set_user(User* client, const std::string& nick, int fd);
    void    delete_user(iterator& it);
    void    checkClientFd();
    short   getPort() const;

private:
    short       _port;
    std::string _pass;

    int         server_fd;
    sockaddr_in address;

    std::map<int, User*>          _user;
    std::map<std::string, int>      _new_user;
	std::map<std::string, Channel*>	_channel;
	CommandHandler*	                _commandHandler;

    void    init_server();

    void    run();
    bool    ft_buffer(iterator& it);

    void    new_user();

    Server();
    Server& operator=(const Server& other);
};