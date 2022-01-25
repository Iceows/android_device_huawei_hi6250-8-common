#define LOG_TAG "mploader"

#include <cutils/log.h>
#include <cutils/properties.h>

#include <cstring>
#include <string>
#include <vector>

#include <fstream>
#include <sstream>
#include <iostream>

std::vector<std::string> split_prop(const char *str)
{
    std::vector<std::string> result;
    do
    {
        const char *begin = str;
        while(*str != '=' && *str)
            str++;

        result.push_back(std::string(begin, str));
    } while (0 != *str++);

    return result;
}

int get_props_offset(std::ifstream &f, std::string pid) {
    int offset = -1;
    std::string buf;

    while (std::getline(f, buf)) {
        if (buf.find(pid) != std::string::npos) {
            offset = f.tellg(); break;
        }
    }

    return offset;
}

std::string read_phone_id() {
    std::ifstream cmdline;
    std::string phoneid, buf;

    cmdline.open("/proc/cmdline");
    if (!cmdline.is_open())
        return "0X00000000";

    while (std::getline(cmdline, buf, ' ')) {
        if (buf.find("productid") != std::string::npos) {
            break;
        }
    }

    if (buf.find("productid") != 0)
        return "0X00000000";

    cmdline.close();

    for (int i = 0; i < buf.size(); i++) {
    	if (i > 9) {
       		phoneid.push_back(toupper(buf[i]));
    	}
    }

    return phoneid;
}

int load_props(std::ifstream &f, std::string pid) {
    std::string buf;
    std::vector<std::string> prop;

    int off = get_props_offset(f, pid);

    if (off == -1)
        return off;

    f.seekg(off);

    while (std::getline(f, buf)) {
        if (buf.length() == 0) break;
        prop = split_prop(buf.c_str());
        __system_property_set(prop[0].c_str(), prop[1].c_str());
    }

    return 0;
}

int main() {
    std::string pid = read_phone_id();
    std::ifstream f("/vendor/phone.prop");

    ALOGI("Loading phone properties for %s...", pid.c_str());
    int ret = load_props(f, pid);
    ALOGI("%s", ret == 0 ? "Success!" : "Fail!");
    __system_property_set("sys.rilprops_ready",  (ret == 0 ? "1" : "0"));

    f.close();
    return ret;
}
