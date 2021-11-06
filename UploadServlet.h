//
// Created by Ethan on 2021-11-05.
//

#ifndef MULTITHREADEDSERVER_C_UPLOADSERVLET_H
#define MULTITHREADEDSERVER_C_UPLOADSERVLET_H


#include "HttpServletRequest.h"
#include "HttpServletResponse.h"
#include "HttpServlet.h"

class UploadServlet : public HttpServlet {
private:
public:
    UploadServlet()= default;
    void doGet(HttpServletRequest req, HttpServletResponse res) override;
    void doPost(HttpServletRequest req, HttpServletResponse res) override;
    ~UploadServlet() override = default;
};


#endif //MULTITHREADEDSERVER_C_UPLOADSERVLET_H
