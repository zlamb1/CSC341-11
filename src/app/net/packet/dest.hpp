#pragma once

#include <memory>

#include "base.hpp"
#include "data/user.hpp"

/**
 * @Pattern Chain of Responsibility (CoR)
 */

struct PacketRequest {
    public:
        PacketRequest(BasePacketRef packet, UserRef packetSender)
            : m_Packet(packet), m_PacketSender(packetSender) {}

        bool accepted() const {
            return m_Accepted;
        }

        void accept() {
            m_Accepted = true;
        }

        BasePacketRef packet() const {
            return m_Packet;
        };

        UserRef packetSender() const {
            return m_PacketSender;
        }

    protected:
        bool m_Accepted = false;
        BasePacketRef m_Packet;
        UserRef m_PacketSender;
};

class PacketDestination;

using PacketDestinationRef = std::shared_ptr<PacketDestination>;

class PacketDestination {
    public:
        PacketDestination(PacketDestination *next = 0) : m_Next(next) {}

        virtual void handlePacket(PacketRequest *request) = 0;

        PacketDestinationRef next() const {
            return m_Next;
        }

        void setNext(PacketDestinationRef next) {
            m_Next = next;
        }

        bool hasNext() {
            return m_Next != nullptr;
        }

    protected:
        PacketDestinationRef m_Next;
};