#pragma once

#include <string>

namespace alpaca {

    __time32_t parseTimeStamp(std::string&& timestamp);
    int32_t getTimeZoneOffset(const std::string& timestamp);

    struct Clock {
        __time32_t next_close;
        __time32_t next_open;
        __time32_t timestamp;
        bool is_open;

    private:
        template<typename> friend class Response;

        template<typename CallerT, typename T>
        std::pair<int, std::string> fromJSON(const T& parser) {
            parser.get<bool>("is_open", is_open);
            next_close = parseTimeStamp(parser.get<std::string>("next_close"));
            next_open = parseTimeStamp(parser.get<std::string>("next_open"));
            timestamp = parseTimeStamp(std::move(parser.get<std::string>("timestamp")));
            return std::make_pair(0, "OK");
        }
    };
} // namespace alpaca