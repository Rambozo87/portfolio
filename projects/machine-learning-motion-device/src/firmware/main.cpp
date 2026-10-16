#include <Arduino.h>
#include <Wire.h>
#include <usb_rawhid.h>

constexpr int MPU_ADDRESS = 0x68;

struct Packet {
  int16_t counter;
  int16_t timestamp;
  int16_t acceleration[3];
  int16_t gyroscope[3];
  int16_t temperature;
};

Packet packet{};
uint8_t transmit_buffer[64]{};

void read_sensor() {
  Wire.beginTransmission(MPU_ADDRESS);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDRESS, 14, true);

  for (int16_t &axis : packet.acceleration)
    axis = Wire.read() << 8 | Wire.read();
  for (int16_t &axis : packet.gyroscope)
    axis = Wire.read() << 8 | Wire.read();
  packet.temperature = Wire.read() << 8 | Wire.read();
}

void encode_packet() {
  std::fill_n(transmit_buffer, sizeof(transmit_buffer), 0);
  const int16_t values[] = {
      packet.counter,         packet.timestamp,       packet.acceleration[0],
      packet.acceleration[1], packet.acceleration[2], packet.gyroscope[0],
      packet.gyroscope[1],    packet.gyroscope[2],    packet.temperature,
  };
  for (size_t i = 0; i < sizeof(values) / sizeof(values[0]); ++i) {
    transmit_buffer[i * 2] = static_cast<uint8_t>(values[i] & 0xff);
    transmit_buffer[i * 2 + 1] = static_cast<uint8_t>((values[i] >> 8) & 0xff);
  }
}

void setup() {
  Wire.begin();
  Wire.beginTransmission(MPU_ADDRESS);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
}

void loop() {
  read_sensor();
  packet.timestamp = millis();
  encode_packet();
  if (usb_rawhid_send(transmit_buffer, 10))
    ++packet.counter;
}
