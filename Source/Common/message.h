#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace bond
{
    namespace network
    {

        struct Header
        {
            char messageType[32];
            uint64_t totalSize{};
            uint32_t packetSize{};
            uint32_t totalPackets{};
        };

        class Message
        {
        public:
            Message(const std::string& type, std::vector<char> body, uint32_t packetSize = 4096);

            const Header& header() const { return _header; }
            const std::vector<char>& body() const { return _body; }

        private:
            Header _header{};
            std::vector<char> _body;
        };
    } // namespace network
} // namespace bond
