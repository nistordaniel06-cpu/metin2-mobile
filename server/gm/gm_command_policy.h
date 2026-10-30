#pragma once
// Drakon2: standalone, server-side GM command policy.
// Integration with m2dev command dispatcher is still required.
#include <algorithm>
#include <charconv>
#include <system_error>
#include <cctype>
#include <cstddef>
#include <sstream>
#include <string>
#include <vector>

namespace drakon2 {
enum class Role { Player=0, Helper=1, GM=2, Admin=3, Owner=4 };
struct Decision {
    bool allowed;
    std::string reason;
    std::string command;
    std::vector<std::string> args;
};
inline Role required_role(const std::string& cmd) {
    if (cmd=="gmhelp" || cmd=="where" || cmd=="who") return Role::Helper;
    if (cmd=="goto" || cmd=="bring" || cmd=="notice" || cmd=="kick") return Role::GM;
    if (cmd=="spawn" || cmd=="killmob" || cmd=="item" || cmd=="setlevel" ||
        cmd=="setyang" || cmd=="ban" || cmd=="unban" || cmd=="event") return Role::Admin;
    return Role::Owner;
}
inline bool known_command(const std::string& cmd) {
    static const char* names[]={"gmhelp","where","who","goto","bring","notice","kick",
        "spawn","killmob","item","setlevel","setyang","ban","unban","event","shutdown"};
    for (const auto* name : names) if (cmd==name) return true;
    return false;
}
inline bool bounded_integer(const std::string& value, long long low, long long high) {
    long long parsed=0;
    const char* begin=value.data();
    const char* end=begin+value.size();
    const auto result=std::from_chars(begin,end,parsed);
    return result.ec==std::errc{} && result.ptr==end && parsed>=low && parsed<=high;
}
inline bool valid_args(const std::string& command, const std::vector<std::string>& args) {
    const auto count=args.size();
    if (command=="gmhelp" || command=="where" || command=="who") return count==0;
    if (command=="goto" || command=="bring" || command=="unban" || command=="killmob")
        return count==1;
    if (command=="notice") return count>=1;
    if (command=="kick") return count>=2;
    if (command=="spawn" || command=="item")
        return count==2 && bounded_integer(args[0],1,99999999) && bounded_integer(args[1],1,20);
    if (command=="setlevel")
        return count==2 && bounded_integer(args[1],1,120);
    if (command=="setyang")
        return count==2 && bounded_integer(args[1],0,2000000000LL);
    if (command=="ban")
        return count>=3 && bounded_integer(args[1],1,43200);
    if (command=="event")
        return count==2 && (args[1]=="start" || args[1]=="stop");
    return false;
}
inline Decision authorize(Role serverAuthenticatedRole, const std::string& input) {
    if (input.size()>256 || input.empty() || input[0]!='/')
        return {false,"invalid input","",{}};
    for (unsigned char c : input)
        if (c<32 || c==127) return {false,"control characters rejected","",{}};
    std::istringstream stream(input.substr(1));
    std::string command;
    stream>>command;
    if (!known_command(command)) return {false,"unknown command",command,{}};
    if (static_cast<int>(serverAuthenticatedRole)<static_cast<int>(required_role(command)))
        return {false,"insufficient privilege",command,{}};
    std::vector<std::string> args;
    std::string arg;
    while (stream>>arg) {
        if (args.size()>=32) return {false,"too many arguments",command,{}};
        args.push_back(arg);
    }
    if (command=="shutdown") return {false,"console-only command",command,{}};
    if (!valid_args(command,args)) return {false,"invalid command arguments",command,{}};
    return {true,"authorized; handler must validate arguments and audit",command,args};
}
} // namespace drakon2
