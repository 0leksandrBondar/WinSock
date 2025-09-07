#pragma once

#include <winsock2.h>

namespace bond
{
    namespace network
    {
        class WsaData
        {
        public:
            WsaData() = default;
            ~WsaData() { cleanup(); }

            bool startup();
            bool cleanup();

        private:
            WSADATA _wsaData;
        };
    } // namespace network
} // namespace bond
