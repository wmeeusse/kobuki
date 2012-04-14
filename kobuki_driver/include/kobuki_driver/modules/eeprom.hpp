/**
 * @file /include/kobuki_driver/modules/eeprom.hpp
 *
 * Module for handling of eeprom packet payloads.
 *
 * Not currently using this yet.
 */
/*****************************************************************************
** Preprocessor
*****************************************************************************/

#ifndef KOBUKI_EEPROM_DATA_HPP__
#define KOBUKI_EEPROM_DATA_HPP__

/*****************************************************************************
** Include
*****************************************************************************/

#include <vector>
#include "packet_handler/payload_base.hpp"
#include "../packet_handler/payload_headers.hpp"

/*****************************************************************************
** Namespace
*****************************************************************************/

namespace kobuki
{

/*****************************************************************************
** Interface
*****************************************************************************/

class Eeprom : public packet_handler::payloadBase
{
public:
  struct Data {
    Data() : tmp_eeprom(16) {}
    uint8_t tmp_frame_id;
    std::vector<uint8_t> tmp_eeprom;
  };

  bool serialise(ecl::PushAndPop<unsigned char> & byteStream)
  {
    if (!(byteStream.size() > 0))
    {
      //ROS_WARN_STREAM("kobuki_node: kobuki_eeprom: serialise failed. empty byte stream.");
      return false;
    }

    buildBytes(Header::Eeprom, byteStream);
    buildBytes(data.tmp_frame_id, byteStream);
    for (unsigned int i = 0; i < data.tmp_eeprom.size(); ++i)
    {
      buildBytes(data.tmp_eeprom[i], byteStream);
    }
    return true;
  }

  bool deserialise(ecl::PushAndPop<unsigned char> & byteStream)
  {
    if (!(byteStream.size() > 0))
    {
      //ROS_WARN_STREAM("kobuki_node: kobuki_eeprom: deserialise failed. empty byte stream.");
      return false;
    }

    unsigned char header_id;
    buildVariable(header_id, byteStream);
    buildVariable(data.tmp_frame_id, byteStream);
    for (unsigned int i = 0; i < data.tmp_eeprom.size(); ++i)
    {
      buildVariable(data.tmp_eeprom[i], byteStream);
    }

    return true;
  }
};

} // namespace kobuki

#endif /* KOBUKI_EEPROM_DATA_HPP__ */
