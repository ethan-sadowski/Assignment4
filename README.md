COMP 3940 Assignment 4
  - 

In order to run this project, pull the master branch and compile it by using
the command:

    c++ HttpServlet.h HttpServletRequest.h HttpServletResponse.h multithreadedserver.cpp ServerSocket.h ServerThread.cpp
    ServerThread.h Socket.cpp Socket.h Thread.cpp Thread.h UploadServlet.h UploadServlet.cpp ServerSocket.cpp

Access the server at localhost:9999 or change the port address inside multithreadedserver.cpp to whatever you wish

Run the client against the server buy compiling socketclient.cc

In order to use the client you must list an image in the same root directory as the location the client is being executed, as well as a caption and a date. Each of these elements should be separated by a single space character

Currently working functionality:
- Multi Threading
- Browser Image Upload
- Client Image Upload
- Client Json response from server
- Browser Upload Works with PDFs and correctly formatted text files
- List of images saved by the server displays after upload
- Object oriented server structure
- Custom Caption Missing Exception
