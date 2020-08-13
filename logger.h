#ifndef __LOGGER
#define __LOGGER

#include <iostream>
#include <sstream>
#include <mutex>
#include <chrono>
#include <ctime>

typedef enum
{
    ERROR,
    WARNNING,
    DEBUG,
    VERBOSE,
    INFO
} Severity;

static std::string severity_str[] = {"ERROR", "WARN", "DEBUG", "VERBOSE", "INFO"};

class Logger
{
private:
    Logger() {}
    ~Logger() {}
    Logger &operator=(const Logger &) = delete;
    Logger(const Logger &) = delete;

private:
    static Severity m_severity;
    static std::string m_filename;
    static int m_line;
    static std::string m_funcname;
    std::stringstream ss;
    std::mutex m_lk;

public:
    static Logger &Instance(Severity s = Severity::INFO,
                            const char *f = "", int l = 0, const char *fc = "")
    {
        static Logger instance_;

        instance_.m_severity = s;
        instance_.m_filename = f;
        instance_.m_line = l;
        instance_.m_funcname = fc;
        return instance_;
    }

    static void Init(Severity s)
    {
        m_severity = s;
    }

    Logger &operator<<(const char *t)
    {
        std::lock_guard<std::mutex> _lk(m_lk);
        ss << t;
        return *this;
    }

    template <typename T>
    Logger &operator<<(const T &t)
    {
        std::lock_guard<std::mutex> _lk(m_lk);
        ss << t;
        return *this;
    }

    Logger &operator<<(std::ostream &(*os)(std::ostream &))
    {
        std::lock_guard<std::mutex> _lk(m_lk);
        time_t rawtime;
        char now[80];

        time(&rawtime);
        struct tm *tt = localtime(&rawtime);

        strftime(now, 80, "%Y-%m-%d %H:%M:%S", tt);

        std::string prefix = "";
        if (!m_filename.empty())
        {
            prefix += "[" + m_filename + ":" +
                      std::to_string(m_line) + " " +
                      m_funcname + "]";
        }

        prefix += "[" + std::string(now) + "][" +
                  severity_str[static_cast<int>(m_severity)] + "] ";

        std::cerr << prefix << ss.str() << os;
        ss.str("");
        m_funcname = "";
        m_filename = "";
        m_line = 0;
        return *this;
    }

    template <typename T>
    Logger &operator()(T t)
    {
        *this << t << std::endl;
        return *this;
    }

    template <typename T, typename... Args>
    Logger &operator()(T t, Args... args)
    {
        *this << t;
        Logger()(args...);
        return *this;
    }
};

#define ENDL std::endl

#ifndef NDEBUG
#define LOGI Logger::Instance(Severity::INFO, __FILE__, __LINE__, __func__)
#define LOGV Logger::Instance(Severity::VERBOSE, __FILE__, __LINE__, __func__)
#define LOGD Logger::Instance(Severity::DEBUG, __FILE__, __LINE__, __func__)
#define LOGW Logger::Instance(Severity::WARNNING, __FILE__, __LINE__, __func__)
#define LOGE Logger::Instance(Severity::ERROR, __FILE__, __LINE__, __func__)

#define LOGFI(a, v...) LOGI(a, ##v)
#define LOGFV(a, v...) Logger::Instance(Severity::VERBOSE, __FILE__, __LINE__, __func__)(a, ##v)
#define LOGFD(a, v...) Logger::Instance(Severity::DEBUG, __FILE__, __LINE__, __func__)(a, ##v)
#define LOGFW(a, v...) Logger::Instance(Severity::WARNNING, __FILE__, __LINE__, __func__)(a, ##v)
#define LOGFE(a, v...) Logger::Instance(Severity::ERROR, __FILE__, __LINE__, __func__)(a, ##v)

#else
#define LOGI Logger::Instance()
#define LOGV Logger::Instance()
#define LOGD Logger::Instance()
#define LOGW Logger::Instance()
#define LOGE Logger::Instance()

#define LOGFI(a, v...) Logger::Instance()(a, ##v)
#define LOGFV(a, v...) Logger::Instance()(a, ##v)
#define LOGFD(a, v...) Logger::Instance()(a, ##v)
#define LOGFW(a, v...) Logger::Instance()(a, ##v)
#define LOGFE(a, v...) Logger::Instance()(a, ##v)
#endif // NDEBUG

#define LINE LOGI << __FILE__ << __LINE__ << ENDL
#endif //__LOGGER
