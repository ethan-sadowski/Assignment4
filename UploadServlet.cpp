//
// Created by Ethan on 2021-11-05.
//

#include <mutex>
#include "UploadServlet.h"
#include <filesystem>
#include <fstream>
#include <string>
#include <iterator>



//using namespace std;

using std::filesystem::directory_iterator;

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
    string fileType = req.getHeader("Filename");
    fileType = fileType.erase(0, fileType.length() - 3);
    string path = "../Images/";
    string imageName = req.getHeader("Caption") + req.getHeader("Date") + "." + fileType;
    string fileName = path.append(imageName);

    /* Saves Image bytes to ../Images directory */
    cout << "Saving Image" << endl;
    ofstream file;
    file.open(fileName);
    for(int i = 0; i < req.getImageData().size(); i++) {
        file << req.getImageData().at(i);
    }
    file.close();

    /* Generating HTML listing the names of each image in ../Images */
    path = "../Images/";
    unsigned int pathChar = path.length();
    string htmlString = "HTTP/1.1 200 OK\r\n"
                        "Content-Type: text/html\r\n\r\n"
                        "<!DOCTYPE html>"
                        "<html><body><ul>";

    for (const auto &file: directory_iterator(path)) {
        string imgName = file.path().c_str();
        string fileType = file.path().c_str();

        unsigned int filePathChar = imgName.length();

        imgName = imgName.substr(pathChar, filePathChar - 4);
        fileType = fileType.substr(filePathChar - 4);
        cout << imgName << endl;
        htmlString += "<li>" + imgName + "</li>";
    }
    htmlString += "</ul></body> </html>";
    res.print(htmlString);
}
