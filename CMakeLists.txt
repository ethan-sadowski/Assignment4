cmake_minimum_required(VERSION 3.20)
project(assignment4)

set(CMAKE_CXX_STANDARD 14)

add_executable(assignment4
        socketclient.cc
        ServerSocket.cpp
        ServerSocket.h
        Socket.cpp
        Socket.h
        Thread.cpp
        Thread.h
        multithreadedserver.cpp
        ServerThread.cpp
        ServerThread.h
        HttpServletRequest.cpp
        HttpServletRequest.h
        HttpServletResponse.cpp
        HttpServletResponse.h
        HttpServlet.cpp
        HttpServlet.h
        UploadServlet.cpp
        UploadServlet.h)
