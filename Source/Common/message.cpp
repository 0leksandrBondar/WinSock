#include "message.h"

namespace bond
{
    namespace network
    {

        Message::Message(const std::string& type, std::vector<char> body, uint32_t packetSize)
            : _body(std::move(body))
        {
            _header.totalSize = _body.size();
            _header.packetSize = packetSize;
            _header.totalPackets = (_body.size() + packetSize - 1) / packetSize;
            std::snprintf(_header.messageType, sizeof(_header.messageType), "%s", type.c_str());
        }

    } // namespace network
} // namespace bond
