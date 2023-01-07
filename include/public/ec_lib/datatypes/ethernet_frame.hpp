#ifndef ETHERCAT_ETHERNET_FRAME_HPP
#define ETHERCAT_ETHERNET_FRAME_HPP

#pragma once

#include <array>
#include <cstdint>

/// References
/// https://sir.upc.edu/wikis/roblab/index.php/Development/Ethercat
/// https://www.etherlab.org/download/ethercat/ethercat-1.5.2.pdf
/// https://www.eit.lth.se/sprapport.php?uid=580
/// https://iopscience.iop.org/article/10.1088/1757-899X/612/4/042052/pdf
/// https://rt-labs.com/refman/ethercat-sdk_refman.pdf
/// https://www.ethercat.org/download/documents/ETG2200_V3i1i1_G_R_SlaveImplementationGuide.pdf

namespace ec {

template <typename payload_t>
struct [[nodiscard]] ethernet_frame {
  enum struct ethertype_e : std::uint16_t {
    null_ethernet_type = 0x0000,
    ipv4 = 0x0800,
    ipv6 = 0x86DD,
    address_resolution_protocol = 0x0806,
    wake_on_lan = 0x0842,
    ethercat_communication_protocol = 0x88A4,
    ethercat_configuration_protocol = 0x88A5,
  };

  // Destination MAC address
  std::array<std::byte, 6> destination_mac{};

  // Source MAC address
  std::array<std::byte, 6> source_mac{};

  ethertype_e ethertype{ethertype_e::null_ethernet_type};

  // EtherCat Protocol Data Unit payload is of maximum length 1500 bytes
  static_assert(sizeof(payload_t) == 1500);
  payload_t payload{};

  // Frame check sequence (FCS) todo how to calculate
  std::uint32_t fcs{};
};

struct epdu_command;
using ec_command = ethernet_frame<epdu_command>;

/// \enum ethercat_type_e
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

template <ethercat_type_e type> struct epdu_header {
  ethercat_type_e ethercat_type{type};

  // Length of data in buffer, optional ... not exactly sure how to handle it
  //  std::uint16_t data_length{};
};

template <std::size_t buffer_size> struct epdu_footer {
  std::array<std::byte, buffer_size> data{};
};

struct epdu_command : public epdu_header<ethercat_type_e::ethercat_command_frame>, public epdu_footer<1493> {
  /// \enum command_e
  /// SDO: Service Data Object.
  /// A protocol for transferring small data packets between devices in the ethercat network.
  /// CoE: CAN over Ethernet.
  /// A protocol for transferring data using the CAN protocol over Ethernet.
  /// FoE: File over Ethernet.
  /// A protocol for transferring files between devices in the ethercat network.
  /// SoE: Servo over Ethernet.
  /// A protocol for transferring servo control data between devices in the ethercat network.
  /// VoE: Voice over Ethernet.
  /// A protocol for transferring voice data between devices in the ethercat network.
  /// EoE: Ethernet over EtherCAT.
  /// A protocol for transferring Ethernet data between devices in the ethercat network.
  enum struct command_e : std::uint8_t {
    unknown = 0x00,
    read = 0x01,
    write = 0x02,
    get_status = 0x03,
    reset = 0x04,
    restart = 0x05,
    sync = 0x06,
    upload = 0x07,
    download = 0x08,
    sdo_upload = 0x09,
    sdo_download = 0x0A,
    coe_upload = 0x0B,
    coe_download = 0x0C,
    foe_upload = 0x0D,
    foe_download = 0x0E,
    foe_read = 0x0F,
    foe_write = 0x10,
    soe_read = 0x11,
    soe_write = 0x12,
    voe_read = 0x13,
    voe_write = 0x14,
    voe_execute = 0x15,
    eoe_read = 0x16,
    eoe_write = 0x17,
    eoe_execute = 0x18,
    eoe_set = 0x19,
    eoe_get = 0x1A,
  };

  command_e command{command_e::unknown};
};

} // namespace ec

#endif // ETHERCAT_ETHERNET_FRAME_HPP
