#pragma once

#include <memory>

#include "base.hpp"
#include "data/user.hpp"

/**
 * @Pattern Chain of Responsibility (CoR)
 */

struct PacketRequest {
    public:
        PacketRequest(BasePacketRef packet) : m_Packet(packet) {}

        bool accepted() const {
            return m_Accepted;
        }

        void accept() {
            m_Accepted = true;
        }

        BasePacketRef packet() const {
            return m_Packet;
        };

    protected:
        bool m_Accepted = false;
        BasePacketRef m_Packet;
        UserRef m_PacketSender;
};

class PacketHandler;

using PacketHandlerRef = std::shared_ptr<PacketHandler>;

class PacketHandler {
    public:
        PacketHandler(PacketHandler *next = 0) : m_Next(next) {}

        virtual void handlePacket(PacketRequest *request) = 0;

        PacketHandlerRef next() const {
            return m_Next;
        }

        void setNext(PacketHandlerRef next) {
            m_Next = next;
        }

        bool hasNext() {
            return m_Next != nullptr;
        }

    protected:
        PacketHandlerRef m_Next;
};