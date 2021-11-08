//
// Created by Ethan on 2021-11-05.
//

#include <mutex>
#include "UploadServlet.h"


using namespace std;

void UploadServlet::doGet(HttpServletRequest& req, HttpServletResponse& res) {
    string body =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n\r\n"
        "<!DOCTYPE html>"
        "<html><head><title>File Upload Form</title></head>"
        "<body><h1>Upload file</h1>"
        "<form method=\"POST\" action=\"upload\" "
        "enctype=\"multipart/form-data\">"
        "<input type=\"file\" name=\"fileName\"/><br/><br/>"
        "Caption: <input type=\"text\" name=\"caption\"/><br/><br/>"
        "<br />"
        "Date: <input type=\"date\" name=\"date\"/><br/><br/>"
        "<br />"
        "<input type=\"submit\" value=\"Submit\"/>"
        "</form>"
        "</body></html>\r\n";
    res.print(body);
}

void UploadServlet::doPost(HttpServletRequest& req, HttpServletResponse& res) {
//    std::ofstream file("../Images/picture.png",
//                       std::ofstream::binary | std::ofstream::out);
//    char* buffer[1024];
//    for(int i = 0; i < req.getImageData().size(); i++) {
//        file.write(req.getImageData().at(i), ios::binary);
//    }
//
//    file.close();

}
