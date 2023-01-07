#include <pack.h>
#include <ec_lib/frame.hpp>
#include <ec_lib/datatypes/ethernet_frame.hpp>

auto main() -> int {
  ec::ec_command command;
  return 0;
}


namespace ec {

// Test that the packed struct has the correct size
constexpr header_t header{
  .ethercat_type=header_t::ethercat_type_e::standard_ethernet_frame,
  .protocol=header_t::protocol_e::ethercat,
  .data_length=42,
  .destination_address={std::byte{13},std::byte{37},std::byte{13},std::byte{37},std::byte{13},std::byte{37}},
  .source_address={std::byte{42},std::byte{24},std::byte{42},std::byte{24},std::byte{42},std::byte{24}},
  .crc=0x12345
};
//static_assert(pack_struct(header).size() == sizeof(header_t));
//
//// Test that the packed struct has the correct contents
//constexpr std::vector<std::byte> expected = {
//        std::byte{42},
//        std::byte{3},
//        std::byte{14},
//        std::byte{64},
//        std::byte{0},
//        std::byte{0},
//        std::byte{0},
//        std::byte{0},
//        std::byte{0},
//        std::byte{0},
//        std::byte{248},
//        std::byte{59},
//        std::byte{64},
//};
//static_assert(pack_struct(header) == expected);
//
//// Test that the packed struct can be unpacked correctly
//MyStruct s2;
//std::memcpy(&s2, expected.data(), sizeof(MyStruct));
//static_assert(s2.x == 42);
//static_assert(s2.y == 3.14f);
//static_assert(s2.z == 2.718);

}
