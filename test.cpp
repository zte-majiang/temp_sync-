


 
 
 
 struct SubSTInfo
 {
     bool isBlock{false};
     uint64_t ipPort{0};
 };
 
 typedef std::map<SessionType, SubSTInfo> SubSessionTypeInfo;
 typedef std::map<SessionType, StInfo> SessionTypeInfo;
 

./pub-sub/common/include/common/PubSubConst.h:44:typedef std::string SessionId;  // SessionId = SessionType + "/" + SessionKey
./pub-sub/common/include/common/PubSubConst.h:45:typedef std::string SessionType;
./pub-sub/common/include/common/PubSubConst.h:46:typedef std::string SessionKey;


 
=================================================================
#include <benchmark/benchmark.h>
#include <array>

constexpr int len = 6;

// constexpr function具有inline属性，你应该把它放在头文件中
constexpr auto my_pow(const int i)
{
    return i * i;
}

// 使用operator[]读取元素，依次存入1-6的平方
static void bench_array_operator(benchmark::State& state)
{
    std::array<int, len> arr;
    constexpr int i = 1;
    for (auto _: state) {
        arr[0] = my_pow(i);
        arr[1] = my_pow(i+1);
        arr[2] = my_pow(i+2);
        arr[3] = my_pow(i+3);
        arr[4] = my_pow(i+4);
        arr[5] = my_pow(i+5);
    }
}
BENCHMARK(bench_array_operator);

// 使用at()读取元素，依次存入1-6的平方
static void bench_array_at(benchmark::State& state)
{
    std::array<int, len> arr;
    constexpr int i = 1;
    for (auto _: state) {
        arr.at(0) = my_pow(i);
        arr.at(1) = my_pow(i+1);
        arr.at(2) = my_pow(i+2);
        arr.at(3) = my_pow(i+3);
        arr.at(4) = my_pow(i+4);
        arr.at(5) = my_pow(i+5);
    }
}
BENCHMARK(bench_array_at);

// std::get<>(array)是一个constexpr function，它会返回容器内元素的引用，并在编译期检查数组的索引是否正确
static void bench_array_get(benchmark::State& state)
{
    std::array<int, len> arr;
    constexpr int i = 1;
    for (auto _: state) {
        std::get<0>(arr) = my_pow(i);
        std::get<1>(arr) = my_pow(i+1);
        std::get<2>(arr) = my_pow(i+2);
        std::get<3>(arr) = my_pow(i+3);
        std::get<4>(arr) = my_pow(i+4);
        std::get<5>(arr) = my_pow(i+5);
    }
}
BENCHMARK(bench_array_get);

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


static void map_insert(benchmark::State& state)
{
    U64 peerNumServletId = 123;
    SessionType type = "rand_type";
    std::map<SessionKey, std::shared_ptr<Session>> sessions;
    
    int i = 1;
    for (auto _: state) {
    SessionKey key = 
    Session session = std::make_shared<Session>(type, key, peerNumServletId);
    sessions.insert(std::make_pair(key, session));
    }
}
BENCHMARK_MAIN();
