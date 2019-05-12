#include <benchmark/benchmark.h>
#include <array>
#include <memory>


struct StInfo
 {
     uint32_t lb = {0};
     uint32_t protocol = {0};
 };
typedef std::string SessionType;
typedef std::string SessionKey;
typedef std::map<SessionType, StInfo> SessionTypeInfo;
typedef unsigned long long U64;
typedef unsigned int U32;
struct Session
 {
     Session(const SessionType& type, const SessionKey& key, U64 NumServlet);
     ~Session();
     U64 getPeerServletId() {return peerNumServletId;}
     U32 getGenAffDirect(){return genAffDirect;}
     U32 getMatchPriority(){return matchPriority;}

     void setGenAffDirect(U32 direct){genAffDirect = direct;}
     void setMatchPriority(U32 priority){matchPriority = priority;}

     U32 getSrcWorkerId() {return srcWorkerId;}
 private:
     SessionType type;
     SessionKey key;
     U64 peerNumServletId;
     bool preDeleteFlag = false;
     U32 matchPriority = 0;
     U32 genAffDirect = 0;
     U64 affFirstPkgTime = 0;
     U32 srcWorkerId = 0;
};

 Session::Session(const SessionType& type, const SessionKey& key, U64 NumServlet): type(type), key(key), peerNumServletId(NumServlet)
 {
 }
 
 Session::~Session()
 {
 }

#include <random>
#include <string>

std::string random_string()
{
     std::string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

     std::random_device rd;
     std::mt19937 generator(rd());

     std::shuffle(str.begin(), str.end(), generator);

     return str.substr(0, 32);    // assumes 32 < number of characters in str         
}

//std::string rstr = random_string();

static void map_insert(benchmark::State& state)
{
    U64 peerNumServletId = 123;
    SessionType type = "rand_type";
    std::map<SessionKey, std::shared_ptr<Session>> sessions;
    
    int i = 1;
    for (auto _: state) {
    state.PauseTiming();
    SessionKey key = random_string();
    state.ResumeTiming();
    auto session = std::make_shared<Session>(type, key, peerNumServletId);
    sessions.insert(std::make_pair(key, session));
    }
}

BENCHMARK(map_insert);
BENCHMARK_MAIN();

