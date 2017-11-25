#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <assert.h>
#include "json/json.h"

using namespace std;

//一次性读取文件中的全部内容
string readFile(const string &fileName)
{
    ifstream fs(fileName);

#if 0
    stringstream tmp;
    tmp << fs.rdbuf();

    return tmp.str();
#else
    istreambuf_iterator<char> beg(fs);
    istreambuf_iterator<char> end;
    return string(beg, end);
#endif
}

int main()
{
    Json::Reader reader;
    Json::Value root;
    bool ret = reader.parse(readFile("../test-json/test1.json"), root);
    if(ret)
    {
        cout << root["name"].asString() << endl;
        cout << root["sex"].asString() << endl;
    }
    cout << '\n';

    root.clear();
    ret = reader.parse(readFile("../test-json/test2.json"), root);
    if(ret)
    {
        Json::Value &info = root["info"];
        cout << info["name"].asString() << endl;
        cout << info["sex"].asString() << endl;
        cout << info["age"].asInt() << endl;
        cout << info["height"].asDouble() << endl;
    }
    cout << '\n';

    root.clear();
    ret = reader.parse(readFile("../test-json/test3.json"), root);
    if(ret)
    {
        Json::Value &info = root["class"];
        assert(info.isArray());
        for(auto iter = info.begin(); iter != info.end(); ++iter)
        {
            cout << (*iter)["name"].asString() << endl;
            cout << (*iter)["sex"].asString() << endl;
        }
    }
    cout << '\n';

    root.clear();
    ret = reader.parse(readFile("../test-json/test4.json"), root);
    if(ret)
    {
        {
            Json::Value &info = root["info"];
            cout << info["name"].asString() << endl;
            cout << info["sex"].asString() << endl;
            cout << info["age"].asInt() << endl;
            cout << info["height"].asDouble() << endl;
        }

        Json::Value &info = root["class"];
        assert(info.isArray());
        for(auto iter = info.begin(); iter != info.end(); ++iter)
        {
            cout << (*iter)["name"].asString() << endl;
            cout << (*iter)["sex"].asString() << endl;
        }
    }
    cout << '\n';

    cout << "Hello World!" << endl;
    return 0;
}
