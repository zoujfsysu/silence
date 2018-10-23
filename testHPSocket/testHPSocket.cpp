// testHPSocket.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "hpsocket/hpsocket.h"
#include "rapidjson/writer.h"
#include "rapidjson/document.h"
#include <string.h>
#include <map>
using namespace std;
#pragma comment(lib, "HPSocket.lib")

typedef struct teststruct
{
    int a;
}*LPTESTSTRUCT;

int main()
{
    map<int, int> mapTest;
    char * pTemp = new char[12];
    char * pImageBase64[20];
    for (int i = 0; i < 20; i++)
    {
        pImageBase64[i] = new char[12];
    }
    for (int i = 0; i < 110; i++)
    {
        mapTest.insert(make_pair(i, i));
    }
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType&allocator = document.GetAllocator();

    map<int, int>::iterator it = mapTest.begin();
    while (it != mapTest.end())
    {
        rapidjson::Value array(rapidjson::kArrayType);
        int i = 0;
        while (it != mapTest.end())
        {
            if (i < 20)
            {
                sprintf_s(pImageBase64[i], 12, "%d", it->second);
                rapidjson::Value object(rapidjson::kObjectType);
                object.AddMember("name", rapidjson::StringRef(pImageBase64[i]), allocator);
                object.AddMember("face", it->first, allocator);
                array.PushBack(object, allocator);

                i++;
                it++;
                if (i < 20 && it != mapTest.end())
                {
                    continue;
                }
            }

            {
                document.AddMember("type", 100100, allocator);
                document.AddMember("number", array, allocator);

                rapidjson::StringBuffer buffer;
                rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
                document.Accept(writer);
                string sDelInfo = string(buffer.GetString());
                printf("%s\n", sDelInfo.c_str());

                i = 0;
                document.RemoveAllMembers();
                break;
            }
        }
    }
    


    LPTESTSTRUCT ptest = new teststruct;
    ptest->a = 100;
    LPTESTSTRUCT ptest2 = ptest;
    ptest = NULL;

    printf("%d\n", ptest2->a);

    char pTest[1024] = { 0 };
    char pURL[1024] = "rtsp://%s:%d@%s:%d/123";
    sprintf_s(pTest, pURL, "admin", "xinyi2513", "172.1.1.1", 554, 1, 3, 4);

    CHttpServerPtr pServer(NULL);
    pServer->SetSocketListenQueue(100);

    CHttpSyncClientPtr pClient(NULL);
    pClient->OpenUrl("POST", "http://127.0.0.1:8800/hellworld", NULL, 0, (const BYTE*)"<\"json\":\"format\">", 17);
    LPCBYTE pImageBuf = NULL;
    int nImageLen = 0;
    pClient->GetResponseBody(&pImageBuf, &nImageLen);
    printf("%s\n", pImageBuf);
    getchar();

    /*CHttpSyncClientPtr pClient(NULL);
    pClient->OpenUrl("GET", "http://35.24.22.179/D/StoreSTLibServer/92/B9FDC0E2E9BF4b4498D1CDB0738370D3.jpg");
    LPCBYTE pImageBuf = NULL;
    int nImageLen = 0;
    pClient->GetResponseBody(&pImageBuf, &nImageLen);*/
    return 0;
}

