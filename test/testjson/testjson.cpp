#include "json.hpp"
using json = nlohmann::json;

#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

string func1()
{
    json js;
    js["msg_type"] = 2;
    js["from"] = "zhang san";
    js["to"] = "li si";
    js["msg"] = "hello, what are you doing now?";

    string sendBuf = js.dump();
    cout << sendBuf.c_str() << endl;
    return sendBuf;
}

void func2()
{
    json js;
    js["id"] = {1, 2, 3, 4, 5};
    js["name"] = "zhang san";
    js["msg"]["zhang san"] = "hello world";
    js["msg"]["liu shuo"] = "hello world!";
    js["msg"] = {{"zhang san", "hello world"}, {"liu shuo", "hello world!!!"}};
    cout << js << endl;
}

void func3()
{
    json js;

    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    js["list"] = vec;

    map<int, string> m;
    m.insert({1, "黄山"});
    m.insert({2, "华山"});
    m.insert({3, "泰山"});

    js["path"] = m;

    string sendBuf = js.dump();
    cout << sendBuf.c_str() << endl;
}

int main()
{
    string recvBuf = func1();
    func2();
    func3();

    //数据的反序列化
    json jsbuf = json::parse(recvBuf);
    cout << jsbuf["msg_type"] << endl;
    cout << jsbuf["from"] << endl;
    cout << jsbuf["to"] << endl;
    cout << jsbuf["msg"] << endl;
    return 0;
}