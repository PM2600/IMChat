// jsonStudy.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#elif defined(_MSC_VER)
#pragma warning(disable : 4996)


#include <iostream>
#include "../jsonlib/json.h"
#include <string>
#include <MsXml2.h>
#include "XmlDocument.h"
#include <Windows.h>

void jsonTest() {
    FILE* pFile = fopen("json.txt", "r");
    if (pFile) {
        std::string buffer;
        buffer.resize(4096);
        size_t len = fread((char*)buffer.c_str(), 1, 4096, pFile);
        fclose(pFile);
        buffer.resize(len);
        Json::Value root;
        Json::Reader reader;
        if (reader.parse(buffer, root)) {
            auto members = root.getMemberNames();
            for (unsigned i = 0; i < members.size(); i++) {
                std::cout << members[i] << "==>" << root[members[i]].toStyledString() << std::endl;
            }
        }
        std::string data = root.toStyledString();
        std::cout << data << std::endl;
    }
}

std::string toString(const std::wstring str) {
    int len = WideCharToMultiByte(CP_ACP, 0, str.c_str(), -1, NULL, 0, NULL, 0);
    std::string ret;
    if (len <= 0) {
        return ret;
    }
    ret.resize(len);
    WideCharToMultiByte(CP_ACP, 0, str.c_str(), -1, (char*)ret.c_str(), len, NULL, NULL);
    return ret;
}
void xmlTest() {
    CoInitialize(NULL); // COM初始化
    CXmlDocument doc;
    CXmlNode root, face;
    BOOL ret = doc.Load(_T("FaceConfig.xml"));
    if (!ret) {
        std::cout << "load xml failed" << std::endl;
        return;
    }
    ret = doc.SelectSingleNode(_T("/faceconfig"), root);
    if (ret) {
        std::cout << "row: " << root.GetAttributeInt(_T("row")) << std::endl;
        std::cout << "col: " << root.GetAttributeInt(_T("col")) << std::endl;
        std::cout << "item_width: " << root.GetAttributeInt(_T("item_width")) << std::endl;
        std::cout << "item_height: " << root.GetAttributeInt(_T("item_height")) << std::endl;
        std::cout << "zoom_width: " << root.GetAttributeInt(_T("zoom_width")) << std::endl;
        std::cout << "zoom_height: " << root.GetAttributeInt(_T("zoom_height")) << std::endl;
        ret = root.GetFirstChildNode(_T("face"), face);
        while (ret) {
            std::cout << "id: " << face.GetAttributeInt(_T("id")) << std::endl;
            std::cout << "tip: " << toString(face.GetAttribute(_T("tip"))) << std::endl;
            std::cout << "file: " << toString(face.GetAttribute(_T("file"))) << std::endl;
            ret = face.GetNextSiblingNode(face);
        }
    }
    face.Release();
    root.Release();
    doc.Release();
    CoUninitialize();
}

int main()
{
    //jsonTest();
    xmlTest();
    return 0;
}

#endif