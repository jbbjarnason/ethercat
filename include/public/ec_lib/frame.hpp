#ifndef ETHERCAT_FRAME_HPP
#define ETHERCAT_FRAME_HPP

#pragma once

#include <cstdint>
#include <cstddef>
#include <array>
#include <vector>

namespace ec {

struct [[nodiscard]] header_t {
  /// \enum ethercat_type_t
  /// \var standard_ethernet_frame
  /// Used to transmit standard Ethernet frames, such as ARP or IP frames, over the EtherCAT network.
  /// \var ethercat_command_frame
  /// Used to transmit command frames from the EtherCAT master to the slave devices.
  /// Command frames are used to initiate actions or request information from the slave devices.
  /// \var ethercat_response_frame
  /// Used to transmit response frames from the slave devices to the EtherCAT master.
  /// Response frames contain the requested information or acknowledge receipt of a command.
  /// \var ethercat_data_frame
  /// Used to transmit data frames between the EtherCAT master and slave devices.
  /// Data frames contain application-specific data and are used to exchange information between the master and slave devices.
  /// \var reserved
  /// Reserved for future use and should not be used in current implementations of the EtherCAT Type.
  /// \var application_specific allowed values from 0x80-0xFF.
  /// Used to transmit application-specific data between the EtherCAT master and slave devices.
  /// These frame types are defined by the application and are not part of the standard EtherCAT protocol.
  enum struct ethercat_type_e : std::uint8_t {
    standard_ethernet_frame = 0x00,
    ethercat_command_frame = 0x01,
    ethercat_response_frame = 0x02,
    ethercat_data_frame = 0x03,
    reserved = 0x04,
    application_specific = 0x80
  };
  /// \enum protocol_t
  /// \var ethercat
  /// EtherCat is based on the standard Ethernet Protocol,
  /// but includes additional features and functionality to support real-time communication and synchronization between devices.
  /// \var ethernet
  /// Ethernet Protocol, which allows standard Ethernet frames,
  /// such as ARP or IP frames, to be transmitted over the EtherCAT network.
  /// \var canopen
  /// CANopen Protocol, which is a communication protocol for industrial control systems.
  /// CANopen is based on the standard CAN (Controller Area Network)
  /// Protocol and is used to exchange data and control commands between devices in a network.
  /// \var reserved
  /// Reserved for future use and should not be used in current implementations of the EtherCAT Protocol.
  enum class protocol_e : std::uint8_t {
    ethercat = 0x00,
    ethernet = 0x01,
    canopen = 0x02,
    reserved = 0x03
  };
  ethercat_type_e ethercat_type{};
  protocol_e protocol{};
  std::uint16_t data_length{}; ///< bytes
  static constexpr auto mac_address_byte_length{6};
  std::array<std::byte, mac_address_byte_length> destination_address{};
  std::array<std::byte, mac_address_byte_length> source_address{};
  std::uint32_t crc{};
};

static_assert(sizeof(header_t) == 20);

struct [[nodiscard]] frame_t {
  header_t header;
  std::vector<std::byte> payload{};
};

}


#endif //ETHERCAT_FRAME_HPP
