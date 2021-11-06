//
// Created by Ethan on 2021-11-05.
//

#ifndef MULTITHREADEDSERVER_C_HTTPSERVLET_HPP
#define MULTITHREADEDSERVER_C_HTTPSERVLET_HPP

#include "HttpServletRequest.h"
#include "HttpServletResponse.h"

class HttpServlet {
public:
    HttpServlet(){};
    virtual void doGet(HttpServletRequest request, HttpServletResponse response){};
    virtual void doPost(HttpServletRequest request, HttpServletResponse response){};
    virtual ~HttpServlet()= default;
};


#endif //MULTITHREADEDSERVER_C_HTTPSERVLET_HPP
