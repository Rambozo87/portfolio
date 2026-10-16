#pragma once

#include <hidapi/hidapi.h>

class read_hid {
public:
  read_hid(int vendor_id, int product_id);
  ~read_hid();

  bool is_open() const;
  unsigned char *read();

private:
  hid_device *handle = nullptr;
  unsigned char buffer[64] = {};
};
